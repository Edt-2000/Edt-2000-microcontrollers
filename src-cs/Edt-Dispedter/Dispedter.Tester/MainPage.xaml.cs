﻿using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using Dispedter.Common.DMX;
using Dispedter.Common.Extensions;
using Dispedter.Common.Factories;
using Dispedter.Common.Managers;
using Dispedter.Common.OSC;
using Dispedter.Common.OSCArduino;
using Windows.Storage;
using Windows.System;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace Dispedter.Tester
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private readonly CommandFactory _commandFactory = new CommandFactory(new[] { "/F?", "/SP", "/R?" });
        private readonly CommandFactory _specialCommandFactory = new CommandFactory(new[] { "/?1", "/?2", "/?3", "/?4", "/?5", "/?6", "/?7", "/?8" });
        private readonly ListenerManager _listenerManager = new ListenerManager(detectUsb: false);
        private readonly SenderManager _senderManager = new SenderManager(detectUsb: false, udpDestinations: new[]
        {
            // TODO: fix

            //IPAddress.Parse("127.0.0.1")});
            /* OLD fastled: IPAddress.Parse("10.0.0.20"),*/ 
            /* New fastled1: */ IPAddress.Parse("10.0.0.21"), 
            /* New fastled2: */ IPAddress.Parse("10.0.0.22"), 
            /* New DMX unit: */ IPAddress.Parse("10.0.0.30"), 
            /* New Spectacle: */ IPAddress.Parse("10.0.0.99") });
        /* OLD RGB IPAddress.Parse("10.0.0.40"),*/
        ///* Smoke */ IPAddress.Parse("10.0.0.165") });

        private Dictionary<Mode, Dictionary<VirtualKey, Func<IEnumerable<OscMessage>>>> _commandMapping = new Dictionary<Mode, Dictionary<VirtualKey, Func<IEnumerable<OscMessage>>>>();
        private Dictionary<Mode, Dictionary<VirtualKey, Func<int, (int delay, IEnumerable<OscMessage> command)>>> _proceduralCommandMapping = new Dictionary<Mode, Dictionary<VirtualKey, Func<int, (int delay, IEnumerable<OscMessage> command)>>>();

        private ObservableCollection<DmxDevice> _dmxDevices;
        private ObservableCollection<DmxType> _dmxTypes;
        private ObservableCollection<int> _dmxAddresses;
        private DmxConfig _dmxConfig;

        private static readonly Random R = new Random();

        private Mode _mode;
        private enum Mode
        {
            Default = 0,
            Partial = 1,
            Chase = 2
        }

        private ColorSetMode _colorSetMode;
        private enum ColorSetMode
        {
            RedWhite = 0,
            RedBlue = 1,
            TurquoisePink = 2,
            Pink = 3,
            GreenAmber = 4,
            GreenWhite = 5,
            RedAmber = 6,
            All = 7
        }

        private static int _currentColor = 0;
        private static Dictionary<int, ColorPreset[]> _colorSets = new Dictionary<int, ColorPreset[]>()
        {
            [0] = new[] { ColorPreset.Red, ColorPreset.White },
            [1] = new[] { ColorPreset.Red, ColorPreset.Blue },
            [2] = new[] { ColorPreset.Turquoise, ColorPreset.Pink },
            [3] = new[] { ColorPreset.Pink },
            [4] = new[] { ColorPreset.Green, ColorPreset.Amber },
            [5] = new[] { ColorPreset.Green, ColorPreset.White },
            [6] = new[] { ColorPreset.Red, ColorPreset.Amber },
        };

        private Task _senderTask;
        private Task _listenerTask;

        private DateTime _previousOut = DateTime.UtcNow;
        private List<string> _outHistory = new List<string>();
        private DateTime _previousIn = DateTime.UtcNow;
        private List<string> _inHistory = new List<string>();

        enum CommandDirection
        {
            In,
            Out
        }

        public MainPage()
        {
            _colorSets[7] = Enumerable.Range(0, 255).Cast<ColorPreset>().OrderBy(x => Guid.NewGuid()).ToArray();

            _dmxDevices = new ObservableCollection<DmxDevice>();
            _dmxConfig = new DmxConfig(_dmxDevices);
            _dmxTypes = new ObservableCollection<DmxType>(_dmxConfig.Types);
            _dmxAddresses = new ObservableCollection<int>(Enumerable.Range(1, 512));

            InitializeComponent();
            InitializeListeners();

            _senderTask = _senderManager.ManageDevicesAsync();
            _listenerTask = _listenerManager.ManageDevicesAsync();

            InitializeCommandMappings();

            Window.Current.CoreWindow.KeyDown += async (s, e) =>
            {
                var key = e.VirtualKey;

                KeyCode.Text = $"{(int)key}";

                if (e.VirtualKey == VirtualKey.Control)
                {
                    _mode++;

                    if ((int)_mode >= _commandMapping.Count)
                    {
                        _mode = 0;
                    }

                    CommandMode.Text = _mode.ToString();
                }
                else if (e.VirtualKey == (VirtualKey)192)
                {
                    _colorSetMode++;

                    if ((int)_colorSetMode >= _colorSets.Count)
                    {
                        _colorSetMode = 0;
                    }

                    ColorMode.Text = _colorSetMode.ToString();
                }
                else
                {
                    await SendCommandAsync(key);
                }
            };
        }

        private void InitializeListeners()
        {
            _listenerManager.AttachEventHandler(async (IListener listener, OscEventArgs args) =>
            {
                await LogCommandAsync(CommandDirection.In, new[] { args.GetOscPacket() as OscMessage });
            });
        }

        #region LED
        private async Task SendCommandAsync(VirtualKey key)
        {
            if (!_senderManager.Senders?.Any() ?? false)
            {
                return;
            }

            if (_commandMapping[_mode].TryGetValue(key, out var commandGenerator))
            {
                var commands = commandGenerator();

                await Task.WhenAll(_senderManager.Senders.Select(sender => sender.SendAsync(commands.OptionallyBundle())));

                await LogCommandAsync(CommandDirection.Out, commands);
            }
            else if (_proceduralCommandMapping[_mode].TryGetValue(key, out var proceduralCommandGenerator))
            {
                var i = 0;
                do
                {
                    var (delay, command) = proceduralCommandGenerator(i);

                    await Task.WhenAll(_senderManager.Senders.Select(sender => sender.SendAsync(command.OptionallyBundle())));

                    await LogCommandAsync(CommandDirection.Out, command);

                    await Task.Delay(delay);

                } while (++i < 100);
            }
            else
            {
                ;
            }
        }

        private async Task LogCommandAsync(CommandDirection commandDirection, IEnumerable<OscMessage> messages)
        {
            if (commandDirection == CommandDirection.Out)
            {
                foreach (var message in messages)
                {
                    var delta = DateTime.UtcNow - _previousOut;
                    _previousOut = DateTime.UtcNow;

                    if (_outHistory.Count > 40)
                    {
                        _outHistory.RemoveAt(0);
                    }

                    _outHistory.Add($"+{delta.TotalSeconds:0.0000} - {message.Address} - {string.Join(", ", message.Arguments)}");
                }

                OutCommandHistory.Text = string.Join("\r\n", _outHistory);
            }
            else
            {
                foreach (var message in messages)
                {
                    var delta = DateTime.UtcNow - _previousIn;
                    _previousIn = DateTime.UtcNow;
                    var deltaOutIn = _previousIn - _previousOut;

                    if (_inHistory.Count > 40)
                    {
                        _inHistory.RemoveAt(0);
                    }

                    _inHistory.Add($"+{delta.TotalSeconds:0.0000} - {message.Address} - {string.Join(", ", message.Arguments)} -- <+{deltaOutIn.TotalSeconds:0.0000}>");
                }

                var data = string.Join("\r\n", _inHistory);

                await Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () =>
                {
                    InCommandHistory.Text = data;
                });
            }
        }

        private void InitializeCommandMappings()
        {
            InitializeDefaultCommandMapping();
            InitializeDefaultProceduralCommandMapping();

            InitializePartialCommandMapping();
            InitializePartialProceduralCommandMapping();
        }

        private void InitializeDefaultCommandMapping()
        {
            var i = (byte)0;
            var strobo = (byte)127;
            var color = (byte)0;
            var smoke = (byte)120;

            var test = 0;

            _commandMapping.Add(Mode.Default, new Dictionary<VirtualKey, Func<IEnumerable<OscMessage>>>
            {
                {
                    VirtualKey.PageUp, () =>
                    {
                        smoke -= 5;

                        SmokeTime.Text = smoke.ToString();

                        return _commandFactory.CreateSmokeMessage(smoke);
                    }
                },
                {
                    VirtualKey.PageDown, () =>
                    {
                        smoke += 5;

                        SmokeTime.Text = smoke.ToString();

                        return _commandFactory.CreateSmokeMessage(smoke);
                    }
                },
                { VirtualKey.Back, () => _commandFactory.CreateTestMessage(++test) },
                {
                    VirtualKey.Up, () =>
                    {
                        color++;

                        ColorIndex.Text = color.ToString();
                        ColorIndex.Foreground = new SolidColorBrush(ColorFromHSV(color, 1.0, 1.0));

                        return _commandFactory.CreateSingleSolid((ColorPreset)color, 255, 254);
                    }
                },
                {
                    VirtualKey.Down, () =>
                    {
                        color--;

                        ColorIndex.Text = color.ToString();
                        ColorIndex.Foreground = new SolidColorBrush(ColorFromHSV(color, 1.0, 1.0));

                        return _commandFactory.CreateSingleSolid((ColorPreset)color, 255, 254);
                    }
                },
                {
                    VirtualKey.Right,
                    () => {
                        strobo++;

                        StroboSpeed.Text = strobo.ToString();

                        return Enumerable.Empty<OscMessage>();
                    }
                },
                {
                    VirtualKey.Left,
                    () => {
                        strobo--;

                        StroboSpeed.Text = strobo.ToString();

                        return Enumerable.Empty<OscMessage>();
                    }
                },

                { VirtualKey.Q, () => _commandFactory.CreateSingleSolid(ColorPreset.Red, 255, 20) },
                { VirtualKey.W, () => _commandFactory.CreateSingleSolid(ColorPreset.Red, 255, 40) },
                { VirtualKey.E, () => _commandFactory.CreateSingleSolid(ColorPreset.Red, 255, 60) },
                { VirtualKey.R, () => _commandFactory.CreateSingleSolid(ColorPreset.Red, 255, 80) },

                { VirtualKey.T, () => _commandFactory.CreateRainbowSpark(PulseLength.Medium) },
                { VirtualKey.Y, () => _commandFactory.CreateRainbowPulse(PulseLength.Short) },

                { VirtualKey.Number1, () => _commandFactory.CreateSingleSolid(ColorPreset.White, 255, 254) },
                { VirtualKey.Number2, () => _commandFactory.CreateSingleSolid(ColorPreset.Pink, 255, 254) },
                { VirtualKey.Number3, () => _commandFactory.CreateSingleSolid(ColorPreset.Red, 255, 254) },
                { VirtualKey.Number4, () => _commandFactory.CreateSingleSolid(ColorPreset.Amber, 255, 254) },
                { VirtualKey.Number5, () => _commandFactory.CreateSingleSolid(ColorPreset.Yellow, 255, 254) },
                { VirtualKey.Number6, () => _commandFactory.CreateSingleSolid(ColorPreset.Lime, 255, 254) },
                { VirtualKey.Number7, () => _commandFactory.CreateSingleSolid(ColorPreset.Green, 255, 254) },
                { VirtualKey.Number8, () => _commandFactory.CreateSingleSolid(ColorPreset.SeaGreen, 255, 254) },
                { VirtualKey.Number9, () => _commandFactory.CreateSingleSolid(ColorPreset.Turquoise, 255, 254) },
                { VirtualKey.Number0, () => _commandFactory.CreateSingleSolid(ColorPreset.Blue, 255, 254) },

                { VirtualKey.NumberPad1, () => _commandFactory.CreateDualSolid(ColorPreset.Red, ColorPreset.Blue, 25) },
                { VirtualKey.NumberPad2, () => _commandFactory.CreateDualSolid(ColorPreset.Red, ColorPreset.Blue, 50) },
                { VirtualKey.NumberPad3, () => _commandFactory.CreateDualSolid(ColorPreset.Red, ColorPreset.Blue, 75) },
                { VirtualKey.NumberPad4, () => _commandFactory.CreateDualSolid(ColorPreset.Red, ColorPreset.Blue, 100) },
                { VirtualKey.NumberPad5, () => _commandFactory.CreateDualSolid(ColorPreset.Red, ColorPreset.Blue, 125) },
                { VirtualKey.NumberPad6, () => _commandFactory.CreateDualSolid(ColorPreset.Red, ColorPreset.Blue, 150) },
                { VirtualKey.NumberPad7, () => _commandFactory.CreateDualSolid(ColorPreset.Red, ColorPreset.Blue, 175) },
                { VirtualKey.NumberPad8, () => _commandFactory.CreateDualSolid(ColorPreset.Red, ColorPreset.Blue, 200) },
                { VirtualKey.NumberPad9, () => _commandFactory.CreateDualSolid(ColorPreset.Red, ColorPreset.Blue, 225) },

                { VirtualKey.F1, () => _commandFactory.CreateDualSpark(ColorPreset.Red, ColorPreset.White, 127, PulseLength.Medium) },
                { VirtualKey.F2, () => _commandFactory.CreateDualSpark(ColorPreset.Red, ColorPreset.Blue, 127, PulseLength.Medium) },
                { VirtualKey.F3, () => _commandFactory.CreateDualSpark(ColorPreset.Turquoise, ColorPreset.Pink, 127, PulseLength.Medium) },
                { VirtualKey.F4, () => _commandFactory.CreateDualSpark(ColorPreset.Green, ColorPreset.Amber, 127, PulseLength.Medium) },
                { VirtualKey.F5, () => _commandFactory.CreateDualSpark(ColorPreset.Red, ColorPreset.White, 63, PulseLength.Medium) },
                { VirtualKey.F6, () => _commandFactory.CreateDualSpark(ColorPreset.Red, ColorPreset.Blue, 63, PulseLength.Medium) },
                { VirtualKey.F7, () => _commandFactory.CreateDualSpark(ColorPreset.Turquoise, ColorPreset.Pink, 63, PulseLength.Medium) },
                { VirtualKey.F8, () => _commandFactory.CreateDualSpark(ColorPreset.Green, ColorPreset.Amber, 63, PulseLength.Medium) },
                { VirtualKey.F9, () => _commandFactory.CreateDualSpark(ColorPreset.Red, ColorPreset.White, 192, PulseLength.Medium) },
                { VirtualKey.F10, () =>_commandFactory.CreateDualSpark(ColorPreset.Red, ColorPreset.Blue, 192, PulseLength.Medium) },
                { VirtualKey.F11, () =>_commandFactory.CreateDualSpark(ColorPreset.Turquoise, ColorPreset.Pink, 192, PulseLength.Medium) },
                { VirtualKey.F12, () =>_commandFactory.CreateDualSpark(ColorPreset.Green, ColorPreset.Amber, 192, PulseLength.Medium) },

                { VirtualKey.G, () => _commandFactory.CreateSingleSolid(0, 0, 255) },

                { VirtualKey.U, () => _commandFactory.CreateSingleSpark(ColorPreset.Red, 255, 254, PulseLength.Medium) },
                { VirtualKey.I, () => _commandFactory.CreateSingleSpark(ColorPreset.Blue, 255, 254, PulseLength.Medium) },
                { VirtualKey.O, () => _commandFactory.CreateSingleSpark(ColorPreset.Pink, 255, 254, PulseLength.Medium) },
                { VirtualKey.P, () => _commandFactory.CreateSingleSpark(ColorPreset.Green, 255, 254, PulseLength.Medium) },

                { VirtualKey.H, () => _commandFactory.CreateSinglePulse(ColorPreset.Red, 255, 254, PulseLength.Medium) },
                { VirtualKey.J, () => _commandFactory.CreateSinglePulse(ColorPreset.Blue, 255, 254, PulseLength.Medium) },
                { VirtualKey.K, () => _commandFactory.CreateSinglePulse(ColorPreset.Pink, 255, 254, PulseLength.Medium) },
                { VirtualKey.L, () => _commandFactory.CreateSinglePulse(ColorPreset.Green, 255, 254, PulseLength.Medium) },

                { VirtualKey.B, () => _commandFactory.CreateSinglePulse(ColorPreset.Red, 255, 254, PulseLength.Long) },
                { VirtualKey.N, () => _commandFactory.CreateSinglePulse(ColorPreset.Blue, 255, 254, PulseLength.Long) },
                { VirtualKey.M, () => _commandFactory.CreateSinglePulse(ColorPreset.Pink, 255, 254, PulseLength.Long) },
                { (VirtualKey)188, () => _commandFactory.CreateSinglePulse(ColorPreset.Green, 255, 254, PulseLength.Long) }, // comma

                { VirtualKey.Space, () => _commandFactory.CreateStrobo(RandomColor(), strobo)},
                { VirtualKey.Escape, () => _commandFactory.CreateStrobo(0, 0) },

                { VirtualKey.Z, () => _commandFactory.CreateTwinkle(RandomColor(), Random()) },
                { VirtualKey.Shift, () => _commandFactory.CreateTwinkle(ColorPreset.White, Random()) },
                { VirtualKey.X, () => _specialCommandFactory.CreateUTPPinout() },
                { VirtualKey.CapitalLock, () => _specialCommandFactory.CreateRainbowUsingAddresses() },

                { VirtualKey.C, () => _commandFactory.CreateChase(RandomColor(), 1, 1, true) },
                { VirtualKey.V, () => _commandFactory.CreateChase(RandomColor(), 1, 1, false) },

                { (VirtualKey)187, () => _commandFactory.CreateChase(RandomColor(), 3, 32, true) },
                { (VirtualKey)189, () => _commandFactory.CreateChase(RandomColor(), 3, 32, false) },

                { (VirtualKey)186, () =>
                {
                    RandomColor();
                    return _commandFactory.CreateTheaterChase(RandomColor(), RandomColor(), 3, Random() / 42);
                } }, // ;
                { (VirtualKey)222, () =>
                {
                    RandomColor();
                    return _commandFactory.CreateTheaterChase(RandomColor(), RandomColor(), 10, Random() / 42);
                } }, // '

                { (VirtualKey)190, () => _commandFactory.CreateSwipe(RandomColor(), 5, Random()) }, // .
                { (VirtualKey)191, () => _commandFactory.CreateFire(3) }, // /

                { (VirtualKey)220, () => _specialCommandFactory.CreateTwinkleUsingAddresses(RandomColor) }, // \
                { (VirtualKey)219, () => _specialCommandFactory.CreateChaseUsingSomeAddresses(RandomColor(), 2, 1, 1, true) }, // [
                { (VirtualKey)221, () => _specialCommandFactory.CreateChaseUsingSomeAddresses(RandomColor(), 2, 1, 1, false) }, // ]
            });
        }

        private void InitializePartialCommandMapping()
        {
            _commandMapping.Add(Mode.Partial, new Dictionary<VirtualKey, Func<IEnumerable<OscMessage>>>
            {
                { VirtualKey.Number1, () => _commandFactory.CreateSinglePulse(0, 12, RandomColor(), 255, 254, PulseLength.Long) },
                { VirtualKey.Number2, () => _commandFactory.CreateSinglePulse(12, 24, RandomColor(), 255, 254, PulseLength.Long) },
                { VirtualKey.Number3, () => _commandFactory.CreateSinglePulse(24, 36, RandomColor(), 255, 254, PulseLength.Long) },
                { VirtualKey.Number4, () => _commandFactory.CreateSinglePulse(36, 48, RandomColor(), 255, 254, PulseLength.Long) },
                { VirtualKey.Number5, () => _commandFactory.CreateSinglePulse(48, 60, RandomColor(), 255, 254, PulseLength.Long) },
                { VirtualKey.Number6, () => _commandFactory.CreateSinglePulse(60, 72, RandomColor(), 255, 254, PulseLength.Long) },
                { VirtualKey.Number7, () => _commandFactory.CreateSinglePulse(72, 84, RandomColor(), 255, 254, PulseLength.Long) },
                { VirtualKey.Number8, () => _commandFactory.CreateSinglePulse(84, 96, RandomColor(), 255, 254, PulseLength.Long) },
                { VirtualKey.Number9, () => _commandFactory.CreateSinglePulse(96, 108, RandomColor(), 255, 254, PulseLength.Long) },
                { VirtualKey.Number0, () => _commandFactory.CreateSinglePulse(108, 127, RandomColor(), 255, 254, PulseLength.Long) },

                { VirtualKey.Q, () => _commandFactory.CreateSinglePulse(0, 12, ColorPreset.Red, 255, 254, PulseLength.Long) },
                { VirtualKey.W, () => _commandFactory.CreateSinglePulse(12, 24, ColorPreset.Red, 255, 254, PulseLength.Long) },
                { VirtualKey.E, () => _commandFactory.CreateSinglePulse(24, 36, ColorPreset.Red, 255, 254, PulseLength.Long) },
                { VirtualKey.R, () => _commandFactory.CreateSinglePulse(36, 48, ColorPreset.Red, 255, 254, PulseLength.Long) },
                { VirtualKey.T, () => _commandFactory.CreateSinglePulse(48, 60, ColorPreset.Red, 255, 254, PulseLength.Long) },
                { VirtualKey.Y, () => _commandFactory.CreateSinglePulse(60, 72, ColorPreset.Red, 255, 254, PulseLength.Long) },
                { VirtualKey.U, () => _commandFactory.CreateSinglePulse(72, 84, ColorPreset.Red, 255, 254, PulseLength.Long) },
                { VirtualKey.I, () => _commandFactory.CreateSinglePulse(84, 96, ColorPreset.Red, 255, 254, PulseLength.Long) },
                { VirtualKey.O, () => _commandFactory.CreateSinglePulse(96, 108, ColorPreset.Red, 255, 254, PulseLength.Long) },
                { VirtualKey.P, () => _commandFactory.CreateSinglePulse(108, 127, ColorPreset.Red, 255, 254, PulseLength.Long) },

                { VirtualKey.A, () => _commandFactory.CreateSinglePulse(0, 12, ColorPreset.Blue, 255, 254, PulseLength.Long) },
                { VirtualKey.S, () => _commandFactory.CreateSinglePulse(12, 24, ColorPreset.Blue, 255, 254, PulseLength.Long) },
                { VirtualKey.D, () => _commandFactory.CreateSinglePulse(24, 36, ColorPreset.Blue, 255, 254, PulseLength.Long) },
                { VirtualKey.F, () => _commandFactory.CreateSinglePulse(36, 48, ColorPreset.Blue, 255, 254, PulseLength.Long) },
                { VirtualKey.G, () => _commandFactory.CreateSinglePulse(48, 60, ColorPreset.Blue, 255, 254, PulseLength.Long) },
                { VirtualKey.H, () => _commandFactory.CreateSinglePulse(60, 72, ColorPreset.Blue, 255, 254, PulseLength.Long) },
                { VirtualKey.J, () => _commandFactory.CreateSinglePulse(72, 84, ColorPreset.Blue, 255, 254, PulseLength.Long) },
                { VirtualKey.K, () => _commandFactory.CreateSinglePulse(84, 96, ColorPreset.Blue, 255, 254, PulseLength.Long) },
                { VirtualKey.L, () => _commandFactory.CreateSinglePulse(96, 108, ColorPreset.Blue, 255, 254, PulseLength.Long) },
                { (VirtualKey)186, () => _commandFactory.CreateSinglePulse(108, 127, ColorPreset.Blue, 255, 254, PulseLength.Long) },

                { VirtualKey.Z, () => _commandFactory.CreateSinglePulse(0, 12, ColorPreset.Pink, 255, 254, PulseLength.Long) },
                { VirtualKey.X, () => _commandFactory.CreateSinglePulse(12, 24, ColorPreset.Pink, 255, 254, PulseLength.Long) },
                { VirtualKey.C, () => _commandFactory.CreateSinglePulse(24, 36, ColorPreset.Pink, 255, 254, PulseLength.Long) },
                { VirtualKey.V, () => _commandFactory.CreateSinglePulse(36, 48, ColorPreset.Pink, 255, 254, PulseLength.Long) },
                { VirtualKey.B, () => _commandFactory.CreateSinglePulse(48, 60, ColorPreset.Pink, 255, 254, PulseLength.Long) },
                { VirtualKey.N, () => _commandFactory.CreateSinglePulse(60, 72, ColorPreset.Pink, 255, 254, PulseLength.Long) },
                { VirtualKey.M, () => _commandFactory.CreateSinglePulse(72, 84, ColorPreset.Pink, 255, 254, PulseLength.Long) },
                { (VirtualKey)188, () => _commandFactory.CreateSinglePulse(84, 96, ColorPreset.Pink, 255, 254, PulseLength.Long) },
                { (VirtualKey)190, () => _commandFactory.CreateSinglePulse(96, 108, ColorPreset.Pink, 255, 254, PulseLength.Long) },
                { (VirtualKey)191, () => _commandFactory.CreateSinglePulse(108, 127, ColorPreset.Pink, 255, 254, PulseLength.Long) },
            });
        }

        private void InitializeDefaultProceduralCommandMapping()
        {
            _proceduralCommandMapping.Add(Mode.Default, new Dictionary<VirtualKey, Func<int, (int, IEnumerable<OscMessage>)>>
            {
                { VirtualKey.A, (i) => (10, _commandFactory.CreateVuMeter(Wave(i))) },
                { VirtualKey.S, (i) => (20, _commandFactory.CreateTwinkle(ColorPreset.Red, Wave(i))) },
                { VirtualKey.D, (i) => (5, _commandFactory.CreateTwinkle(RandomColor(), Random())) },
                { VirtualKey.F, (i) => (5, _commandFactory.CreateSingleSolid((ColorPreset)Clamp(i / 100.0), 255, 254)) }
            });
        }

        private void InitializePartialProceduralCommandMapping()
        {
            _proceduralCommandMapping.Add(Mode.Partial, new Dictionary<VirtualKey, Func<int, (int, IEnumerable<OscMessage>)>>
            {

            });
        }

        private static int Wave(int i)
        {
            return (int)(Math.Sin(i / 100.0 * Math.PI) * 255);
        }
        private ColorPreset RandomColor()
        {
            var set = _colorSets[(int)_colorSetMode];
            if (_currentColor >= set.Length)
            {
                _currentColor = 0;
            }
            return set[_currentColor++];
        }

        private static int Random()
        {
            return Clamp(R.NextDouble());
        }
        private static int Clamp(double i)
        {
            return (int)(i * 255);
        }

        public static Color ColorFromHSV(double hue, double saturation, double value)
        {
            var baseValue = 60 * (255.0 / 360.0);

            var hi = Convert.ToInt32(Math.Floor(hue / baseValue)) % 6;
            var f = (hue / baseValue) - Math.Floor(hue / baseValue);

            value = value * 255;
            var v = Convert.ToByte(value);
            var p = Convert.ToByte(value * (1 - saturation));
            var q = Convert.ToByte(value * (1 - (f * saturation)));
            var t = Convert.ToByte(value * (1 - ((1 - f) * saturation)));

            if (hi == 0)
            {
                return Color.FromArgb(255, v, t, p);
            }
            else if (hi == 1)
            {
                return Color.FromArgb(255, q, v, p);
            }
            else if (hi == 2)
            {
                return Color.FromArgb(255, p, v, t);
            }
            else if (hi == 3)
            {
                return Color.FromArgb(255, p, q, v);
            }
            else if (hi == 4)
            {
                return Color.FromArgb(255, t, p, v);
            }
            else
            {
                return Color.FromArgb(255, v, p, q);
            }
        }

        #endregion

        #region DMX

        private async void DmxLoadButton_Click(object sender, RoutedEventArgs e)
        {
            var tag = (sender as Button).Tag as string;

            try
            {
                var fileName = GetFileName(tag);

                var folder = await GetStorageFolderAsync();

                if (folder == null)
                {
                    return;
                }

                var fileContents = await GetReadFileContentsAsync(fileName, folder);

                _dmxConfig.ReadConfig(fileContents);
            }
            catch
            {
                _dmxConfig.RemoveAllDevices();
            }
        }

        private async void DmxDownloadSaveButton_Click(object sender, RoutedEventArgs e)
        {
            var tag = (sender as Button).Tag as string;
            try
            {
                var fileName = GetFileName(tag);

                var folder = await GetStorageFolderAsync();

                if (folder != null)
                {
                    var fileContents = _dmxConfig.WriteConfig();

                    await WriteStreamToFileAsync(fileName, folder, fileContents);
                }
            }
            catch
            {

            }

            var command = _dmxConfig.GenerateOscConfig(tag);

            foreach (var oscSender in _senderManager.Senders)
            {
                await oscSender.SendAsync(command);
            }

            await LogCommandAsync(CommandDirection.Out, command);
        }

        private static string GetFileName(string tag)
        {
            return $"edt-{tag.Replace("/", "")}.edt";
        }

        private static async Task<StorageFolder> GetStorageFolderAsync()
        {
            StorageFolder folder = null;
            try
            {
                folder = await ApplicationData.Current.LocalFolder.GetFolderAsync("Edt-2000").AsTask();
            }
            catch
            {
                folder = await ApplicationData.Current.LocalFolder.CreateFolderAsync("Edt-2000").AsTask();
            }

            return folder;
        }

        private static async Task<string> GetReadFileContentsAsync(string fileName, StorageFolder folder)
        {
            var fileHandle = await folder.GetFileAsync(fileName).AsTask();

            return await FileIO.ReadTextAsync(fileHandle).AsTask();
        }

        private static async Task WriteStreamToFileAsync(string fileName, StorageFolder folder, string fileContentString)
        {
            StorageFile fileHandle;
            try
            {
                fileHandle = await folder.GetFileAsync(fileName).AsTask();
            }
            catch
            {
                fileHandle = await folder.CreateFileAsync(fileName).AsTask();
            }

            await FileIO.WriteTextAsync(fileHandle, fileContentString).AsTask();
        }

        private void AddDeviceButton_Click(object sender, RoutedEventArgs e)
        {
            var deviceType = DeviceType.SelectedValue as int?;
            var deviceAddress = DeviceAddress.SelectedValue as int?;
            var minimumBrightness = MinimumBrightness.Value;
            var maximumBrightness = MaximumBrightness.Value;

            if (deviceType.HasValue && deviceAddress.HasValue)
            {
                try
                {
                    _dmxConfig.AddDevice(deviceType.Value, deviceAddress.Value, maximumBrightness, minimumBrightness);

                    AddressError.Visibility = Visibility.Collapsed;
                }
                catch (DataMisalignedException)
                {
                    AddressError.Visibility = Visibility.Visible;
                }
            }
        }

        private void DeleteDeviceButton_Click(object sender, RoutedEventArgs e)
        {
            _dmxConfig.RemoveDevice(((sender as Button).Tag as int?) ?? -1);
        }

        #endregion
    }
}
