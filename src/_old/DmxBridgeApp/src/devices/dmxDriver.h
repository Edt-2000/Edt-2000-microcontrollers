#pragma once

#include "dmxDriverConfig.h"

#include <EEPROM.h>

#define COUNTLOCATION 10
#define DEVICELOCATION 11

class DmxDriver
{
protected:
	uint16_t _address;
	uint8_t _minimumBrightness;
	uint8_t _maximumBrightness;

	inline CHSV clampValue(CHSV color)
	{
		return CHSV(color.h, color.s, _minimumBrightness + ((color.v / 255.0) * ((float)(_maximumBrightness - _minimumBrightness))));
	}

public:
	void virtual initialize(uint16_t address, uint8_t maximumBrightness, uint8_t minimumBrightness) = 0;
	void virtual loop() = 0;

	void virtual solid(CHSV color) = 0;
	void virtual solid(CHSV color1, CHSV color2, uint8_t percentage) = 0;
	void virtual intensity(uint8_t intensity) = 0;
	void virtual fade(uint8_t duration, FadeMode mode = FadeMode::FadeToBlack) = 0;
	void virtual disableFade() = 0;
	void virtual strobo(CHSV color, uint8_t intesity) = 0;

	static void clearDeviceConfig()
	{
		setDeviceCount(0);
	}

	static uint8_t getDeviceCount()
	{
		uint8_t count = 0;

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
