using Dispedter.Common.Factories;
using Dispedter.Common.OSC;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;

namespace Dispedter.Common.DMX
{
    public class DmxConfig
    {
        public ICollection<DmxDevice> DmxDevices;

        public DmxConfig(ICollection<DmxDevice> collection)
        {
            DmxDevices = collection;
        }

        public ICollection<DmxType> Types { get; private set; } = new[]
        {
            new DmxType { Name = "LED Spot - LED Spot light 4 channel", TypeNr = 1, Width = 6 },
            new DmxType { Name = "LED Par - Generic 3 channel", TypeNr = 2, Width = 3 },
            new DmxType { Name = "LED Par - Show Tec Compact Par 8 channel", TypeNr = 3, Width = 8 },
            new DmxType { Name = "Fixed - Single channel", TypeNr = 4, Width = 1 }
        };


        public void ReadConfig(string configString)
        {
            var config = JsonConvert.DeserializeObject<List<DmxDevice>>(configString);

            RemoveAllDevices();
            
            config?.OrderBy(s => s.Address).ToList().ForEach(DmxDevices.Add);
        }

        public string WriteConfig()
        {
            var configString = JsonConvert.SerializeObject(DmxDevices);
            return configString;
        }

        public IEnumerable<OscMessage> GenerateOscConfig(string target)
        {
            var commandFactory = new CommandFactory(new[] { target });

            var commands = new List<OscMessage>();

            commands.AddRange(commandFactory.ClearDMX());

            foreach (var device in DmxDevices)
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

            if (DmxDevices.SelectMany(s => Enumerable.Range(s.Address, s.Type.Width)).Intersect(requiredAddressSpace).Any())
            {
                throw new DataMisalignedException();
            }

            DmxDevices.Add(new DmxDevice
            {
                Type = newType,
                Address = address,
                MaximumBrightness = maximumBrightness,
                MinimumBrightness = minimumBrightness
            });
        }

        public void RemoveDevice(int address)
        {
            if (DmxDevices.Any(s => s.Address == address))
            {
                DmxDevices.Remove(DmxDevices.First(s => s.Address == address));
            }
        }

        public void RemoveAllDevices()
        {
            DmxDevices.Clear();
        }
    }
}
