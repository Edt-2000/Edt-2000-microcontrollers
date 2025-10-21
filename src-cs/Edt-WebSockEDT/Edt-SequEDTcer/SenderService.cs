using System.Net.WebSockets;
using System.Text;
using System.Text.Json;
using System.Threading.Channels;
using Core.Midi;
using Microsoft.Extensions.Hosting;
using Color = int[];

namespace Edt_SequEDTcer;

internal class SenderService : BackgroundService
{
    private readonly ChannelReader<Message> _messageReader;
    private readonly JsonSerializerOptions _options = new()
    {
        PropertyNamingPolicy = JsonNamingPolicy.CamelCase
    };

    public SenderService(
        ChannelReader<Message> messageReader)
    {
        _messageReader = messageReader;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        using var client = new ClientWebSocket();

        await client.ConnectAsync(new Uri("ws://10.0.0.21:80/ws"), stoppingToken);

        do
        {
            var message = await _messageReader.ReadAsync();

            var json = JsonSerializer.Serialize(message, _options);

            var memory = new ReadOnlyMemory<byte>(Encoding.UTF8.GetBytes(json));

            await client.SendAsync(memory, WebSocketMessageType.Text, true, CancellationToken.None);
        }
        while (true);
    }
}

internal static class Colors
{
    public static Color Red => [0, 255, 255];
    public static Color White => [0, 0, 255];
}

internal record Message
{
    public string Animation { get; init; }
    public int Leds { get; init; } = 255;
    public required Color Color1 { get; init; }
    public required Color Color2 { get; init; }
    public int Fade { get; init; } = 40;
    public int Speed { get; init; } = 40;
}

internal static class MessageBuilder
{
    private readonly static List<StateChannel> Channels = new(8)
    {
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
        new StateChannel()
    };

    public static void UpdateChannel(int channel, StateChannel state)
    {
        Channels[channel] = state;
    }

    public static IEnumerable<Message> CreateMessages(int channel)
    {
        var state = Channels[channel];

        var message = new Message
        {
            Animation = state.Select switch
            {
                < 25 => "singlePulse",
                < 50 => "singlePartialPulse",
                < 75 => "doublePulse",
                < 100 => "singleChase",
                _ => "doubleChase",
            },
            Color1 = Colors.White,
            Color2 = Colors.Red,
            Fade = state.Intensity
        };

        yield return message;
    }
}
