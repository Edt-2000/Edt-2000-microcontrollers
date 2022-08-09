using Commons.Music.Midi;
using System;
using System.Threading.Tasks;

namespace Edt_Kontrol.Midi
{
    public class Kontrol
    {
        private IMidiInput _input;
        private IMidiOutput _output;

        public async Task InitAsync()
        {
            var inputs = MidiAccessManager.Default.Inputs;

            foreach (var inputDevice in inputs)
            {
                if (inputDevice.Name == "nanoKONTROL2")
                {
                    _input = await MidiAccessManager.Default.OpenInputAsync(inputDevice.Id);

                    _input.MessageReceived += Input_MessageReceived;
                }
            }

            var outputs = MidiAccessManager.Default.Outputs;

            foreach (var outputDevice in outputs)
            {
                if (outputDevice.Name == "nanoKONTROL2")
                {
                    _output = await MidiAccessManager.Default.OpenOutputAsync(outputDevice.Id);

                }
            }
        }

        public void Notify(byte type)
        {
            _output.Send(new byte[] { 0x90, 0x5B, IsOn(type, 0x01) }, 0, 3, 0);
            _output.Send(new byte[] { 0x90, 0x5C, IsOn(type, 0x02) }, 0, 3, 0);
            _output.Send(new byte[] { 0x90, 0x5D, IsOn(type, 0x04) }, 0, 3, 0);
            _output.Send(new byte[] { 0x90, 0x5E, IsOn(type, 0x08) }, 0, 3, 0);
            _output.Send(new byte[] { 0x90, 0x5F, IsOn(type, 0x10) }, 0, 3, 0);
        }

        private void Input_MessageReceived(object sender, MidiReceivedEventArgs e)
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
                if (y < 0x18)
                {
                    var channel = (byte)(y & 0x07);
                    var mode = (byte)((y & 0xFC) >> 3);

                    if (mode < 3 && z != 0)
                    {
                        var value = mode switch
                        {
                            2 => Mode.Two,
                            1 => Mode.One,
                            _ => Mode.Four
                        };

                        Channels[channel].Mode = (Channels[channel].Mode & value) > 0 ?
                            Channels[channel].Mode & ~value :
                            Channels[channel].Mode | value;

                        _output.Send(new byte[] { 0x90, (byte)(channel + 8), IsOn(Channels[channel].Mode, Mode.One) }, 0, 3, 0);
                        _output.Send(new byte[] { 0x90, (byte)(channel + 16), IsOn(Channels[channel].Mode, Mode.Two) }, 0, 3, 0);
                        _output.Send(new byte[] { 0x90, (byte)(channel + 0), IsOn(Channels[channel].Mode, Mode.Four) }, 0, 3, 0);
                    }
                    if (z == 0x7F)
                    {
                        Channels[channel].ButtonPresses++;
                    }
                }

                Backward = (y == 0x5B && z == 0x7F);
                Forward = (y == 0x5C && z == 0x7F);
                Stop = (y == 0x5D && z == 0x7F);
                Play = (y == 0x5E && z == 0x7F);
                Rec = (y == 0x5F && z == 0x7F);
            }
            else if (x == 0xb0)
            {
                var channel = y & 0x07;
                if (z == 0x3F)
                {
                    Channels[channel].Select = 127;
                }
                else if (z == 0x7F)
                {
                    Channels[channel].Select = 0;
                }
                else if ((z & 0x40) > 0)
                {
                    Channels[channel].Select -= z & 0x03;
                }
                else
                {
                    Channels[channel].Select += z & 0x03;
                }

                Channels[channel].Select = Math.Max(Math.Min(Channels[channel].Select, 127), 0);
            }
            else if ((x & 0xe0) > 0)
            {
                var channel = x & 0x07;
                var intensity = y;
                Channels[channel].Intensity = intensity;
            }

            Console.SetCursorPosition(0, 0);

            Console.WriteLine($"{x:X2} {y:X2} {z:X2}.");
            Console.WriteLine();

            Console.WriteLine("  M   | I   IL  | S   SL  | ");

            for (var i = 0; i < 8; i++)
            {
                Console.WriteLine(
                    $"- " +
                    $"{((int)Channels[i].Mode):000} | " +
                    $"{Channels[i].Intensity:000} " +
                    $"{Channels[i].IntensityLog:000} | " +
                    $"{Channels[i].Select:000} " +
                    $"{Channels[i].SelectLog:000} | " +
                    $"{Channels[i].ButtonPresses}" +
                    $"   ");
            }

            Console.WriteLine();
            Console.WriteLine(Play ? "Play" : "    ");
            Console.WriteLine(Rec ? "Rec" : "    ");
            Console.WriteLine(Stop ? "Stop" : "    ");
        }

        public ChannelState[] Channels { get; set; } = new ChannelState[8];

        public bool Backward { get; set; }
        public bool Forward { get; set; }
        public bool Stop { get; set; }
        public bool Play { get; set; }
        public bool Rec { get; set; }

        private static byte IsOn(byte type, byte bitmask) => (type & bitmask) > 0 ? (byte)0x7F : (byte)0x00;
        private static byte IsOn(Mode type, Mode bitmask) => (type & bitmask) > 0 ? (byte)0x7F : (byte)0x00;
    }
}
