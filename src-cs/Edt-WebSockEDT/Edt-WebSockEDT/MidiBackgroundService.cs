using System.Text.Json;
using EdtWebSockEDT.Midi;

namespace EdtWebSockEDT;

public class MidiBackgroundService : BackgroundService
{
    private readonly Kontrol _kontrol = new();
    private readonly WebSocketHandler _webSocketHandler;
    private readonly JsonSerializerOptions _options = new()
    {
        PropertyNamingPolicy = JsonNamingPolicy.CamelCase
    };

    public MidiBackgroundService(
        WebSocketHandler webSocketHandler)
    {
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

    private void HandleMidiMessage(Channel[] states)
    {
        var data = JsonSerializer.Serialize(states, _options);
        _webSocketHandler.Send(Constants.WebSocketControl, data);
    }
}
