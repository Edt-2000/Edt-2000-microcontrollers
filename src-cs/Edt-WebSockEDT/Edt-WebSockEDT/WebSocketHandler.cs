using System.Net.WebSockets;
using System.Text;

namespace EdtWebSockEDT;

public class WebSocketHandler
{
    private readonly List<(string type, Uri? uri, WebSocket ws)> _webSockets = new();
    private readonly Uri[] _outboundWebSocketUrls = [new Uri("ws://10.0.0.25:80/ws")];
    private readonly bool _activelyOpenOutboundWebSocket;

    public WebSocketHandler(bool activelyOpenOutboundWebSocket)
    {
        _activelyOpenOutboundWebSocket = activelyOpenOutboundWebSocket;
    }

    public void AddWebSocket(string type, WebSocket ws)
    {
        _webSockets.Add((type, null, ws));
    }

    public void RemoveWebSocket(WebSocket ws)
    {
        _webSockets.RemoveAll(x => x.ws == ws);
    }

    public async Task MaintainOutboundWebSocketsAsync()
    {
        if (!_activelyOpenOutboundWebSocket)
        {
            return;
        }

        foreach (var uri in _outboundWebSocketUrls)
        {
            var socket = _webSockets.FirstOrDefault(x => x.uri == uri);

            if (socket == default || (socket.ws.State != WebSocketState.Open && socket.ws.State != WebSocketState.Connecting))
            {
                await AddOutboundWebSocketAsync(uri);
            }
        }
    }

    public async Task SendAsync(string type, string data)
    {
        var memory = new ReadOnlyMemory<byte>(Encoding.UTF8.GetBytes(data));
        var sockets = _webSockets.Where(x => x.type == type).ToArray();

        foreach (var socket in sockets)
        {
            var (_, _, ws) = socket;

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

    private async Task AddOutboundWebSocketAsync(Uri uri)
    {
        var outbound = new ClientWebSocket();
        outbound.Options.KeepAliveInterval = TimeSpan.FromSeconds(5);
        try
        {
            await outbound.ConnectAsync(uri, CancellationToken.None);

            Console.WriteLine($"New device of type led at address {uri} added");

            _webSockets.Add(("led", uri, outbound));
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Adding outbound WebSocket encountered issue: {ex.Message}");
        }
    }
}
