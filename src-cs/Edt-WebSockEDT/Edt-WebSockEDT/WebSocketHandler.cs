using System.Net.WebSockets;
using System.Text;

namespace EdtWebSockEDT;

public class WebSocketHandler
{
    private readonly List<(string type, WebSocket ws)> _webSockets = new();
    private readonly bool _activelyOpenOutboundWebSocket;

    public WebSocketHandler(bool activelyOpenOutboundWebSocket)
    {
        _activelyOpenOutboundWebSocket = activelyOpenOutboundWebSocket;
        if (activelyOpenOutboundWebSocket)
        {
            _ = AddOutboundWebSocketAsync();
        }
    }

    public void AddWebSocket(string type, WebSocket ws)
    {
        _webSockets.Add((type, ws));
    }

    public void RemoveWebSocket(WebSocket ws)
    {
        _webSockets.RemoveAll(x => x.ws == ws);
    }

    public async Task SendAsync(string type, string data)
    {
        var memory = new ReadOnlyMemory<byte>(Encoding.UTF8.GetBytes(data));
        var sockets = _webSockets.Where(x => x.type == type).ToArray();

        if (type == "led" && sockets.Length == 0 && _activelyOpenOutboundWebSocket)
        {
            await AddOutboundWebSocketAsync();
        }

        foreach (var socket in sockets)
        {
            var (_, ws) = socket;

            try
            {
                if (ws.State == WebSocketState.Open)
                {
                    try
                    {
                        await ws.SendAsync(memory, WebSocketMessageType.Text, true, CancellationToken.None);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"WebSocket encountered issue: {ex.Message}");

                        _webSockets.Remove(socket);
                    }
                }
                else
                {
                    _webSockets.Remove(socket);
                    ws.Dispose();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"WebSocketHandler encountered issue: {ex.Message}");
            }
        }
    }

    private async Task AddOutboundWebSocketAsync()
    {
        var outbound = new ClientWebSocket();
        await outbound.ConnectAsync(new Uri("ws://10.0.0.25:80/ws"), CancellationToken.None);

        Console.WriteLine("New device of type led added");

        _webSockets.Add(("led", outbound));
    }
}
