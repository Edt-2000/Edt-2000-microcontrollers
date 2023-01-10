#pragma once

#include "core.h"

extern Leds SpectacleLeds;

class ChaseAnimation : public BaseAnimation
{
private:
    uint8_t _direction;
    uint8_t _speed;
    uint8_t _fadeSpeed;
    CRGB _color;

    uint8_t _progress = 0;

public:
    ChaseAnimation(ChaseCommand command) : _direction(command.direction), _speed(command.speed), _fadeSpeed(command.fadeSpeed), _color(command.getColor())
    {
    }

    void virtual animate()
    {
        uint8_t from = _progress / 2;
        uint8_t to = (_progress / 2) + 1;

        if (to > 127)
        {
            to = 127;
        }

        if (_direction == 1)
        {
            auto start = SpectacleLeds.normalizeLedNrDown(127 - to);
            auto end = SpectacleLeds.normalizeLedNrUp(127 - from);

            fill_solid(SpectacleLeds.leds + start, end - start, _color);
            SpectacleLeds.fade(start, end, _fadeSpeed * 2, FadeMode::FadeOneByOne);
        }
        else
        {
            auto start = SpectacleLeds.normalizeLedNrDown(from);
            auto end = SpectacleLeds.normalizeLedNrUp(to);

            fill_solid(SpectacleLeds.leds + start, end - start, _color);
            SpectacleLeds.fade(start, end, _fadeSpeed * 2, FadeMode::FadeOneByOne);
        }
        
        if (_progress > 255 - _speed)
        {
            finished = true;
            return;
        }

        _progress += _speed;
    }
};
