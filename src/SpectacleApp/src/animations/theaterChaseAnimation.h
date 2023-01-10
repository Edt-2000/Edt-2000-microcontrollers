#pragma once

#include "core.h"

extern Leds SpectacleLeds;

// share this chase progress between animations instances to make it more smooth
uint8_t _chaseProgress = 0;
uint8_t _progress = 0;

class TheaterChaseAnimation : public BaseAnimation
{
private:
    uint8_t _speed;
    CRGB _color1;
    CRGB _color2;

public:
    TheaterChaseAnimation(TheatreChaseCommand command) : _speed(command.speed), _color1(command.getColor1()), _color2(command.getColor2())
    {
        output();
    }

    void virtual animate()
    {
        if (_progress++ > _speed)
        {
            _progress = 0;

            _chaseProgress++;

            output();
        }
    }

    void output()
    {
        int offset = _chaseProgress % 2;

        fill_solid(SpectacleLeds.leds, SpectacleLeds.nrOfLeds, CRGB::Black);

        for (int i = offset; i < 12; i = i + 2)
        {
            fill_solid(SpectacleLeds.leds + i, 1, _color1);
        }
        for (int i = offset + 12; i < 24; i = i + 2)
        {
            fill_solid(SpectacleLeds.leds + i, 1, _color2);
        }
    }
};
