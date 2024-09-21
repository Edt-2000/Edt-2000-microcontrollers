using System.Net.WebSockets;
using EdtWebSockEDT;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddSingleton(new WebSocketHandler());

builder.Services.AddHostedService<MidiBackgroundService>();

var app = builder.Build();

app.UseWebSockets(new() { KeepAliveInterval = TimeSpan.FromSeconds(10) });

app.Map("/{type:regex(^led|control$)}", async (string type, HttpContext context, WebSocketHandler handler) =>
{
    if (context.WebSockets.IsWebSocketRequest)
    {
        Console.WriteLine($"New device of type {type} joined");

        using var ws = await context.WebSockets.AcceptWebSocketAsync();

        handler.AddWebSocket(type, ws);

        var buffer = new byte[1024 * 4];

        while (ws.State == WebSocketState.Open)
        {
            // todo: this should be forwarded to the led units
            await ws.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None);

            await Task.Delay(1000);
        }

        Console.WriteLine($"Device of type {type} left");
    }
    else
    {
        context.Response.StatusCode = StatusCodes.Status400BadRequest;
    }
});

app.Run();
