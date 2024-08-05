using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using EdtSpedtometer.Messaging;

namespace EdtSpedtometer.Networking;

[Obsolete("Only used to test")]
internal class UdpOscSender : ISender
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
        byte[] animationPayload;

        if (payload is AnimationAndSettingsMessage m)
        {
            animationPayload = GetPayload(m);
        }
        else
        {
            var json = JsonSerializer.Serialize(payload, _jsonSettings);
            animationPayload = Encoding.UTF8.GetBytes(json);
        }

        await _client.SendAsync(animationPayload, animationPayload.Length);
    }

    private byte[] GetPayload(AnimationAndSettingsMessage message)
    {
        var oscMessage = new Edt_Kontrol.OSC.OscMessage("/F2", 0, 0, 127, message.Color1.Value.h, message.Color1.Value.s, message.Color1.Value.v, message.Brightness.Value);

        return oscMessage.GetBytes();
    }
}
