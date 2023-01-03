#pragma once

#include "core.h"
#include "spectacleDevice.h"
#include "baseAnimation.h"

class StroboAnimation : public BaseAnimation
{
private:
    uint8_t _intensity;
    uint8_t _progress;
    CRGB _color;

public:
    StroboAnimation(StroboCommand command) : _intensity(command.intensity), _color(command.getColor())
    {
        _progress = _intensity;
    }

    void virtual animate(SpectacleDevice *device)
    {
        fill_solid(device->leds, device->nrOfLeds, CRGB::Black);

        if ((_progress++) > _intensity)
        {
            _progress = 0;

            fill_solid(device->leds, device->nrOfLeds, _color);
        }
    }
};
