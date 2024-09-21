using System.Net.WebSockets;
using System.Text;

namespace EdtWebSockEDT;

public class WebSocketHandler
{
    private readonly List<(string type, WebSocket ws)> _webSockets = new();

    public void AddWebSocket(string type, WebSocket ws)
    {
        _webSockets.Add((type, ws));
    }

    public async Task SendAsync(string type, string data)
    {
        var memory = new ReadOnlyMemory<byte>(Encoding.UTF8.GetBytes(data));

        var sockets = _webSockets.Where(x => x.type == type).ToArray();

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
}
