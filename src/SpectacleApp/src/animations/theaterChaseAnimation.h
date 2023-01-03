#pragma once

#include "core.h"
#include "spectacleDevice.h"
#include "baseAnimation.h"

class TheaterChaseAnimation : public BaseAnimation
{
private:
    uint8_t _speed;
    uint8_t _progress;
    uint8_t _chaseProgress = 0;
    CRGB _color1;
    CRGB _color2;

public:
    TheaterChaseAnimation(TheatreChaseCommand command) : _speed(command.speed), _color1(command.getColor1()), _color2(command.getColor2())
    {
        _progress = _speed;
    }

    void virtual animate(SpectacleDevice *device)
    {
        if (_progress++ > _speed)
        {
            _progress = 0;

            _chaseProgress++;
            int offset = _chaseProgress % 2;

            fill_solid(device->leds, device->nrOfLeds, CRGB::Black);

            for (int i = offset; i < 12; i = i + 2)
            {
                fill_solid(device->leds + i, 1, _color1);
            }
            for (int i = offset + 12; i < 24; i = i + 2)
            {
                fill_solid(device->leds + i, 1, _color2);
            }
        }
    }
};
