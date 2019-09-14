#pragma once

#include <Arduino.h>
#include "time.hpp"

class Blinker
{
private:
    bool _currentState = false;
    unsigned long _previousTime = 0;
    unsigned long _startLoops = 1;
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

        if (now - _previousTime > (fast ? 250 : 500))
        {
            _currentState = !_currentState;

            _previousTime = now;
        }

        led();
    }

    inline bool initialized()
    {
        auto now = _time->now();

        if (now - _previousTime > (1000 / _startLoops))
        {
            _currentState = !_currentState;

            _startLoops++;
            _previousTime = now;
        }

        led();

        if (_startLoops >= 16)
        {
            _startLoops = 1;

            return true;
        }

        return false;
    }

    inline void release() {
        pinMode(_ledPin, 0);
    }

    inline void led()
    {
        digitalWrite(_ledPin, _currentState ? !_offState : _offState);
    }
};