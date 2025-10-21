using System.Text.Json;
using System.Text.Json.Serialization;
using Core.Midi;

namespace EdtWebSockEDT;

public class MidiBackgroundService : BackgroundService
{
    private readonly Kontrol _kontrol;
    private readonly WebSocketHandler _webSocketHandler;
    private readonly JsonSerializerOptions _options = new()
    {
        PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
        Converters =
        {
            new JsonStringEnumConverter(JsonNamingPolicy.CamelCase)
        }
    };

    public MidiBackgroundService(
        StatusHandler statusHandler,
        WebSocketHandler webSocketHandler)
    {
        _kontrol = new(statusHandler);
        _webSocketHandler = webSocketHandler;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        var handler = HandleMidiMessage;

        await _kontrol.InitAsync(handler);

        do
        {
            await _kontrol.ManageConnectionsAsync();
        }
        while (!stoppingToken.IsCancellationRequested);
    }

    private void HandleMidiMessage(ChannelMessage message)
    {
        var data = JsonSerializer.Serialize(message, _options);
        _webSocketHandler.Send(Constants.WebSocketControl, data);
    }
}
