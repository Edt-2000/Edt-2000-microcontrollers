using Commons.Music.Midi;

namespace EdtWebSockEDT.Midi;

public class Kontrol
{
    private IMidiInput? _input;
    private IMidiOutput? _output;

    private Func<Channel[], Task>? _messageCallback = null;

    public async Task InitAsync(Func<Channel[], Task> onMessage)
    {
        _messageCallback = onMessage;

        await ManageConnectionsAsync();
    }

    public async Task ManageConnectionsAsync()
    {
        if (!MidiAccessManager.Default.Inputs.Any() && _input != null)
        {
            _input = null;
            Console.WriteLine("MIDI Input disconnected");

            _output = null;
            Console.WriteLine("MIDI Output disconnected");
        }

        do
        {
            if (_input == null)
            {
                var inputs = MidiAccessManager.Default.Inputs;

                foreach (var inputDevice in inputs)
                {
                    if (inputDevice.Name.Contains("nanoKONTROL2", StringComparison.CurrentCultureIgnoreCase))
                    {
                        _input = await MidiAccessManager.Default.OpenInputAsync(inputDevice.Id);

                        _input.MessageReceived += MessageReceived;

                        Console.WriteLine("MIDI Input connected");
                    }
                }
            }

            if (_output == null)
            {
                var outputs = MidiAccessManager.Default.Outputs;

                foreach (var outputDevice in outputs)
                {
                    if (outputDevice.Name.Contains("nanoKONTROL2", StringComparison.CurrentCultureIgnoreCase))
                    {
                        _output = await MidiAccessManager.Default.OpenOutputAsync(outputDevice.Id);

                        Console.WriteLine("MIDI Output connected");
                    }
                }
            }

            await Task.Delay(1000);
        }
        while (_input == null || _output == null);
    }

    private void MessageReceived(object? sender, MidiReceivedEventArgs e)
    {
        if (e.Length != 3)
        {
            return;
        }

        var x = e.Data[0];
        var y = e.Data[1];
        var z = e.Data[2];

        if (x == 0x90)
        {
            var channel = (byte)(y & 0x07);
            if (y < 0x18)
            {
                var mode = (byte)((y & 0xFC) >> 3);

                if (mode < 3 && z != 0)
                {
                    var value = mode switch
                    {
                        2 => Mode.Two,
                        1 => Mode.One,
                        _ => Mode.Four
                    };

                    Cs[channel].SetMode(value);
                }
                else
                {
                    Cs[channel].ButtonUp();
                }

                var output = Cs[channel].GetMode();

                _output?.Send([0x90, (byte)(channel + 8), IsOn(output, Mode.One)], 0, 3, 0);
                _output?.Send([0x90, (byte)(channel + 16), IsOn(output, Mode.Two)], 0, 3, 0);
                _output?.Send([0x90, (byte)(channel + 0), IsOn(output, Mode.Four)], 0, 3, 0);
            }
        }
        else if (x == 0xb0)
        {
            var channel = y & 0x07;
            if (z == 0x3F)
            {
                Cs[channel].SetSelect(127, null);
            }
            else if (z == 0x7F)
            {
                Cs[channel].SetSelect(0, null);
            }
            else if ((z & 0x40) > 0)
            {
                Cs[channel].SetSelect(null, -(z & 0x03));
            }
            else
            {
                Cs[channel].SetSelect(null, z & 0x03);
            }
        }
        else if ((x & 0xe0) > 0)
        {
            var channel = x & 0x07;
            var intensity = y;
            Cs[channel].SetIntensity(intensity);
        }

        _messageCallback?.Invoke(Cs);
    }

    public Channel[] Cs { get; set; } = [
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
        new StateChannel(),
    ];

    private static byte IsOn(Mode type, Mode bitmask) => (type & bitmask) > 0 ? (byte)0x7F : (byte)0x00;
}
