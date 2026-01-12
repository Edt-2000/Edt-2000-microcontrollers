using System.Net.WebSockets;
using System.Text;
using System.Threading.RateLimiting;
using EdtWebSockEDT.RateLimiters;
using H.Socket.IO;

namespace EdtWebSockEDT;

public class WebSocketHandler
{
    private readonly MessageAnalyzer _messageAnalyzer = new();
    private readonly List<Task> _sendingTasks = new();
    private readonly StatusHandler _statusHandler;

    private readonly List<WebSocketRegistration> _webSockets = new();
    private readonly WebSocketConfig[] _ledWebSocketUrls =
    [
        new("unit1", new Uri("ws://10.0.0.21:80/ws"), ConnectionType.Wired),
        new("unit2", new Uri("ws://10.0.0.22:80/ws"), ConnectionType.Wired),
        new("powerbar", new Uri("ws://10.0.0.30:80/ws"), ConnectionType.Wireless),
        new("strobe1", new Uri("ws://10.0.0.41:80/ws"), ConnectionType.Wireless),
        new("dmx", new Uri("ws://10.0.0.50:80/ws"), ConnectionType.Wired),
    ];
    private readonly Uri _mainframeWebSocketUrl = new("ws://10.0.0.202:8898");

    private SocketIoClient? _socketIoClient = null;

    public WebSocketHandler(StatusHandler statusHandler)
    {
        _statusHandler = statusHandler;
    }

    public void AddWebSocket(string type, string unit, WebSocket ws)
    {
        var connectionType = unit == "spectacle" ? ConnectionType.Wireless : ConnectionType.Wired;

        var socket = new WebSocketRegistration(type, unit, null, ws, CreateRateLimiter(connectionType));
        _webSockets.Add(socket);
        _statusHandler.ReportStatus(socket.ToString(), true);
    }

    public void RemoveWebSocket(WebSocket ws)
    {
        _webSockets.RemoveAll(x => x.WebSocket == ws);
    }

    public async Task MaintainWebSocketsAsync()
    {
        var registerTasks = Task.WhenAll(_ledWebSocketUrls.Select(CreateWebSocketRegistrationAsync));

        if (_socketIoClient == null)
        {
            _socketIoClient = new SocketIoClient();
            _socketIoClient.Connected += (s, e) =>
            {
                Console.WriteLine("Socket IO connected");
                _statusHandler.ReportStatus("SocketIO", true);
            };
            _socketIoClient.Disconnected += (s, e) =>
            {
                Console.WriteLine("Socket IO disconnected");
                _statusHandler.ReportStatus("SocketIO", false);
            };

            try
            {
                await _socketIoClient.ConnectAsync(_mainframeWebSocketUrl, CancellationToken.None, Constants.SocketIoNamespace);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Socket IO encountered issue: {ex.Message}");
                _socketIoClient = null;
                _statusHandler.ReportStatus("SocketIO", false);
            }
        }

        await registerTasks;

        // clean up all tasks that have ran
        _sendingTasks.RemoveAll(task => task.IsCompleted);
    }

    public void Send(string type, string data)
    {
        _sendingTasks.Add(SendAsync(type, data));
    }

    private async Task SendAsync(string type, string data)
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
            using var rateLimit = await socket.RateLimiter.AcquireAsync(1);
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
                        _statusHandler.ReportStatus(socket.ToString(), true);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"WebSocket {socket} encountered issue: {ex.Message}");

                        _statusHandler.ReportStatus(socket.ToString(), false);
                        _webSockets.Remove(socket);
                    }
                }
                else
                {
                    _statusHandler.ReportStatus(socket.ToString(), false);
                    _webSockets.Remove(socket);
                    socket.WebSocket.Dispose();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"WebSocketHandler {socket} encountered issue: {ex.Message}");
            }
        }

        if (colorTask != null)
        {
            _statusHandler.ReportStatus("SocketIO", true);
            await colorTask;
        }
    }

    private async Task CreateWebSocketRegistrationAsync(WebSocketConfig config)
    {
        var socket = _webSockets.FirstOrDefault(x => x.Uri == config.Uri);

        if (socket == default || (socket.WebSocket.State != WebSocketState.Open && socket.WebSocket.State != WebSocketState.Connecting))
        {
            await AddOutboundWebSocketAsync(Constants.WebSocketLed, config.Unit, config.Uri, config.ConnectionType);
        }
    }

    private async Task AddOutboundWebSocketAsync(string type, string unit, Uri uri, ConnectionType connectionType)
    {
        var outbound = new ClientWebSocket();
        outbound.Options.KeepAliveInterval = TimeSpan.FromSeconds(1);
        try
        {
            var socket = new WebSocketRegistration(type, unit, uri, outbound, CreateRateLimiter(connectionType));
            _statusHandler.ReportStatus(socket.ToString(), false);

            await outbound.ConnectAsync(uri, CancellationToken.None);

            Console.WriteLine($"New device of type {type} ({unit}) at address {uri} added");

            _webSockets.Add(socket);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Adding outbound {type} ({unit}) WebSocket encountered issue: {ex.Message}");
        }
    }

    private static RateLimiter CreateRateLimiter(ConnectionType type)
    {
        if (type == ConnectionType.Wireless)
        {
            return new LastInQueueRateLimiter(TimeSpan.FromMilliseconds(100));
        }

        return new LastInQueueRateLimiter(TimeSpan.FromMilliseconds(1));
    }

    public enum ConnectionType
    {
        Wired,
        Wireless
    }

    private sealed record WebSocketRegistration(
        string Type,
        string Unit,
        Uri? Uri,
        WebSocket WebSocket,
        RateLimiter RateLimiter)
    {
        public override string ToString() => Type == Unit ? Type : $"{Type}({Unit})";
    }

    private sealed record WebSocketConfig(
        string Unit,
        Uri Uri,
        ConnectionType ConnectionType);
}
