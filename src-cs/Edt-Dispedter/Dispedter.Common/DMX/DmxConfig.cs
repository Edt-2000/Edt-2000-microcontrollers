using System;
using System.Collections.Generic;
using System.Linq;
using Dispedter.Common.Factories;
using Dispedter.Common.OSC;
using Newtonsoft.Json;

namespace Dispedter.Common.DMX
{
    public class DmxConfig
    {
        private readonly ICollection<DmxDevice> _dmxDevices;

        public DmxConfig(ICollection<DmxDevice> collection)
        {
            _dmxDevices = collection;
        }

        public ICollection<DmxType> Types { get; private set; } = new[]
        {
            new DmxType { Name = "LED Spot - LED Spot light 4 channel", TypeNr = 1, Width = 6 },
            new DmxType { Name = "LED Par - Generic 3 channel", TypeNr = 2, Width = 3 },
            new DmxType { Name = "LED Par - Show Tec Compact Par 8 channel", TypeNr = 3, Width = 8 },
            new DmxType { Name = "LED Par - Show Tec Compact Par 4 channel", TypeNr = 5, Width = 4 },
            new DmxType { Name = "LED Par - Show Tec Compact Par 3 channel", TypeNr = 6, Width = 3 },
            new DmxType { Name = "Fixed - Single channel", TypeNr = 4, Width = 1 }
        };

        public void ReadConfig(string configString)
        {
            var config = JsonConvert.DeserializeObject<List<DmxDevice>>(configString);

            RemoveAllDevices();

            config?.OrderBy(s => s.Address).ToList().ForEach(_dmxDevices.Add);
        }

        public string WriteConfig()
        {
            var configString = JsonConvert.SerializeObject(_dmxDevices);
            return configString;
        }

        public IEnumerable<OscMessage> GenerateOscConfig(string target)
        {
            var commandFactory = new CommandFactory(new[] { target });

            var commands = new List<OscMessage>();

            commands.AddRange(commandFactory.ClearDMX());

            foreach (var device in _dmxDevices)
            {
                commands.AddRange(commandFactory.ProgramDmxDevice(device.Type.TypeNr, device.Address, device.MaximumBrightness, device.MinimumBrightness));
            }

            commands.AddRange(commandFactory.RestartDMX());

            return commands;
        }

        public void AddDevice(int typeNr, int address, double maximumBrightness, double minimumBrightness)
        {
            var newType = Types.First(t => t.TypeNr == typeNr);

            var requiredAddressSpace = Enumerable.Range(address, newType.Width);

            if (_dmxDevices.SelectMany(s => Enumerable.Range(s.Address, s.Type.Width)).Intersect(requiredAddressSpace).Any())
            {
                throw new DataMisalignedException();
            }

            _dmxDevices.Add(new DmxDevice
            {
                Type = newType,
                Address = address,
                MaximumBrightness = maximumBrightness,
                MinimumBrightness = minimumBrightness
            });
        }

        public void RemoveDevice(int address)
        {
            if (_dmxDevices.Any(s => s.Address == address))
            {
                _dmxDevices.Remove(_dmxDevices.First(s => s.Address == address));
            }
        }

        public void RemoveAllDevices()
        {
            _dmxDevices.Clear();
        }
    }
}
