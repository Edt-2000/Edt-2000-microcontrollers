using System.Net.WebSockets;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace EdtSpedtometer.Networking;

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
