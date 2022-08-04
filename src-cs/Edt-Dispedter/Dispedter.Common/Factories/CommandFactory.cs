using Dispedter.Common.OSC;
using Dispedter.Common.OSCArduino;
using System;
using System.Collections.Generic;
using System.Linq;

namespace Dispedter.Common.Factories
{
    public class CommandFactory
    {
        private readonly string[] _addresses;

        public CommandFactory(string[] addresses)
        {
            _addresses = addresses;
        }

        public IEnumerable<OscMessage> CreateTestMessage(int i)
        {
            return new[] { new OscMessage("/TD", i, 0) };
        }

        public IEnumerable<OscMessage> CreateSingleSolid(ColorPreset h, int s, int v)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.SingleSolid, 0, 127, (int)h, s, v));
        }

        public IEnumerable<OscMessage> CreateSinglePulse(ColorPreset h, int s, int v, PulseLength p)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.SinglePulse, 0, 127, (int)h, s, v, (int)p));
        }

        public IEnumerable<OscMessage> CreateSinglePulse(int start, int end, ColorPreset h, int s, int v, PulseLength p)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.SinglePulse, start, end, (int)h, s, v, (int)p));
        }

        public IEnumerable<OscMessage> CreateSingleSpark(ColorPreset h, int s, int v, PulseLength p)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.SingleSpark, 0, 127, (int)h, s, v, (int)p));
        }

        public IEnumerable<OscMessage> CreateDualSolid(ColorPreset h1, ColorPreset h2, int percentage)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.DualSolid, 0, 127, (int)h1, (int)h2, percentage));
        }

        public IEnumerable<OscMessage> CreateDualPulse(ColorPreset h1, ColorPreset h2, int percentage, PulseLength p)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.DualPulse, 0, 127, (int)h1, (int)h2, percentage, (int)p));
        }

        public IEnumerable<OscMessage> CreateDualSpark(ColorPreset h1, ColorPreset h2, int percentage, PulseLength p)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.DualSpark, 0, 127, (int)h1, (int)h2, percentage, (int)p));
        }

        public IEnumerable<OscMessage> CreateRainbowSolid()
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.RainbowSolid, 0, 127, 0, 127));
        }

        public IEnumerable<OscMessage> CreateRainbowSolid(int percentage)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.RainbowSolid, 0, percentage, 0, 255));
        }

        public IEnumerable<OscMessage> CreateRainbowPulse(PulseLength p)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.RainbowPulse, 0, 127, 0, 127, (int)p));
        }

        public IEnumerable<OscMessage> CreateRainbowSpark(PulseLength p)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.RainbowSpark, 0, 127, 0, 127, (int)p));
        }

        public IEnumerable<OscMessage> CreateVuMeter(int intensity)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.VUMeter, 0, 127, 63, (int)ColorPreset.Green, 128, intensity));
        }

        public IEnumerable<OscMessage> CreateTwinkle(ColorPreset h, int intensity)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.Twinkle, 0, 127, (int)h, intensity));
        }

        public IEnumerable<OscMessage> CreateStrobo(ColorPreset h, int speed)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.Strobo, (int)h, speed));
        }

        public IEnumerable<OscMessage> CreateBerserk()
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.Berserk));
        }

        public IEnumerable<OscMessage> CreateChase(ColorPreset h, int speed, int fadeSpeed, bool up)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.Chase, (int)h, speed, fadeSpeed, up ? 1 : 0));
        }

        public IEnumerable<OscMessage> CreateChaseStill(ColorPreset h, int length)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.ChaseStill, (int)h, length));
        }

        public IEnumerable<OscMessage> CreateBash(ColorPreset h, int intensity)
        {
            return _addresses.Select(a => new OscMessage(a, (int)Command.Bash, (int)h, intensity));
        }

        public IEnumerable<OscMessage> CreateRainbowUsingAddresses()
        {
            return _addresses.Select((a, i) => new OscMessage(a, (int)Command.SingleSolid, 0, 127, (int)(i * (255.0 / _addresses.Count())), 255, 254));
        }

        public IEnumerable<OscMessage> CreateSolidPulseUsingAddresses(Func<ColorPreset> h)
        {
            var parts = 4;
            var length = 128 / parts;

            return _addresses.SelectMany((a, i) =>
                Enumerable.Range(0, parts)
                    .Select(x => new OscMessage(a, (int)Command.SinglePulse, x * (length), (x * length) + length - 1, (int)h(), 255, 254, 0)));
        }

        public IEnumerable<OscMessage> CreateChaseUsingSomeAddresses(ColorPreset h, int amount, int speed, int fadeSpeed, bool up)
        {
            return _addresses
                .OrderBy(x => Guid.NewGuid())
                .Take(amount)
                .Select(a => new OscMessage(a, (int)Command.Chase, (int)h, speed, fadeSpeed, up ? 1 : 0));
        }

        public IEnumerable<OscMessage> CreateUTPPinout()
        {
            var colors = new[]
            {
                new [] { ColorPreset.Yellow, ColorPreset.White},
                new [] { ColorPreset.Yellow},
                new [] { ColorPreset.White, ColorPreset.Green },
                new [] { ColorPreset.Blue},
                new [] { ColorPreset.Blue, ColorPreset.White},
                new [] { ColorPreset.Green},
                new [] { ColorPreset.White, ColorPreset.Amber},
                new [] { ColorPreset.Amber},
            };

            return _addresses
                .SelectMany((a, i) =>
                {
                    var color = colors[i];

                    if (color.Length == 1)
                    {
                        return new[]
                        {
                            new OscMessage(a, (int)Command.SinglePulse, 0, 127, (int)color[0], 255, 254, 1)
                        };
                    }
                    else
                    {
                        return new[]
                        {
                            new OscMessage(a, (int)Command.SinglePulse, 0, 32,(int)color[0], 255, 254, 1),
                            new OscMessage(a, (int)Command.SinglePulse, 32, 64, (int)color[1], 255, 254, 1),
                            new OscMessage(a, (int)Command.SinglePulse, 64, 96, (int)color[0], 255, 254, 1),
                            new OscMessage(a, (int)Command.SinglePulse, 96, 127, (int)color[1], 255, 254, 1),
                        };
                    }
                });
        }

        public IEnumerable<OscMessage> CreateTwinkleUsingAddresses(Func<ColorPreset> h)
        {
            var parts = 4;

            var r = new Random();

            return _addresses.SelectMany((a, i) =>
                Enumerable.Range(0, parts)
                    .Select(x => r.Next(0, 126))
                    .Select(x => new OscMessage(a, (int)Command.SinglePulse, x, x + 1, (int)h(), 255, 255, (int)PulseLength.Long)));
        }

        public IEnumerable<OscMessage> ClearDMX()
        {
            return _addresses.Select((a, i) => DmxMessageStub(a, 0, 0, false, true)); // new OscMessage(a, 254, 1, 0, 0, 0));
        }

        public IEnumerable<OscMessage> RestartDMX()
        {
            return _addresses.Select((a, i) => DmxMessageStub(a, 0, 0, true, false)); // new OscMessage(a, 254, 0, 1, 0, 0));
        }

        public IEnumerable<OscMessage> ProgramDmxDevice(int type, int address, double maximumBrightness, double minimumBrightness)
        {
            return _addresses.Select((a, i) =>
            {
                var msg = DmxMessageStub(a, type, address, false, false);

                msg.Arguments.Add((int)(maximumBrightness * 255));
                msg.Arguments.Add((int)(minimumBrightness * 255));

                return msg;
            });
        }

        private OscMessage DmxMessageStub(string address, int dmxType, int dmxAddress, bool reset, bool clear)
        {
            var address256 = dmxAddress >= 256;

            var firstInt = 0;

            if (clear)
            {
                firstInt |= 0b0000_0100;
            }

            if (reset)
            {
                firstInt |= 0b0000_0010;
            }

            if (address256)
            {
                firstInt |= 0b0000_0001;
            }

            return new OscMessage(address, 254, firstInt, dmxAddress, dmxType);
        }
    }
}
