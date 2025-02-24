using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace EdtSpedtometer.Networking;

internal class UdpJsonSender : ISender
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
