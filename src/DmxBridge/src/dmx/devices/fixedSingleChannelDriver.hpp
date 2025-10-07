#pragma once

#include "dmxDriver.hpp"
#include "../serial/dmxSerial.hpp"

class FixedSingleChannelDriver : public DmxDriver
{
private:
	inline void output()
	{
		DmxSerial::Write(_address, _minimumBrightness);
	}

public:
	void initialize(uint16_t address, uint8_t ledIndex, uint8_t maximumBrightness, uint8_t minimumBrightness)
	{
		_address = address;
        _ledIndex = ledIndex;
		_maximumBrightness = maximumBrightness;
		_minimumBrightness = minimumBrightness;

		output();
	}

	void loop()
	{
		output();
	}
};
