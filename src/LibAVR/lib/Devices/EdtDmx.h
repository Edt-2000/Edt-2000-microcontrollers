#pragma once

#include <OSCArduino.h>
#include <OSCMessageConsumer.h>
#include <OSCMessageDefinitions.h>

#include "../Drivers/Dmx/DmxDriver.h"
#include "../Drivers/Dmx/DmxDriverConfig.h"
#include "../Drivers/Dmx/FixedSingleChannelDriver.h"
#include "../Drivers/Dmx/LedSpotDriver.h"
#include "../Drivers/Dmx/ShowTecCompactParDriver.h"
#include "../Drivers/Dmx/ThreeChannelLedDriver.h"

namespace Devices
{
	class EdtDmx : public OSC::MessageConsumer<OSC::StructMessage<OSC::EdtMessage, uint8_t>>
	{
	private:
		const char *_pattern;
		Drivers::Dmx::DmxDriver **_devices;
		uint8_t _deviceCount = 0;

	public:
		EdtDMX(const char *pattern) : MessageConsumer()
		{
			_pattern = pattern;
		}

		const char *pattern()
		{
			return _pattern;
		}

		void initialize()
		{
			if (_deviceCount > 0)
			{
				delete[] _devices;
			}

			_deviceCount = Drivers::Dmx::DmxDriver::getDeviceConfig();

			if (_deviceCount > 0)
			{
				_devices = new Drivers::Dmx::DmxDriver*[_deviceCount];
				for (uint8_t i = 0; i < _deviceCount; ++i)
				{
					Drivers::Dmx::DeviceConfig config = Drivers::Dmx::DmxDriver::getDeviceConfig(i);

					switch (config.type)
					{
					case Drivers::Dmx::DeviceType::LedSpot:
						_devices[i] = (Drivers::Dmx::Device *)new Drivers::Dmx::LedSpot();
						break;

					case Drivers::Dmx::DeviceType::ShowTecCompactPar:
						_devices[i] = (Drivers::Dmx::Device *)new Drivers::Dmx::ShowTecCompactPar();
						break;

					case Drivers::Dmx::DeviceType::ThreeChannelLed:
						_devices[i] = (Drivers::Dmx::Device *)new Drivers::Dmx::ThreeChannelLed();
						break;

					case Drivers::Dmx::DeviceType::FixedSingleChannel:
						_devices[i] = (Drivers::Dmx::Device *)new Drivers::Dmx::FixedSingleChannel();
						break;

					case Drivers::Dmx::DeviceType::Unknown:
					default:
						continue;
					};

					_devices[i]->initialize(config.address, config.maximumBrightness, config.minimumBrightness);

					_devices[i]->solid(120, 255, 255);
					_devices[i]->fade(2);
				}
			}
		}

		void callbackMessage(OSC::StructMessage<OSC::EdtMessage, uint8_t> *message)
		{
			// TODO: put loop in switch
			for (uint8_t i = 0; i < _deviceCount; ++i)
			{
				// todo: remove these variables
				auto command = message->messageStruct.command;
				auto dualColor = message->messageStruct.commands.dualColor;
				auto rainbow = message->messageStruct.commands.rainbow;
				auto singleColor = message->messageStruct.commands.singleColor;
				auto strobo = message->messageStruct.commands.strobo;
				auto twinkle = message->messageStruct.commands.twinkle;
				auto vuMeter = message->messageStruct.commands.vuMeter;

				switch (command)
				{

				case OSC::ColorCommands::SinglePulse:
				case OSC::ColorCommands::SingleSolid:
				case OSC::ColorCommands::SingleSpark:

					if (singleColor.value > 0)
					{
						_devices[i]->solid(singleColor.hue, singleColor.saturation, singleColor.value);
					}

					if (command == OSC::ColorCommands::SinglePulse || singleColor.value == 0)
					{
						_devices[i]->fade(singleColor.duration, FadeMode::FadeToBlack);
					}
					else if (command == OSC::ColorCommands::SingleSpark)
					{
						_devices[i]->fade(singleColor.duration, FadeMode::FadeOneByOne);
					}
					else
					{
						_devices[i]->disableFade();
					}

					break;

				case OSC::ColorCommands::DualPulse:
				case OSC::ColorCommands::DualSolid:
				case OSC::ColorCommands::DualSparkle:

					_devices[i]->solid(dualColor.hue1, dualColor.hue2, 255, 254, dualColor.percentage);

					if (command == OSC::ColorCommands::DualPulse)
					{
						_devices[i]->fade(dualColor.duration, FadeMode::FadeToBlack);
					}
					else if (command == OSC::ColorCommands::DualSparkle)
					{
						_devices[i]->fade(dualColor.duration, FadeMode::FadeOneByOne);
					}
					else
					{
						_devices[i]->disableFade();
					}

					break;

				case OSC::ColorCommands::VuMeter:

					if (vuMeter.intensity > 0)
					{
						_devices[i]->intensity(vuMeter.intensity);
					}
					else
					{
						_devices[i]->fade(127);
					}

					break;

				case OSC::ColorCommands::Twinkle:

					_devices[i]->disableFade();

					if (twinkle.intensity > 0)
					{
						_devices[i]->solid(twinkle.hue, 255, twinkle.intensity - 1);
					}
					else
					{
						_devices[i]->fade(127);
					}

					break;

				case OSC::ColorCommands::Strobo:

					_devices[i]->strobo(strobo.hue, strobo.intensity);

					break;

				case OSC::ColorCommands::Chase:
				case OSC::ColorCommands::Bash:
				case OSC::ColorCommands::RainbowPulse:
				case OSC::ColorCommands::RainbowSolid:
				case OSC::ColorCommands::RainbowSpark:

					// No implementation

					break;
				}
			}

			if (message->messageStruct.command == OSC::ColorCommands::DMXConfig)
			{

				auto dmxConfigCommand = message->messageStruct.commands.dmxConfig;

				bool clear = dmxConfigCommand.config & 0x04;
				bool reset = dmxConfigCommand.config & 0x02;
				bool address256 = dmxConfigCommand.config & 0x01;

				if (clear)
				{
					Drivers::Dmx::Device::clearDeviceConfig();
				}

				if (dmxConfigCommand.deviceAddress > 0)
				{
					auto config = Drivers::Dmx::DeviceConfig();
					config.address = (uint16_t)dmxConfigCommand.deviceAddress;
					if (address256)
					{
						config.address += (uint16_t)256U;
					}
					config.type = (Drivers::Dmx::DeviceType)dmxConfigCommand.deviceType;
					config.maximumBrightness = dmxConfigCommand.maximumBrightness;
					config.minimumBrightness = dmxConfigCommand.minimumBrightness;

					Drivers::Dmx::Device::setDeviceConfig(config);
				}

				if (reset)
				{
					initialize();
				}
			}
		}

		void animationLoop()
		{
			for (uint8_t i = 0; i < _deviceCount; ++i)
			{
				_devices[i]->loop();
			}
		}
	};
}