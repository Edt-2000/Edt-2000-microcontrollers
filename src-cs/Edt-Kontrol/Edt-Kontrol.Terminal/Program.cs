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
    internal class Program
    {
        private static readonly Kontrol Kontrol = new Kontrol();

        private static readonly ISender[] SenderSP = new[]
        {
            new UdpSender(IPAddress.Parse("10.0.0.99"), 12345),
        };
        private static readonly ISender[] SenderFs = new[] {
            //new UdpSender(IPAddress.Parse("10.0.0.20"), 12345),
            new UdpSender(IPAddress.Parse("10.0.0.21"), 12345),
            new UdpSender(IPAddress.Parse("10.0.0.22"), 12345)
        };
        //private static ISender _senderR = new UdpSender(IPAddress.Parse("10.0.0.40"), 12345);
        //private static ISender _senderDmx = new UdpSender(IPAddress.Parse("10.0.0.30"), 12345);
        //  ADD 10.0.0.30

        private static readonly CommandFactory CommandFactory = new CommandFactory(new[] { "/F?", "/SP" });
        private static readonly CommandFactory AddressCommandFactory = new CommandFactory(new[] { "/?1", "/?2", "/?3", "/?4", "/?5", "/?6", "/?7", "/?8" });

        private static readonly int[] Count = new int[8];
        private static readonly int[] Value = new int[8];
        private static readonly int[] CurrentVariant = new int[8];

        private static Timer[] _timers;

        private static int _currentColor = 0;
        private static readonly Dictionary<Mode, ColorPreset[]> ColorSets = new Dictionary<Mode, ColorPreset[]>()
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

        private static async Task Main(string[] args)
        {
            ColorSets[Mode.One | Mode.Two | Mode.Four] = Enumerable.Range(0, 255).Cast<ColorPreset>().OrderBy(x => Guid.NewGuid()).ToArray();

            await Kontrol.InitAsync();

            _timers = new[]
            {
                new Timer((o) => TwinkePerIntensityAsync(0, Kontrol.Channels[0]), default, 0, 40),
                new Timer((o) => PulseAsync(1, Kontrol.Channels[1]), default, 5, 1),
                new Timer((o) => PulseMuxAsync(2, Kontrol.Channels[2]), default, 10, 40),
                new Timer((o) => ChaseAsync(3, Kontrol.Channels[3], true), default, 15, 40),
                new Timer((o) => ChaseAsync(4, Kontrol.Channels[4], false), default, 20, 40),
                new Timer((o) => TwinkeWithIntensityAsync(5, Kontrol.Channels[5]), default, 20, 40),
                new Timer((o) => VuMeterAsync(6, Kontrol.Channels[6]), default, 30, 1),
                new Timer((o) => SolidAsync(7, Kontrol.Channels[7]), default, 35, 1),

                new Timer(TriggersAsync, default, 40, 40)
            };

            await Task.Delay(-1);
        }

        private static async void TwinkePerIntensityAsync(int channel, ChannelState state)
        {
            if (PulseOncePer(channel, state.IntensityLog))
            {
                var message = CommandFactory.CreateTwinkle((ColorPreset)((state.Select * 2) + 1), 160 - (state.Intensity / 2));
                await SendAsync(message);
            }
        }

        private static async void PulseAsync(int channel, ChannelState state)
        {
            var variant = Variant(channel, state.Select, 8);

            if (PulseOncePer(channel, state.Intensity))
            {
                var message = variant switch
                {
                    0 => AddressCommandFactory.CreatePartialTwinkle(() => RandomColor(state.Mode)),
                    1 => AddressCommandFactory.CreateSingleSolid(RandomColor(state.Mode), 255, 255).TakeRandom(3),
                    2 => AddressCommandFactory.CreateRainbowPulse(PulseLength.Long).TakeRandom(3),
                    3 => AddressCommandFactory.CreateSinglePulse(RandomColor(state.Mode), 255, 255, PulseLength.Long).TakeRandom(3),
                    4 => AddressCommandFactory.CreateDualPulse(RandomColor(state.Mode), RandomColor(state.Mode), 127 / 2, PulseLength.Long).TakeRandom(3),
                    5 => AddressCommandFactory.CreateSinglePulse(RandomColor(state.Mode), 255, 255, PulseLength.Medium).TakeRandom(4),
                    6 => AddressCommandFactory.CreateDualPulse(RandomColor(state.Mode), RandomColor(state.Mode), 127 / 2, PulseLength.Medium).TakeRandom(4),
                    7 => AddressCommandFactory.CreateSinglePulse(RandomColor(state.Mode), 255, 255, PulseLength.Short).TakeRandom(5),
                    8 => AddressCommandFactory.CreateDualPulse(RandomColor(state.Mode), RandomColor(state.Mode), 127 / 2, PulseLength.Short).TakeRandom(5),

                    _ => Enumerable.Empty<OscMessage>()
                };
                await SendAsync(message);
            }
        }

        private static async void TwinkeWithIntensityAsync(int channel, ChannelState state)
        {
            if (state.Intensity > 0)
            {
                var message = CommandFactory.CreateTwinkle((ColorPreset)((state.Select * 2) + 1), state.Intensity * 2);
                await SendAsync(message);
            }
        }

        private static int _address = 0;

        private static async void PulseMuxAsync(int channel, ChannelState state)
        {
            var variant = Variant(channel, state.Select, 6);

            if (PulseOncePer(channel, state.IntensityLog))
            {
                var message = variant switch
                {
                    0 => CommandFactory.CreateRainbowPulse(PulseLength.Long),
                    1 => CommandFactory.CreateSinglePulse(RandomColor(state.Mode), 250, 250, PulseLength.Long),
                    2 => CommandFactory.CreateSingleSpark(RandomColor(state.Mode), 250, 250, PulseLength.Long),
                    3 => CommandFactory.CreateDualPulse(RandomColor(state.Mode), RandomColor(state.Mode), 63, PulseLength.Long),
                    4 => CommandFactory.CreateDualSpark(RandomColor(state.Mode), RandomColor(state.Mode), 63, PulseLength.Long),
                    5 => AddressCommandFactory.CreateSinglePulse(RandomColor(state.Mode), 250, 250, PulseLength.Long).Where((m, index) => (index + (_address % 2)) % 2 == 1),
                    6 => AddressCommandFactory.CreateSinglePulse(RandomColor(state.Mode), 250, 250, PulseLength.Long).Skip(_address++).Take(1),

                    _ => Enumerable.Empty<OscMessage>()
                };
                await SendAsync(message);

                if (variant == 5)
                {
                    _address++;
                }

                if (_address >= 8)
                {
                    _address = 0;
                }
            }
        }

        private static async void ChaseAsync(int channel, ChannelState state, bool up)
        {
            if (state.Select > 15)
            {
                if (PulseOncePer(channel, state.Intensity))
                {
                    var color = RandomColor(state.Mode);

                    var message = CommandFactory.CreateChase(color, state.Select / 16, state.Select < 30 ? 1 : 4, up);
                    await SendAsync(message);
                }
            }
        }

        private static async void VuMeterAsync(int channel, ChannelState state)
        {
            var variant = Variant(channel, state.Select, 11);

            if (variant < 5)
            {
                if (Changed(channel, state.Intensity + state.Select + (int)state.Mode))
                {
                    var message = variant switch
                    {
                        0 => CommandFactory.CreateStrobo(ColorPreset.White, 0),
                        1 => CommandFactory.CreateFire(state.Intensity / 10),
                        2 => CommandFactory.CreateTheaterChase(RandomColor(Kontrol.Channels[channel].Mode), RandomColor(Kontrol.Channels[channel].Mode), 128 - state.Intensity, 1),
                        3 => CommandFactory.CreateTheaterChase(RandomColor(Kontrol.Channels[channel].Mode), RandomColor(Kontrol.Channels[channel].Mode), 128 - state.Intensity, 2),
                        4 => CommandFactory.CreateTheaterChase(RandomColor(Kontrol.Channels[channel].Mode), RandomColor(Kontrol.Channels[channel].Mode), 128 - state.Intensity, 3),
                        5 => CommandFactory.CreateTheaterChase(RandomColor(Kontrol.Channels[channel].Mode), RandomColor(Kontrol.Channels[channel].Mode), 128 - state.Intensity, 6),

                        _ => Enumerable.Empty<OscMessage>()
                    };
                    await SendAsync(message);
                }
            }
            else
            {
                if (PulseOncePer(channel, variant * 45))
                {
                    await SendAsync(CommandFactory.CreateStrobo(ColorPreset.White, 0));

                    var message = CommandFactory.CreateSwipe(RandomColor(Kontrol.Channels[channel].Mode), 10, state.Intensity * 2);

                    await SendAsync(message);
                }
            }
        }

        private static async void SolidAsync(int channel, ChannelState state)
        {
            if (Changed(channel, state.Intensity + state.Select))
            {
                var h = (ColorPreset)((state.Select * 2) + 1);
                var s = state.Mode == Mode.One ? state.Intensity * 2 : 255;
                var v = state.Mode == Mode.Two ? state.Intensity * 2 : 255;

                var message = CommandFactory.CreateSingleSolid(h, s, v);
                await SendAsync(message);
            }
        }

        private static async void TriggersAsync(object state)
        {
            if (Kontrol.Play)
            {
                await SendAsync(CommandFactory.CreateStrobo(RandomColor(Kontrol.Channels[0].Mode), 130));
                Kontrol.Play = false;
            }
            else if (Kontrol.Stop)
            {
                await SendAsync(CommandFactory.CreateStrobo(0, 0));
                Kontrol.Stop = false;
            }

            if (Kontrol.Rec)
            {
                await SendAsync(CommandFactory.CreateSingleSpark(RandomColor(Kontrol.Channels[0].Mode), 255, 255, PulseLength.Long));
            }

            if (Kontrol.Backward)
            {
                await SendAsync(CommandFactory.CreateSinglePulse(RandomColor(Kontrol.Channels[0].Mode), 255, 255, PulseLength.Long));
                Kontrol.Backward = false;
            }

            if (Kontrol.Forward)
            {
                await SendAsync(CommandFactory.CreateDualPulse(RandomColor(Kontrol.Channels[0].Mode), RandomColor(Kontrol.Channels[0].Mode), 127 / 2, PulseLength.Long));
                Kontrol.Forward = false;
            }
        }

        private static bool PulseOncePer(int channel, int delay)
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

        private static bool Changed(int channel, int value)
        {
            if (Value[channel] != value)
            {
                Value[channel] = value;
                return true;
            }

            return false;
        }

        private static (int start, int stop) Range(int input, int length)
        {
            var start = (int)Math.Min(127 - length, Math.Max(0, (double)input * ((127.0 - length) / 127.0)));

            return (start, start + length);
        }

        private static int Variant(int channel, int input, int options)
        {
            var variant = (int)(input * (options / 127.0));

            if (variant != CurrentVariant[channel])
            {
                CurrentVariant[channel] = variant;

                Kontrol.Notify((byte)variant);
            }

            return variant;
        }

        private static PulseLength Pulse(int input) => input < 50 ? PulseLength.Long : PulseLength.Medium;

        private static ColorPreset RandomColor(Mode mode)
        {
            var set = ColorSets[mode];
            if (_currentColor >= set.Length)
            {
                _currentColor = 0;
            }
            return set[_currentColor++];
        }

        private static ColorPreset Rotate(ColorPreset color, ColorPreset degree) => (ColorPreset)(((int)color + (int)degree) % 255);

        private static async Task SendAsync(IEnumerable<OscMessage> messages)
        {
            var senderFsTasks = SenderFs.Select(sender => sender.SendAsync(messages.Where(x => x.Address != "/SP").OptionallyBundle()));
            var senderSPTasks = SenderSP.Select(sender => sender.SendAsync(messages.Where(x => x.Address == "/SP").OptionallyBundle()));

            await Task.WhenAll(senderFsTasks.Union(senderSPTasks));
        }
    }
}
