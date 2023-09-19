#pragma once

#include "core.h"
#include "leds.h"

extern Leds SpectacleLeds;

// share this chase progress between animations instances to make it more smooth
static uint8_t _chaseProgress = 0;
static uint8_t _progress = 0;

class TheaterChaseAnimation : public BaseAnimation
{
private:
    uint8_t _speed;
    uint8_t _nrOfSpokes;
    CRGB _color1;
    CRGB _color2;

public:
// TODO: accept BaseLeds*
    TheaterChaseAnimation(TheatreChaseCommand command) : _speed(command.speed), _nrOfSpokes(command.nrOfSpokes), _color1(command.getColor1()), _color2(command.getColor2())
    {
        if (_nrOfSpokes == 0)
        {
            _nrOfSpokes = 6;
        }

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
        uint8_t ledsSkipped = 12 / _nrOfSpokes;

        uint8_t offset = _chaseProgress % ledsSkipped;

        fill_solid(SpectacleLeds.leds, SpectacleLeds.nrOfLeds, CRGB::Black);

        for (uint8_t i = offset; i < 12; i = i + ledsSkipped)
        {
            fill_solid(SpectacleLeds.leds + i, 1, _color1);
        }
        for (uint8_t i = offset + 12; i < 24; i = i + ledsSkipped)
        {
            fill_solid(SpectacleLeds.leds + i, 1, _color2);
        }
    }
};
