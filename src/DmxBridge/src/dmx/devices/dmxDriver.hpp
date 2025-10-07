#pragma once

#include "dmxDriverConfig.hpp"

#include <EEPROM.h>
#include <FastLED.h>
#include <fader.hpp>

#define COUNTLOCATION 10
#define DEVICELOCATION 11

class DmxDriver
{
protected:
	uint16_t _address;
	uint8_t _ledIndex;
	uint8_t _minimumBrightness;
	uint8_t _maximumBrightness;

	inline CRGB clampValue(CRGB rgb)
	{
		// TODO
		return rgb;

		auto color = rgb2hsv_approximate(rgb);
		return CHSV(color.h, color.s, _minimumBrightness + ((color.v / 255.0) * ((float)(_maximumBrightness - _minimumBrightness))));
	}

public:
	void virtual initialize(uint16_t address, uint8_t ledIndex, uint8_t maximumBrightness, uint8_t minimumBrightness) = 0;
	void virtual loop() = 0;

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
