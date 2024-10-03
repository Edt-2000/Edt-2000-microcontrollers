using System.Net.WebSockets;
using System.Text;
using H.Socket.IO;

namespace EdtWebSockEDT;

public class WebSocketHandler
{
    private readonly MessageAnalyzer _messageAnalyzer = new();

    private readonly List<(string type, Uri? uri, WebSocket ws)> _webSockets = new();
    private readonly Uri[] _ledWebSocketUrls = [new Uri("ws://10.0.0.25:80/ws")];
    private readonly Uri _mainframeWebSocketUrl = new("ws://10.0.0.202:8898");

    private SocketIoClient? _socketIoClient = null;

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

        foreach (var uri in _ledWebSocketUrls)
        {
            var socket = _webSockets.FirstOrDefault(x => x.uri == uri);

            if (socket == default || (socket.ws.State != WebSocketState.Open && socket.ws.State != WebSocketState.Connecting))
            {
                await AddOutboundWebSocketAsync(Constants.WebSocketLed, uri);
            }
        }

        if (_socketIoClient == null)
        {
            _socketIoClient = new SocketIoClient();
            _socketIoClient.Connected += (s, e) =>
            {
                Console.WriteLine("Socket IO connected");
            };
            _socketIoClient.Disconnected += (s, e) =>
            {
                Console.WriteLine("Socket IO disconnected");
            };

            try
            {
                await _socketIoClient.ConnectAsync(_mainframeWebSocketUrl, CancellationToken.None, Constants.SocketIoNamespace);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Socket IO encountered issue: {ex.Message}");

                _socketIoClient = null;
            }
        }
    }

    public async Task SendAsync(string type, string data)
    {
        var message = _messageAnalyzer.AnalyzeMessage(type, data);
        Task? colorTask = null;

        if (message.Colors.Length > 0 && _socketIoClient != null)
        {
            colorTask = _socketIoClient.Emit(Constants.SocketIoName, message.Colors.ToMainframeMessage(), Constants.SocketIoNamespace);
        }

        var memory = new ReadOnlyMemory<byte>(Encoding.UTF8.GetBytes(message.MessageToSend));
        var sockets = _webSockets.Where(x => x.type == type).ToArray();

        foreach (var socket in sockets)
        {
            var (socketType, _, ws) = socket;

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
                        Console.WriteLine($"WebSocket {socketType} encountered issue: {ex.Message}");

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
                Console.WriteLine($"WebSocketHandler {socketType} encountered issue: {ex.Message}");
            }
        }

        if (colorTask != null)
        {
            await colorTask;
        }
    }

    private async Task AddOutboundWebSocketAsync(string type, Uri uri)
    {
        var outbound = new ClientWebSocket();
        outbound.Options.KeepAliveInterval = TimeSpan.FromSeconds(5);
        try
        {
            await outbound.ConnectAsync(uri, CancellationToken.None);

            Console.WriteLine($"New device of type {type} at address {uri} added");

            _webSockets.Add((type, uri, outbound));
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Adding outbound {type} WebSocket encountered issue: {ex.Message}");
        }
    }
}
