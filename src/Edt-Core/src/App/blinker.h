#pragma once

#include <Arduino.h>
#include "time.h"

namespace App
{
class Blinker
{
private:
    bool _currentState = false;
    unsigned long _previousTime = 0;
    int _ledPin = 0;
    int _offState = LOW;

    Time *_time;

public:
    Blinker(Time *time) : _time(time){};

    inline void setup(int ledPin, int offState)
    {
        _ledPin = ledPin;
        _offState = offState;

        pinMode(_ledPin, OUTPUT);
    }

    // begin blocks for 2 seconds to signal beginning
    inline void begin()
    {
        _currentState = !_offState;

        led();

        delay(2000);

        _currentState = _offState;

        led();
    }

    inline void blink(bool fast)
    {
        auto now = _time->now();

        if (now - _previousTime > (fast ? 150 : 500))
        {
            _currentState = !_currentState;

            _previousTime = now;
        }

        led();
    }

    // blocks for some seconds to signal starting of program
    inline void release()
    {
        int loops = 1;
        do
        {
            delay(1000.0 / loops);
            _currentState = !_currentState;
            led();
        } while (loops++ <= 16);

        _currentState = _offState;
        led();
    }

    inline void led()
    {
        digitalWrite(_ledPin, _currentState ? !_offState : _offState);
    }
};
} // namespace App