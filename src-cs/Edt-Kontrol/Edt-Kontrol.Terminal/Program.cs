using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Threading;
using System.Threading.Tasks;
using Dispedter.Common.Factories;
using Edt_Kontrol.Effects;
using Edt_Kontrol.Midi;
using Edt_Kontrol.OSC;

namespace Edt_Kontrol.Terminal
{
    class Program
    {
        private static Kontrol _kontrol = new Kontrol();

        private static ISender[] _senderFs = new[] {
            //new UdpSender(IPAddress.Parse("10.0.0.20"), 12345),
            new UdpSender(IPAddress.Parse("10.0.0.21"), 12345),
            new UdpSender(IPAddress.Parse("10.0.0.22"), 12345)
        };
        //private static ISender _senderR = new UdpSender(IPAddress.Parse("10.0.0.40"), 12345);
        //private static ISender _senderDmx = new UdpSender(IPAddress.Parse("10.0.0.30"), 12345);
        //  ADD 10.0.0.30

        private static CommandFactory _commandFactory = new CommandFactory(new[] { "/F?" });
        private static CommandFactory _addressCommandFactory = new CommandFactory(new[] { "/?1", "/?2", "/?3", "/?4", "/?5", "/?6", "/?7", "/?8" });

        private static readonly int[] Count = new int[8];
        private static readonly int[] Value = new int[8];
        private static readonly int[] CurrentVariant = new int[8];
        private static bool _strobo = false;

        private static Random _random = new Random();

        private static Timer[] _timers;

        private static int _currentColor = 0;
        private static Dictionary<Mode, ColorPreset[]> _colorSets = new Dictionary<Mode, ColorPreset[]>()
        {
#pragma warning disable format
            [0] =                       new[] { ColorPreset.Red, ColorPreset.White },
            [Mode.One] =                new[] { ColorPreset.Red, ColorPreset.Blue },
            [Mode.Two] =                new[] { ColorPreset.Turquoise, ColorPreset.Pink },
            [Mode.One | Mode.Two] =     new[] { ColorPreset.Pink },
            [Mode.Four] =               new[] { ColorPreset.Green, ColorPreset.Amber },
            [Mode.One | Mode.Four] =    new[] { ColorPreset.Green, ColorPreset.White },
            [Mode.Two | Mode.Four] =    new[] { ColorPreset.Red, ColorPreset.Amber }
#pragma warning restore format

        };


        static async Task Main(string[] args)
        {
            _colorSets[Mode.One | Mode.Two | Mode.Four] = Enumerable.Range(0, 255).Cast<ColorPreset>().ToArray();

            await _kontrol.InitAsync();

            _timers = new[]
            {
                new Timer((o) => TwinkePerIntensityAsync(0, _kontrol.Channels[0]), default, 0, 40),
                new Timer((o) => PulseAsync(1, _kontrol.Channels[1]), default, 5, 1),
                new Timer((o) => PulseMuxAsync(2, _kontrol.Channels[2]), default, 10, 40),
                new Timer((o) => ChaseAsync(3, _kontrol.Channels[3], true), default, 15, 40),
                new Timer((o) => ChaseAsync(4, _kontrol.Channels[4], false), default, 20, 40),
                new Timer((o) => TwinkeWithIntensityAsync(5, _kontrol.Channels[5]), default, 20, 40),
                new Timer((o) => VuMeterAsync(6, _kontrol.Channels[6]), default, 30, 1),
                new Timer((o) => SolidAsync(7, _kontrol.Channels[7]), default, 35, 1),

                new Timer(TriggersAsync, default, 40, 40)
            };

            await Task.Delay(-1);
        }

        static async void TwinkePerIntensityAsync(int channel, ChannelState state)
        {
            if (PulseOncePer(channel, state.IntensityLog))
            {
                var message = _commandFactory.CreateTwinkle((ColorPreset)((state.Select * 2) + 1), 160 - (state.Intensity / 2));
                await SendAsync(message);
            }
        }

