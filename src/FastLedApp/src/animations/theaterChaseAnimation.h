#pragma once

#include "core.h"
#include "leds.h"

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

    BaseLeds *_baseLeds;

public:
    TheaterChaseAnimation(TheatreChaseCommand command, BaseLeds *baseLeds) : _speed(command.speed), _nrOfSpokes(command.nrOfSpokes), _color1(command.getColor1()), _color2(command.getColor2()), _baseLeds(baseLeds)
    {
        if (_nrOfSpokes == 0)
        {
            _nrOfSpokes = 6;
        }

        output();
    }

    bool virtual animate(bool progressAnimation)
    {
        if (progressAnimation)
        {
            if (_progress++ > _speed)
            {
                _progress = 0;

                _chaseProgress++;

                output();

                return true;
            }
        }

        return false;
    }

    void output()
    {
        uint8_t ledsSkipped = _baseLeds->nrOfLeds / _nrOfSpokes;

        uint8_t offset = _chaseProgress % ledsSkipped;

        fill_solid(_baseLeds->leds, _baseLeds->nrOfLeds, CRGB::Black);

        uint8_t halfbar = _baseLeds->nrOfLeds / 2;

        for (uint8_t i = offset; i < halfbar; i = i + ledsSkipped)
        {
            fill_solid(_baseLeds->leds + i, 1, _color1);
        }
        for (uint8_t i = offset + halfbar; i < _baseLeds->nrOfLeds; i = i + ledsSkipped)
        {
            fill_solid(_baseLeds->leds + i, 1, _color2);
        }
    }
};
