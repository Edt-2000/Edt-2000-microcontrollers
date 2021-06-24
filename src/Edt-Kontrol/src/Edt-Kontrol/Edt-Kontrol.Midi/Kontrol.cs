using Commons.Music.Midi;
using System;
using System.Threading.Tasks;

namespace Edt_Kontrol.Midi
{
    public class Kontrol
    {
        private IMidiInput _input;

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
                var channel = y & 0x07;
                var mode = (y & 0xFC)>>3;
                Channels[channel].Mode = mode;
                if (z == 0x7F)
                {
                    Channels[channel].ButtonPresses++;
                }
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

            for (var i = 0; i < 8; i++)
            {
                Console.WriteLine($"- {Channels[i].Mode:000} {Channels[i].Intensity:000} {Channels[i].Select:000} {Channels[i].ButtonPresses}   ");
            }
        }

        public ChannelState[] Channels { get; set; } = new ChannelState[8];
    }
}
