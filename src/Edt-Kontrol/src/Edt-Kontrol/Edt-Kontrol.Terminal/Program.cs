using Dispedter.Common.Factories;
using Edt_Kontrol.Effects;
using Edt_Kontrol.Midi;
using Edt_Kontrol.OSC;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Threading;
using System.Threading.Tasks;

namespace Edt_Kontrol.Terminal
{
    class Program
    {
        private static Kontrol _kontrol = new Kontrol();

        private static ISender _senderF = new UdpSender(IPAddress.Parse("10.0.0.20"), 12345);
        private static ISender _senderR = new UdpSender(IPAddress.Parse("10.0.0.21"), 12345);
        private static ISender _senderDmx = new UdpSender(IPAddress.Parse("10.0.0.30"), 12345);
        //  ADD 10.0.0.30

        private static CommandFactory _commandFactory = new CommandFactory(new[] { "/F?", "/R?" });

        private static int[] _count = new int[8];
        private static int[] _value = new int[8];
        private static bool _strobo = false;

        private static Random _random = new Random();

        private static Timer[] _timers;

        private static Dictionary<int, ColorPreset[]> _colorSets = new Dictionary<int, ColorPreset[]>()
        {
            // TODO: chase lower intensity
            [0] = new[] { ColorPreset.Red, ColorPreset.White },
            [1] = new[] { ColorPreset.Red, ColorPreset.Blue },
            [2] = new[] { ColorPreset.Turquoise, ColorPreset.Pink },
            [3] = new[] { ColorPreset.Green, ColorPreset.Amber }

        };

        static async Task Main(string[] args)
        {
            await _kontrol.InitAsync();

            _timers = new[]
            {
                new Timer((o) => TwinkeAsync(0, _kontrol.Channels[0]), default, 0, 40),
                new Timer((o) => TwinkeAsync(1, _kontrol.Channels[1]), default, 5, 40),
                new Timer((o) => PulseMuxAsync(2, _kontrol.Channels[2]), default, 10, 40),
                new Timer((o) => ChaseAsync(3, _kontrol.Channels[3], 1), default, 15, 40),
                new Timer((o) => ChaseAsync(4, _kontrol.Channels[4], 3), default, 20, 40),

                new Timer((o) => VuMeterAsync(6, _kontrol.Channels[6]), default, 30, 1),
                new Timer((o) => SolidAsync(7, _kontrol.Channels[7]), default, 35, 1),

                new Timer(TriggersAsync, default, 40, 40)
            };

            await Task.Delay(-1);
        }

        static async void TwinkeAsync(int channel, ChannelState state)
        {
            if (PulseOncePer(channel, state.IntensityLog))
            {
                var message = _commandFactory.CreateTwinkle((ColorPreset)((state.Select * 2) + 1), 160 - (state.Intensity / 2));
                await SendAsync(message);
            }
        }

        static async void PulseMuxAsync(int channel, ChannelState state)
        {
            if (PulseOncePer(channel, state.IntensityLog))
            {
                var color1 = RandomColor(state.Mode);
                var color2 = RandomColor(state.Mode);
                var message = Variant(state.Select, 5) switch
                {
                    1 => _commandFactory.CreateSinglePulse(color1, 250, 250, Pulse(state.Intensity)),
                    2 => _commandFactory.CreateSingleSpark(color1, 250, 250, PulseLength.Long),
                    3 => _commandFactory.CreateDualPulse(color1, color2, 63, Pulse(state.Intensity)),
                    4 => _commandFactory.CreateDualSpark(color1, color2, 63, PulseLength.Long),
                    _ => _commandFactory.CreateRainbowPulse(Pulse(state.Intensity))
                };
                await SendAsync(message);
            }
        }

        static async void ChaseAsync(int channel, ChannelState state, int type)
        {
            if (state.Select > 15)
            {
                if (PulseOncePer(channel, state.Intensity / 2))
                {
                    var color = RandomColor(state.Mode);

                    var message = _commandFactory.CreateChase(color, state.Select / 16, type);
                    await SendAsync(message);
                }
            }
        }

        static async void VuMeterAsync(int channel, ChannelState state)
        {
            if (Changed(channel, state.Select))
            {
                var message = _commandFactory.CreateVuMeter(state.Select * 2);
                await SendAsync(message);
            }
        }

        static async void SolidAsync(int channel, ChannelState state)
        {
            if (Changed(channel, state.Intensity + state.Select))
            {
                var h = (ColorPreset)((state.Select * 2) + 1);
                var s = state.Mode == Mode.One ? state.Intensity * 2 : 255;
                var v = state.Mode == Mode.Two ? state.Intensity * 2 : 255;

                var message = _commandFactory.CreateSingleSolid(h, s, v);
                await SendAsync(message);
            }
        }

        static async void TriggersAsync(object state)
        {
            if (!_strobo && _kontrol.Play)
            {
                _strobo = true;
                await SendAsync(_commandFactory.CreateStrobo((ColorPreset)255, 130));
            }
            else if (_strobo && _kontrol.Stop)
            {
                _strobo = false;
                await SendAsync(_commandFactory.CreateStrobo(0, 0));
            }

            if (_kontrol.Rec)
            {
                await SendAsync(_commandFactory.CreateSingleSpark((ColorPreset)((_kontrol.Channels[0].Select * 2) + 1), 255, 255, PulseLength.Medium));
            }

            if (_kontrol.Backward)
            {
                await SendAsync(_commandFactory.CreateSinglePulse((ColorPreset)((_kontrol.Channels[0].Select * 2) + 1), 255, 255, PulseLength.Medium));
            }

            if (_kontrol.Forward)
            {
                await SendAsync(_commandFactory.CreateSinglePulse(Rotate((ColorPreset)((_kontrol.Channels[0].Select * 2) + 1), (ColorPreset)127), 255, 255, PulseLength.Medium));
            }
        }

        static bool PulseOncePer(int channel, int delay)
        {
            if (delay == 0)
            {
                return false;
            }

            if (_count[channel]++ > Math.Abs(((127 - delay) / 127.0) * 20))
            {
                _count[channel] = 0;
                return true;
            }
            return false;
        }

        static bool Changed(int channel, int value)
        {
            if (_value[channel] != value)
            {
                _value[channel] = value;
                return true;
            }

            return false;
        }

        static (int start, int stop) Range(int input, int length)
        {
            var start = (int)Math.Min(127 - length, Math.Max(0, (double)input * ((127.0 - length) / 127.0)));

            return (start, start + length);
        }

        static int Variant(int input, int options) => (int)(input * (options / 127.0));

        static PulseLength Pulse(int input) => input < 50 ? PulseLength.Long : PulseLength.Medium;

        static ColorPreset RandomColor(Mode mode) => _colorSets[(int)mode][(int)(_random.NextDouble() * 2)];

        static ColorPreset Rotate(ColorPreset color, ColorPreset degree) => (ColorPreset)(((int)color + (int)degree) % 255);

        private static async Task SendAsync(IEnumerable<OscMessage> messages)
            => await Task.WhenAll(
                _senderF.SendAsync(messages.Where(x => x.Address.Contains("F"))),
                _senderR.SendAsync(messages.Where(x => x.Address.Contains("R"))),
                _senderDmx.SendAsync(messages.Where(x => x.Address.Contains("R"))));
    }
}
