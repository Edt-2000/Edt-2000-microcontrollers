#pragma once

#include "core.h"
#include "leds.h"

extern Leds SpectacleLeds;

class StroboAnimation : public BaseAnimation
{
private:
    uint8_t _intensity;
    uint8_t _progress;
    CRGB _color;

public:
// TODO: accept BaseLeds*
    StroboAnimation(StroboCommand command) : _intensity(command.intensity), _color(command.getColor())
    {
        _progress = _intensity;
    }

    void virtual animate()
    {
        fill_solid(SpectacleLeds.leds, SpectacleLeds.nrOfLeds, CRGB::Black);

        if ((_progress++) > _intensity)
        {
            _progress = 0;

            fill_solid(SpectacleLeds.leds, SpectacleLeds.nrOfLeds, _color);
        }
    }
};
