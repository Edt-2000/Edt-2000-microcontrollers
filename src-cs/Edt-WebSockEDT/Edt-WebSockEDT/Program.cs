using System.Net.WebSockets;
using System.Text;
using EdtWebSockEDT;

var builder = WebApplication.CreateBuilder(args);

builder.WebHost.UseUrls("http://*:5151");

builder.Services.AddSingleton(new WebSocketHandler(true));

builder.Services.AddHostedService<MidiBackgroundService>();
builder.Services.AddHostedService<WebSocketBackgroundService>();

var app = builder.Build();

app.UseWebSockets(new() { KeepAliveInterval = TimeSpan.FromSeconds(10) });

app.Map("/{type:regex(^led|control|mainframe$)}", async (string type, HttpContext context, WebSocketHandler handler) =>
{
    if (context.WebSockets.IsWebSocketRequest)
    {
        Console.WriteLine($"New device of type {type} joined");

        using var ws = await context.WebSockets.AcceptWebSocketAsync();

        try
        {
            handler.AddWebSocket(type, ws);

            var buffer = new byte[1024 * 4];
            var memory = new Memory<byte>(buffer);

            while (ws.State == WebSocketState.Open)
            {
                var result = await ws.ReceiveAsync(memory, CancellationToken.None);

                if (type == "control" && result.Count > 0)
                {
                    var data = memory[..result.Count];

                    var @string = Encoding.UTF8.GetString(data.Span);

                    await handler.SendAsync("led", @string);
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Device failed with error {ex.Message}");

            handler.RemoveWebSocket(ws);
        }

        Console.WriteLine($"Device of type {type} left");
    }
    else
    {
        context.Response.StatusCode = StatusCodes.Status400BadRequest;
    }
});

app.Run();
