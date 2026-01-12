#pragma once

#include "dmxDriver.hpp"
#include "../serial/dmxSerial.hpp"

class JbSystemLedPar56Driver : public DmxDriver
{
private:
    inline void output()
    {
        auto led = clampValue(leds[_ledIndex]);

        DmxSerial::Write(_address + 0, led.r);
        DmxSerial::Write(_address + 1, led.g);
        DmxSerial::Write(_address + 2, led.b);
        DmxSerial::Write(_address + 3, 255);
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
