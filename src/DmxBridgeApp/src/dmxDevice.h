#pragma once

#include "core.h"
#include "dmxCommand.h"
#include "devices/dmxDriver.h"
#include "devices/fixedSingleChannelDriver.h"
#include "devices/ledSpotDriver.h"
#include "devices/showTecCompactParDriver.h"
#include "devices/threeChannelLedDriver.h"
#include "devices/jbSystemLedPar56.h"

class DmxDevice : public OSC::MessageConsumer
{
private:
	OSC::StructMessage<DmxCommand, uint32_t> _message;
	const char *_address;
	DmxDriver **_devices;
	uint8_t _deviceCount = 0;

public:
	DmxDevice(const char *address) : MessageConsumer()
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

		_deviceCount = DmxDriver::getDeviceCount();

		if (_deviceCount > 0)
		{
			_devices = new DmxDriver*[_deviceCount];
			for (uint8_t i = 0; i < _deviceCount; ++i)
			{
				auto config = DmxDriver::getDeviceConfig(i);

				switch (config.type)
				{
				case DmxDeviceType::LedSpot:
					_devices[i] = (DmxDriver *)new LedSpotDriver();
					break;

				case DmxDeviceType::ShowTecCompactPar8channel:
					_devices[i] = (DmxDriver *)new ShowTecCompactParDriver(8);
					break;
				
				case DmxDeviceType::ShowTecCompactPar4channel:
					_devices[i] = (DmxDriver *)new ShowTecCompactParDriver(4);
					break;

				case DmxDeviceType::ShowTecCompactPar3channel:
					_devices[i] = (DmxDriver *)new ShowTecCompactParDriver(3);
					break;

				case DmxDeviceType::ThreeChannelLed:
					_devices[i] = (DmxDriver *)new ThreeChannelLedDriver();
					break;

				case DmxDeviceType::FixedSingleChannel:
					_devices[i] = (DmxDriver *)new FixedSingleChannelDriver();
					break;

				case DmxDeviceType::JbSystemLedPar56:
					_devices[i] = (DmxDriver *)new JbSystemLedPar56Driver();
					break;

				case DmxDeviceType::Unknown:
				default:
					continue;
				};

				_devices[i]->initialize(config.address, config.maximumBrightness, config.minimumBrightness);

				_devices[i]->solid(CHSV(80, 255, 255));
				_devices[i]->fade(2);
			}
		}
	}

	void callbackMessage()
	{
		auto message = _message.messageStruct;

		switch (message.mode)
		{

		case ColorCommands::SinglePulse:
		case ColorCommands::SingleSolid:
		case ColorCommands::SingleSpark:
			for (uint8_t i = 0; i < _deviceCount; ++i)
			{
				if (message.commands.singleColor.value > 0)
				{
					_devices[i]->solid(message.commands.singleColor.getColor());
				}

				if (message.mode == ColorCommands::SinglePulse || message.commands.singleColor.value == 0)
				{
					_devices[i]->fade(message.commands.singleColor.duration, FadeMode::FadeToBlack);
				}
				else if (message.mode == ColorCommands::SingleSpark)
				{
					_devices[i]->fade(message.commands.singleColor.duration, FadeMode::FadeOneByOne);
				}
				else
				{
					_devices[i]->disableFade();
				}
			}
			break;

		case ColorCommands::DualPulse:
		case ColorCommands::DualSolid:
		case ColorCommands::DualSparkle:
			for (uint8_t i = 0; i < _deviceCount; ++i)
			{
				_devices[i]->solid(message.commands.dualColor.getColor1(), message.commands.dualColor.getColor2(), message.commands.dualColor.percentage);

				if (message.mode == ColorCommands::DualPulse)
				{
					_devices[i]->fade(message.commands.dualColor.duration, FadeMode::FadeToBlack);
				}
				else if (message.mode == ColorCommands::DualSparkle)
				{
					_devices[i]->fade(message.commands.dualColor.duration, FadeMode::FadeOneByOne);
				}
				else
				{
					_devices[i]->disableFade();
				}
			}
			break;

		case ColorCommands::VuMeter:
			for (uint8_t i = 0; i < _deviceCount; ++i)
			{
				if (message.commands.vuMeter.intensity > 0)
				{
					_devices[i]->intensity(message.commands.vuMeter.intensity);
				}
				else
				{
					_devices[i]->fade(127);
				}
			}
			break;

		case ColorCommands::Twinkle:
			for (uint8_t i = 0; i < _deviceCount; ++i)
			{
				_devices[i]->disableFade();

				if (message.commands.twinkle.intensity > 0)
				{
					_devices[i]->solid(message.commands.twinkle.getColor());
				}
				else
				{
					_devices[i]->fade(127);
				}
			}
			break;

		case ColorCommands::Strobo:
			for (uint8_t i = 0; i < _deviceCount; ++i)
			{
				_devices[i]->strobo(message.commands.strobo.getColor(), message.commands.strobo.intensity);
			}
			break;

		case ColorCommands::Chase:
		case ColorCommands::RainbowPulse:
		case ColorCommands::RainbowSolid:
		case ColorCommands::RainbowSpark:

			// No implementation

			break;
		}

		if (message.mode == ColorCommands::DMXConfig)
		{

			auto dmxConfigCommand = _message.messageStruct.commands.dmxConfig;

			bool clear = dmxConfigCommand.config & 0x04;
			bool reset = dmxConfigCommand.config & 0x02;
			bool address256 = dmxConfigCommand.config & 0x01;

			if (clear)
			{
				DmxDriver::clearDeviceConfig();
			}

			if (dmxConfigCommand.deviceAddress > 0)
			{
				auto config = DmxDriverConfig();
				config.address = (uint16_t)dmxConfigCommand.deviceAddress;
				if (address256)
				{
					config.address += (uint16_t)256U;
				}
				config.type = (DmxDeviceType)dmxConfigCommand.deviceType;
				config.maximumBrightness = dmxConfigCommand.maximumBrightness;
				config.minimumBrightness = dmxConfigCommand.minimumBrightness;

				DmxDriver::setDeviceConfig(config);
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