#pragma once

#include "core.h"
#include "spectacleDevice.h"
#include "baseAnimation.h"

class ChaseAnimation : public BaseAnimation
{
private:
    uint8_t _direction;
    uint8_t _speed;
    uint8_t _fadeSpeed;
    CRGB _color;

    uint8_t _progress;

public:
    ChaseAnimation(ChaseCommand command) : _direction(command.direction), _speed(command.speed), _fadeSpeed(command.fadeSpeed), _color(command.getColor())
    {
    }

    void virtual animate(SpectacleDevice *device)
    {
        if (_progress > 255 - _speed)
        {
            finished = true;
            return;
        }

        _progress += _speed;

        uint8_t from = _progress / 2;
        uint8_t to = (_progress / 2) + 1;

        if (to > 127)
        {
            to = 127;
        }

        if (_direction == 1)
        {
            auto start = device->normalizeLedNrDown(127 - to);
            auto end = device->normalizeLedNrUp(127 - from);

            fill_solid(device->leds + start, end - start, _color);
            device->fade(start, end, _fadeSpeed * 2, FadeMode::FadeOneByOne);
        }
        else
        {
            auto start = device->normalizeLedNrDown(from);
            auto end = device->normalizeLedNrUp(to);

            fill_solid(device->leds + start, end - start, _color);
            device->fade(start, end, _fadeSpeed * 2, FadeMode::FadeOneByOne);
        }
    }
};
