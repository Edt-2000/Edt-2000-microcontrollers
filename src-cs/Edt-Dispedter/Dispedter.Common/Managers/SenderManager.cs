﻿using Dispedter.Common.OSC;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.SerialCommunication;

namespace Dispedter.Common.Managers
{
    public class SenderManager
    {
        private readonly bool _detectUsb;
        private readonly IEnumerable<IPAddress> _udpDestinations;

        private const int UdpPort = 12345;

        private readonly List<ISender> _senders = new List<ISender>();

        public SenderManager(bool detectUsb = false, IEnumerable<IPAddress> udpDestinations = null)
        {
            _detectUsb = detectUsb;
            _udpDestinations = udpDestinations;
        }

        public List<ISender> Senders { get => _senders; }

        public async Task ManageDevicesAsync()
        {
            do
            {
                try
                {
                    _senders.RemoveAll(s => s.IsBroken());

                    if (_detectUsb)
                    {
                        var allDevices = await GetAllUsbDevicesAsync();

                        var newSenders = allDevices.Where(s => !_senders.Select(sender => sender.Id).Contains(s.Id));

                        foreach (var newSender in newSenders)
                        {
                            var usbSender = new UsbSender(newSender);

                            _senders.Add(usbSender);
                        }
                    }

                    if (_udpDestinations?.Any() ?? false)
                    {
                        foreach (var ip in _udpDestinations)
                        {
                            if (!_senders.Exists(s => s.Id == UdpSender.CreateId(ip, UdpPort)))
                            {
                                var udpSender = new UdpSender(ip, UdpPort);

                                _senders.Add(udpSender);
                            }
                        }
                    }

                    await Task.Delay(5000);
                }
                catch (Exception)
                {
                }
            }
            while (true);
        }

        private async Task<IEnumerable<DeviceInformation>> GetAllUsbDevicesAsync()
        {
            var devices = new List<DeviceInformation>();

            try
            {
                var _serialSelector = SerialDevice.GetDeviceSelector();
                var infos = await DeviceInformation.FindAllAsync(_serialSelector);

                foreach (var info in infos.Where(i => IsTargetDevice(i.Name)))
                {
                    devices.Add(info);
                }
            }
            catch (Exception)
            {
            }

            return devices;
        }

        private bool IsTargetDevice(string name)
        {
            var names = new[] { "SparkFun", "Arduino", "UART" };
            return names.Any(n => name.Contains(n));
        }
    }
}
