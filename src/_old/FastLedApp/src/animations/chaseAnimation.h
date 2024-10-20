#pragma once

#include "core.h"
#include "leds.h"

class ChaseAnimation : public BaseAnimation
{
private:
    uint8_t _direction;
    uint8_t _speed;
    uint8_t _fadeSpeed;
    CRGB _color;
    uint8_t _progress = 0;

    BaseLeds *_baseLeds;

public:
    ChaseAnimation(ChaseCommand command, BaseLeds *baseLeds) : _direction(command.direction), _speed(command.speed), _fadeSpeed(command.fadeSpeed), _color(command.getColor()), _baseLeds(baseLeds)
    {
    }

    bool virtual animate(bool progressAnimation)
    {
        if (progressAnimation)
        {
            uint8_t from = _progress / 2;
            uint8_t to = (_progress / 2) + 1;

            if (to > 127)
            {
                to = 127;
            }

            if (_direction == 1)
            {
                auto start = _baseLeds->normalizeLedNrDown(127 - to);
                auto end = _baseLeds->normalizeLedNrUp(127 - from);

                fill_solid(_baseLeds->leds + start, end - start, _color);
                _baseLeds->fade(start, end, _fadeSpeed * 2, FadeMode::FadeOneByOne);
            }
            else
            {
                auto start = _baseLeds->normalizeLedNrDown(from);
                auto end = _baseLeds->normalizeLedNrUp(to);

                fill_solid(_baseLeds->leds + start, end - start, _color);
                _baseLeds->fade(start, end, _fadeSpeed * 2, FadeMode::FadeOneByOne);
            }

            if (_progress > 255 - _speed)
            {
                finished = true;
                return true;
            }

            _progress += _speed;

            return true;
        }

        return false;
    }
};
