using System.Net;
using System.Net.Sockets;
using System.Net.WebSockets;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace EdtSpedtometer;

internal interface ISender
{
    Task InitializeAsync();
    Task SendAsync<T>(T payload);
}

internal class WebSocketSender : ISender
{
    private readonly ClientWebSocket _ws = new ClientWebSocket();
    private readonly Uri _uri = new Uri("ws://10.0.0.25:80/ws");
    private readonly JsonSerializerOptions _jsonSettings = new JsonSerializerOptions
    {
        DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull,
        WriteIndented = false,
        PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
        IncludeFields = true,
        Converters =
        {
            new ValueTupleConverter<int>()
        }
    };

    public async Task InitializeAsync()
    {
        await _ws.ConnectAsync(_uri, CancellationToken.None);
    }

    public async Task SendAsync<T>(T payload)
    {
        var json = JsonSerializer.Serialize(payload, _jsonSettings);

        var animationPayload = Encoding.UTF8.GetBytes(json);

        try
        {
            await _ws.SendAsync(animationPayload, WebSocketMessageType.Binary, true, CancellationToken.None);
        }
        catch (InvalidOperationException)
        {
            await _ws.ConnectAsync(_uri, CancellationToken.None);
            await _ws.SendAsync(animationPayload, WebSocketMessageType.Binary, true, CancellationToken.None);
        }
    }
}

internal class UdpSender : ISender
{
    private readonly UdpClient _client = new();
    private readonly JsonSerializerOptions _jsonSettings = new JsonSerializerOptions
    {
        DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull,
        WriteIndented = false,
        PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
        IncludeFields = true,
        Converters =
        {
            new ValueTupleConverter<int>()
        }
    };

    public Task InitializeAsync()
    {
        _client.Connect(IPEndPoint.Parse("10.0.0.25:12345"));
        return Task.CompletedTask;
    }

    public async Task SendAsync<T>(T payload)
    {
        var json = JsonSerializer.Serialize(payload, _jsonSettings);

        var animationPayload = Encoding.UTF8.GetBytes(json);

        await _client.SendAsync(animationPayload, animationPayload.Length);
    }
}
