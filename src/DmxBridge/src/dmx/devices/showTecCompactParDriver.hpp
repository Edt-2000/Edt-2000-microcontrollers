#pragma once

#include "dmxDriver.hpp"
#include "../serial/dmxSerial.hpp"

class ShowTecCompactParDriver : public DmxDriver
{
private:
    uint8_t _channels;

    inline void output()
    {
        auto led = clampValue(leds[_ledIndex]);

        if (_channels == 8)
        {
            DmxSerial::Write(_address + 0, 255);
            DmxSerial::Write(_address + 1, led.r);
            DmxSerial::Write(_address + 2, led.g);
            DmxSerial::Write(_address + 3, led.b);
        }
        else if (_channels == 4)
        {
            DmxSerial::Write(_address + 0, 255);
            DmxSerial::Write(_address + 1, led.r);
            DmxSerial::Write(_address + 2, led.g);
            DmxSerial::Write(_address + 3, led.b);
        }
        else if (_channels == 3)
        {
            DmxSerial::Write(_address + 0, led.r);
            DmxSerial::Write(_address + 1, led.g);
            DmxSerial::Write(_address + 2, led.b);
        }
    }

public:
    ShowTecCompactParDriver(uint8_t channels) : _channels(channels)
    {
    }

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
