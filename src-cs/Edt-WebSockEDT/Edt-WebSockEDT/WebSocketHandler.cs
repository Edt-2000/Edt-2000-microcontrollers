using System.Net.WebSockets;
using System.Text;
using System.Threading.RateLimiting;
using EdtWebSockEDT.RateLimiters;
using H.Socket.IO;

namespace EdtWebSockEDT;

public class WebSocketHandler
{
    private readonly MessageAnalyzer _messageAnalyzer = new();

    private readonly List<WebSocketRegistration> _webSockets = new();
    private readonly (string unit, Uri uri)[] _ledWebSocketUrls =
    [
        ("unit1", new Uri("ws://10.0.0.21:80/ws")),
        ("unit2", new Uri("ws://10.0.0.22:80/ws"))
    ];
    private readonly Uri _mainframeWebSocketUrl = new("ws://10.0.0.202:8898");

    private SocketIoClient? _socketIoClient = null;

    private readonly bool _activelyOpenOutboundWebSocket;

    public WebSocketHandler(bool activelyOpenOutboundWebSocket)
    {
        _activelyOpenOutboundWebSocket = activelyOpenOutboundWebSocket;
    }

    public void AddWebSocket(string type, string unit, WebSocket ws)
    {
        _webSockets.Add(new(type, unit, null, ws, CreateRateLimiter(unit)));
    }

    public void RemoveWebSocket(WebSocket ws)
    {
        _webSockets.RemoveAll(x => x.WebSocket == ws);
    }

    public async Task MaintainOutboundWebSocketsAsync()
    {
        if (!_activelyOpenOutboundWebSocket)
        {
            return;
        }

        foreach (var (unit, uri) in _ledWebSocketUrls)
        {
            var socket = _webSockets.FirstOrDefault(x => x.Uri == uri);

            if (socket == default || (socket.WebSocket.State != WebSocketState.Open && socket.WebSocket.State != WebSocketState.Connecting))
            {
                await AddOutboundWebSocketAsync(Constants.WebSocketLed, unit, uri);
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
        var sockets = _webSockets.Where(x => x.Type == type && message.UnitToSentTo.Contains(x.Unit)).ToArray();

        foreach (var socket in sockets)
        {
            var rateLimit = await socket.RateLimiter.AcquireAsync(1);
            if (rateLimit?.IsAcquired == false)
            {
                continue;
            }

            try
            {
                if (socket.WebSocket.State == WebSocketState.Open)
                {
                    try
                    {
                        await socket.WebSocket.SendAsync(memory, WebSocketMessageType.Text, true, CancellationToken.None);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"WebSocket {socket.Type} ({socket.Unit}) encountered issue: {ex.Message}");

                        _webSockets.Remove(socket);
                    }
                }
                else
                {
                    _webSockets.Remove(socket);
                    socket.WebSocket.Dispose();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"WebSocketHandler {socket.Type} ({socket.Unit}) encountered issue: {ex.Message}");
            }

            rateLimit?.Dispose();
        }

        if (colorTask != null)
        {
            await colorTask;
        }
    }

    private async Task AddOutboundWebSocketAsync(string type, string unit, Uri uri)
    {
        var outbound = new ClientWebSocket();
        outbound.Options.KeepAliveInterval = TimeSpan.FromSeconds(5);
        try
        {
            await outbound.ConnectAsync(uri, CancellationToken.None);

            Console.WriteLine($"New device of type {type} ({unit}) at address {uri} added");

            _webSockets.Add(new(type, unit, uri, outbound, CreateRateLimiter(unit)));
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Adding outbound {type} ({unit}) WebSocket encountered issue: {ex.Message}");
        }
    }

    private static RateLimiter CreateRateLimiter(string unit)
    {
        if (unit == "spectacle")
        {
            return new SlidingWindowRateLimiter(new()
            {
                Window = TimeSpan.FromMilliseconds(100),
                SegmentsPerWindow = 1,
                PermitLimit = 1,
                AutoReplenishment = true,
                QueueLimit = 0,
                QueueProcessingOrder = QueueProcessingOrder.NewestFirst
            });
        }

        // TODO: test this and add it to spectacle
        return new LastInQueueRateLimiter(TimeSpan.FromMilliseconds(10));
    }

    private sealed record WebSocketRegistration(
        string Type,
        string Unit,
        Uri? Uri,
        WebSocket WebSocket,
        RateLimiter RateLimiter);
}
