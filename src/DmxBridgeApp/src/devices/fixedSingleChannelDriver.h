#pragma once

#include "dmxCommand.h"
#include "dmxDriver.h"
#include "dmxSerial.h"

class FixedSingleChannelDriver : public DmxDriver
{
private:
	inline void output()
	{
		DmxSerial::Write(_address, _minimumBrightness);
	}

public:
	void initialize(uint16_t address, uint8_t maximumBrightness, uint8_t minimumBrightness)
	{
		_address = address;
		_maximumBrightness = maximumBrightness;
		_minimumBrightness = minimumBrightness;

		output();
	}

	void loop()
	{
		output();
	}

	void solid(CHSV color)
	{
		// do nothing
	}

	void solid(CHSV color1, CHSV color2, uint8_t percentage)
	{
		// do nothing
	}

	void intensity(uint8_t intensity)
	{
		// do nothing
	}

	void fade(uint8_t fade, FadeMode mode = FadeMode::FadeToBlack)
	{
		// do nothing
	}

	void disableFade()
	{
		// do nothing
	}

	void strobo(CHSV color, uint8_t intensity)
	{
		// do nothing
	}
};
