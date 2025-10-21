using System.Threading.Channels;
using Core.Midi;
using Microsoft.Extensions.Hosting;

namespace Edt_SequEDTcer;

internal class MidiBackgroundService : BackgroundService
{
    private readonly Kontrol _kontrol;
    private readonly ChannelWriter<Message> _messageWriter;
    private readonly Timer _timer;

    private byte _currentChannel = 0;
    private int _counter = 0;

    public MidiBackgroundService(
        Kontrol kontrol,
        ChannelWriter<Message> messageWriter)
    {
        _kontrol = kontrol;
        _messageWriter = messageWriter;
        _timer = new Timer(TimerCallback, null, 0, 2);
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        using (_timer)
        {
            var handler = HandleMidiMessage;

            await _kontrol.InitAsync(handler);

            do
            {
                await _kontrol.ManageConnectionsAsync();
            }
            while (!stoppingToken.IsCancellationRequested);
        }
    }

    private void HandleMidiMessage(ChannelMessage change)
    {
        MessageBuilder.UpdateChannel(change.Index, _kontrol.Cs[change.Index]);
    }

    private void TimerCallback(object? state)
    {
        if (_counter++ < (128 - _kontrol.Cs[_currentChannel].Intensity))
        {
            return;
        }

        _counter = 0;

        _kontrol.Send(_currentChannel, Mode.Zero);

        _currentChannel++;
        _currentChannel %= 8;

        _kontrol.Send(_currentChannel, Mode.Four);

        foreach (var message in MessageBuilder.CreateMessages(_currentChannel))
        {
            _messageWriter.TryWrite(message);
        }
    }
}
