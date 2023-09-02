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

    bool _on = false;

public:
    StroboAnimation(StroboCommand command, BaseLeds *baseLeds) : _intensity(command.intensity), _color(command.getColor()), _baseLeds(baseLeds)
    {
        _progress = _intensity;
    }

    bool virtual animate(bool progressAnimation)
    {
        if (!progressAnimation)
        {
            return false;
        }

        // if (_progress == 0)
        // {
        //     fill_solid(_baseLeds->leds, _baseLeds->nrOfLeds, CRGB::Black);

        //     return true;
        // }

        if ((_progress++ > _intensity))
        {
            _on = !_on;
            _progress = 0;
            fill_solid(_baseLeds->leds, _baseLeds->nrOfLeds, _on ? _color : CRGB::Black);

            return true;
        }

        return false;
    }
};
