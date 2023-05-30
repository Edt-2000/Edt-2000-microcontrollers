#pragma once

#include "core.h"
#include "leds.h"

extern volatile bool doFastLed;

class StroboAnimation : public BaseAnimation
{
private:
    uint8_t _intensity;
    uint8_t _progress;
    CRGB _color;

    BaseLeds *_baseLeds;

public:
    StroboAnimation(StroboCommand command, BaseLeds *baseLeds) : _intensity(command.intensity), _color(command.getColor()), _baseLeds(baseLeds)
    {
        _progress = _intensity;
    }

    bool virtual animate(bool progressAnimation)
    {
        if (_progress == 0)
        {
            fill_solid(_baseLeds->leds, _baseLeds->nrOfLeds, CRGB::Black);

            return true;
        }

        if (progressAnimation && (_progress++) > _intensity)
        {
            _progress = 0;
            fill_solid(_baseLeds->leds, _baseLeds->nrOfLeds, _color);

            return true;
        }

        return false;
    }
};
