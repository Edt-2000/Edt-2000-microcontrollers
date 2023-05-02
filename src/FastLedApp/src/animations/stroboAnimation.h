#pragma once

#include "core.h"
#include "leds.h"

class StroboAnimation : public BaseAnimation
{
private:
    uint8_t _intensity;
    uint8_t _progress;
    CRGB _color;

    BaseLeds * _baseLeds;

public:
    StroboAnimation(StroboCommand command, BaseLeds* baseLeds) : _intensity(command.intensity), _color(command.getColor()), _baseLeds(baseLeds)
    {
        _progress = _intensity;
    }

    void virtual animate()
    {
        fill_solid(_baseLeds->leds, _baseLeds->nrOfLeds, CRGB::Black);

        if ((_progress++) > _intensity)
        {
            _progress = 0;

            FastLED.show();

            fill_solid(_baseLeds->leds, _baseLeds->nrOfLeds, _color);

            FastLED.show();
        }

        _baseLeds->show();
    }
};
