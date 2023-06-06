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

	void solid(uint8_t h, uint8_t s, uint8_t v)
	{
		// do nothing
	}

	void solid(uint8_t h1, uint8_t h2, uint8_t s, uint8_t v, uint8_t percentage)
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

	void strobo(uint8_t h, uint8_t intensity)
	{
		// do nothing
	}
};
