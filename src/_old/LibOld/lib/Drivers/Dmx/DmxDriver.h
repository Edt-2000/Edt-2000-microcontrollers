#pragma once

#include <EEPROM.h>
#include "../Animations/FadeMode.h"
#include "DmxDriverConfig.h"
#include <FastLED.h>

#define COUNTLOCATION 0
#define DEVICELOCATION 1

namespace Drivers
{
	namespace Dmx
	{
		class DmxDriver
		{
		protected:
			uint16_t _address;
			uint8_t _minimumBrightness;
			uint8_t _maximumBrightness;

			inline uint8_t clampValue(uint8_t value)
			{
				return _minimumBrightness + ((value / 255.0) * ((float)(_maximumBrightness - _minimumBrightness)));
			}

		public:
			void virtual initialize(uint16_t address, uint8_t maximumBrightness, uint8_t minimumBrightness) = 0;
			void virtual loop() = 0;

			void virtual solid(uint8_t h, uint8_t s, uint8_t v) = 0;
			void virtual solid(uint8_t h1, uint8_t h2, uint8_t s, uint8_t v, uint8_t percentage) = 0;
			void virtual intensity(uint8_t intensity) = 0;
			void virtual fade(uint8_t duration, Animations::FadeMode mode = Animations::FadeMode::FadeToBlack) = 0;
			void virtual disableFade() = 0;
			void virtual strobo(uint8_t h, uint8_t intesity) = 0;

			static void clearDeviceConfig()
			{
				setDeviceCount(0);
			}

			static uint8_t getDeviceCount()
			{
				uint8_t count;

				EEPROM.get(COUNTLOCATION, count);

				return count;
			}

			static void setDeviceCount(uint8_t count)
			{
				EEPROM.put(COUNTLOCATION, count);
				EEPROM.commit();
			}

			static DmxDriverConfig getDeviceConfig(uint8_t nr)
			{
				DmxDriverConfig config;

				EEPROM.get(DEVICELOCATION + (sizeof(DmxDriverConfig) * nr), config);

				return config;
			}

			static void setDeviceConfig(DmxDriverConfig config)
			{
				uint8_t nr = getDeviceCount();

				EEPROM.put(DEVICELOCATION + (sizeof(DmxDriverConfig) * nr), config);
				EEPROM.commit();
				
				setDeviceCount(nr + 1);
			}
		};
	}
}