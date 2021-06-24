using Dispedter.Common.Factories;
using Edt_Kontrol.Effects;
using Edt_Kontrol.Midi;
using Edt_Kontrol.OSC;
using System;
using System.Net;
using System.Threading;
using System.Threading.Tasks;

namespace Edt_Kontrol.Terminal
{
    class Program
    {
        private static Kontrol _kontrol = new Kontrol();

        private static ISender _sender = new UdpSender(IPAddress.Parse("10.0.0.20"), 12345);

        private static CommandFactory _commandFactory = new CommandFactory(new[] { "/F?", "/R?" });

        private static int[] _count = new int[8];
        private static int[] _value = new int[8];

        private static Random _random = new Random();

        private static Timer[] _timers;

        static async Task Main(string[] args)
        {
            await _kontrol.InitAsync();

            _timers = new[]
            {
                new Timer(Channel0, default, 0, 40),
                new Timer(Channel1, default, 20, 40),
                new Timer(Channel7, default, 0, 40),
            };

            await Task.Delay(-1);
        }

        static async void Channel0(object state)
        {
            if (PulseOncePer(0, _kontrol.Channels[0].Intensity))
            {
                var message = _commandFactory.CreateTwinkle((ColorPreset)(_kontrol.Channels[0].Select * 2), Random());
                await _sender.SendAsync(message);
            }
        }
        static async void Channel1(object state)
        {
            if (PulseOncePer(1, _kontrol.Channels[1].Intensity))
            {
                var message = _commandFactory.CreateTwinkle((ColorPreset)(_kontrol.Channels[1].Select * 2), Random());
                await _sender.SendAsync(message);
            }
        }
        static async void Channel7(object state)
        {
            if(Changed(7, _kontrol.Channels[7].Intensity))
            {
                var message = _commandFactory.CreateStrobo((ColorPreset)(_kontrol.Channels[7].Select * 2), _kontrol.Channels[7].Intensity * 2);
                await _sender.SendAsync(message);
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

        private static int Random()
        {
            return (int)(255 * _random.NextDouble());
        }
    }
}