        static async void PulseAsync(int channel, ChannelState state)
        {
            var variant = Variant(channel, state.Select, 8);

            if (PulseOncePer(channel, state.Intensity))
            {
                var message = variant switch
                {
                    0 => _addressCommandFactory.CreatePartialTwinkle(() => RandomColor(state.Mode)),
                    1 => _addressCommandFactory.CreateSingleSolid(RandomColor(state.Mode), 255, 255).TakeRandom(3),
                    2 => _addressCommandFactory.CreateRainbowPulse(PulseLength.Long).TakeRandom(3),
                    3 => _addressCommandFactory.CreateSinglePulse(RandomColor(state.Mode), 255, 255, PulseLength.Long).TakeRandom(3),
                    4 => _addressCommandFactory.CreateDualPulse(RandomColor(state.Mode), RandomColor(state.Mode), 127 / 2, PulseLength.Long).TakeRandom(3),
                    5 => _addressCommandFactory.CreateSinglePulse(RandomColor(state.Mode), 255, 255, PulseLength.Medium).TakeRandom(4),
                    6 => _addressCommandFactory.CreateDualPulse(RandomColor(state.Mode), RandomColor(state.Mode), 127 / 2, PulseLength.Medium).TakeRandom(4),
                    7 => _addressCommandFactory.CreateSinglePulse(RandomColor(state.Mode), 255, 255, PulseLength.Short).TakeRandom(5),
                    8 => _addressCommandFactory.CreateDualPulse(RandomColor(state.Mode), RandomColor(state.Mode), 127 / 2, PulseLength.Short).TakeRandom(5),

                    _ => Enumerable.Empty<OscMessage>()
                };
                await SendAsync(message);
            }
        }

        static async void TwinkeWithIntensityAsync(int channel, ChannelState state)
        {
            if (state.Intensity > 0)
            {
                var message = _commandFactory.CreateTwinkle((ColorPreset)((state.Select * 2) + 1), state.Intensity * 2);
                await SendAsync(message);
            }
        }

        static async void PulseMuxAsync(int channel, ChannelState state)
        {
            var variant = Variant(channel, state.Select, 5);

            if (PulseOncePer(channel, state.IntensityLog))
            {
                var message = variant switch
                {
                    1 => _commandFactory.CreateSinglePulse(RandomColor(state.Mode), 250, 250, Pulse(state.Intensity)),
                    2 => _commandFactory.CreateSingleSpark(RandomColor(state.Mode), 250, 250, PulseLength.Long),
                    3 => _commandFactory.CreateDualPulse(RandomColor(state.Mode), RandomColor(state.Mode), 63, Pulse(state.Intensity)),
                    4 => _commandFactory.CreateDualSpark(RandomColor(state.Mode), RandomColor(state.Mode), 63, PulseLength.Long),
                    _ => _commandFactory.CreateRainbowPulse(Pulse(state.Intensity))
                };
                await SendAsync(message);
            }
        }

        static async void ChaseAsync(int channel, ChannelState state, bool up)
        {
            if (state.Select > 15)
            {
                if (PulseOncePer(channel, state.Intensity))
                {
                    var color = RandomColor(state.Mode);

                    var message = _commandFactory.CreateChase(color, state.Select / 16, state.Select < 30 ? 1 : 4, up);
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

            if (Count[channel]++ > Math.Abs(((127 - delay) / 127.0) * 20))
            {
                Count[channel] = 0;
                return true;
            }
            return false;
        }

        static bool Changed(int channel, int value)
        {
            if (Value[channel] != value)
            {
                Value[channel] = value;
                return true;
            }

            return false;
        }

        static (int start, int stop) Range(int input, int length)
        {
            var start = (int)Math.Min(127 - length, Math.Max(0, (double)input * ((127.0 - length) / 127.0)));

            return (start, start + length);
        }

        static int Variant(int channel, int input, int options)
        {
            var variant = (int)(input * (options / 127.0));

            if (variant != CurrentVariant[channel])
            {
                CurrentVariant[channel] = variant;

                _kontrol.Notify((byte)variant);
            }

            return variant;
        }

        static PulseLength Pulse(int input) => input < 50 ? PulseLength.Long : PulseLength.Medium;

        static ColorPreset RandomColor(Mode mode)
        {
            var set = _colorSets[mode];
            if (_currentColor >= set.Length)
            {
                _currentColor = 0;
            }
            return set[_currentColor++];
        }

        static ColorPreset Rotate(ColorPreset color, ColorPreset degree) => (ColorPreset)(((int)color + (int)degree) % 255);

        private static async Task SendAsync(IEnumerable<OscMessage> messages)
            => await Task.WhenAll(
                _senderFs.Select(sender => sender.SendAsync(messages.OptionallyBundle())));
    }
}
