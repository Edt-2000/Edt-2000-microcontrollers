#pragma once

#include <OSCArduino.h>
#include <CommandMessage.h>
#include <IMessage.h>
#include <OSCStructMessage.h>
#include <FadeMode.h>

#include "../Drivers/Dmx/DmxSerial.h"
#include "../Drivers/Dmx/DmxDriver.h"
#include "../Drivers/Dmx/DmxDriverConfig.h"
#include "../Drivers/Dmx/FixedSingleChannelDriver.h"
#include "../Drivers/Dmx/LedSpotDriver.h"
#include "../Drivers/Dmx/ShowTecCompactParDriver.h"
#include "../Drivers/Dmx/ThreeChannelLedDriver.h"

using namespace Animations;

namespace Devices
{
	class EdtDmx : public OSC::MessageConsumer
	{
	private:
		OSC::StructMessage<Messages::CommandMessage, uint32_t> _message;
		const char *_address;
		Drivers::Dmx::DmxDriver **_devices;
		uint8_t _deviceCount = 0;

	public:
		EdtDmx(const char *address) : MessageConsumer()
		{
			_address = address;
		}

		const char *address()
		{
			return _address;
		}

		OSC::IMessage *message()
		{
			return &_message;
		}

		void start()
		{
			if (_deviceCount > 0)
			{
				delete[] _devices;
			}

			_deviceCount = Drivers::Dmx::DmxDriver::getDeviceCount();

			if (_deviceCount > 0)
			{
				_devices = new Drivers::Dmx::DmxDriver *[_deviceCount];
				for (uint8_t i = 0; i < _deviceCount; ++i)
				{
					auto config = Drivers::Dmx::DmxDriver::getDeviceConfig(i);

					switch (config.type)
					{
					case Drivers::Dmx::DmxDeviceType::LedSpot:
						_devices[i] = (Drivers::Dmx::DmxDriver *)new Drivers::Dmx::LedSpotDriver();
						break;

					case Drivers::Dmx::DmxDeviceType::ShowTecCompactPar:
						_devices[i] = (Drivers::Dmx::DmxDriver *)new Drivers::Dmx::ShowTecCompactParDriver();
						break;

					case Drivers::Dmx::DmxDeviceType::ThreeChannelLed:
						_devices[i] = (Drivers::Dmx::DmxDriver *)new Drivers::Dmx::ThreeChannelLedDriver();
						break;

					case Drivers::Dmx::DmxDeviceType::FixedSingleChannel:
						_devices[i] = (Drivers::Dmx::DmxDriver *)new Drivers::Dmx::FixedSingleChannelDriver();
						break;

					case Drivers::Dmx::DmxDeviceType::Unknown:
					default:
						continue;
					};

					_devices[i]->initialize(config.address, config.maximumBrightness, config.minimumBrightness);

					_devices[i]->solid(120, 255, 255);
					_devices[i]->fade(2);
				}
			}
		}

		void callbackMessage()
		{
			// todo: remove these variables
			auto command = _message.messageStruct.command;
			auto dualColor = _message.messageStruct.commands.dualColor;
			auto rainbow = _message.messageStruct.commands.rainbow;
			auto singleColor = _message.messageStruct.commands.singleColor;
			auto strobo = _message.messageStruct.commands.strobo;
			auto twinkle = _message.messageStruct.commands.twinkle;
			auto vuMeter = _message.messageStruct.commands.vuMeter;

			switch (command)
			{

			case Messages::ColorCommands::SinglePulse:
			case Messages::ColorCommands::SingleSolid:
			case Messages::ColorCommands::SingleSpark:
				for (uint8_t i = 0; i < _deviceCount; ++i)
				{
					if (singleColor.value > 0)
					{
						_devices[i]->solid(singleColor.hue, singleColor.saturation, singleColor.value);
					}

					if (command == Messages::ColorCommands::SinglePulse || singleColor.value == 0)
					{
						_devices[i]->fade(singleColor.duration, FadeMode::FadeToBlack);
					}
					else if (command == Messages::ColorCommands::SingleSpark)
					{
						_devices[i]->fade(singleColor.duration, FadeMode::FadeOneByOne);
					}
					else
					{
						_devices[i]->disableFade();
					}
				}
				break;

			case Messages::ColorCommands::DualPulse:
			case Messages::ColorCommands::DualSolid:
			case Messages::ColorCommands::DualSparkle:
				for (uint8_t i = 0; i < _deviceCount; ++i)
				{
					_devices[i]->solid(dualColor.hue1, dualColor.hue2, 255, 254, dualColor.percentage);

					if (command == Messages::ColorCommands::DualPulse)
					{
						_devices[i]->fade(dualColor.duration, FadeMode::FadeToBlack);
					}
					else if (command == Messages::ColorCommands::DualSparkle)
					{
						_devices[i]->fade(dualColor.duration, FadeMode::FadeOneByOne);
					}
					else
					{
						_devices[i]->disableFade();
					}
				}
				break;

			case Messages::ColorCommands::VuMeter:
				for (uint8_t i = 0; i < _deviceCount; ++i)
				{
					if (vuMeter.intensity > 0)
					{
						_devices[i]->intensity(vuMeter.intensity);
					}
					else
					{
						_devices[i]->fade(127);
					}
				}
				break;

			case Messages::ColorCommands::Twinkle:
				for (uint8_t i = 0; i < _deviceCount; ++i)
				{
					_devices[i]->disableFade();

					if (twinkle.intensity > 0)
					{
						_devices[i]->solid(twinkle.hue, 255, twinkle.intensity - 1);
					}
					else
					{
						_devices[i]->fade(127);
					}
				}
				break;

			case Messages::ColorCommands::Strobo:
				for (uint8_t i = 0; i < _deviceCount; ++i)
				{
					_devices[i]->strobo(strobo.hue, strobo.intensity);
				}
				break;

			case Messages::ColorCommands::Chase:
			case Messages::ColorCommands::Bash:
			case Messages::ColorCommands::RainbowPulse:
			case Messages::ColorCommands::RainbowSolid:
			case Messages::ColorCommands::RainbowSpark:

				// No implementation

				break;
			}

			if (_message.messageStruct.command == Messages::ColorCommands::DMXConfig)
			{

				auto dmxConfigCommand = _message.messageStruct.commands.dmxConfig;

				bool clear = dmxConfigCommand.config & 0x04;
				bool reset = dmxConfigCommand.config & 0x02;
				bool address256 = dmxConfigCommand.config & 0x01;

				if (clear)
				{
					Drivers::Dmx::DmxDriver::clearDeviceConfig();
				}

				if (dmxConfigCommand.deviceAddress > 0)
				{
					auto config = Drivers::Dmx::DmxDriverConfig();
					config.address = (uint16_t)dmxConfigCommand.deviceAddress;
					if (address256)
					{
						config.address += (uint16_t)256U;
					}
					config.type = (Drivers::Dmx::DmxDeviceType)dmxConfigCommand.deviceType;
					config.maximumBrightness = dmxConfigCommand.maximumBrightness;
					config.minimumBrightness = dmxConfigCommand.minimumBrightness;

					Drivers::Dmx::DmxDriver::setDeviceConfig(config);
				}

				if (reset)
				{
					start();
				}
			}
		}

		void show()
		{
			for (uint8_t i = 0; i < _deviceCount; ++i)
			{
				_devices[i]->loop();
			}
		}
	};
}