#pragma once

#include "core.h"
#include "spectacleDevice.h"
#include "baseAnimation.h"
#include "leds.h"

extern Leds SpectacleLeds;

class FireAnimation : public BaseAnimation
{
private:
    uint8_t _speed;
    uint8_t _progress;
    uint8_t _fireProgress = 0;
    const CRGB _colors[7] = {
        (CRGB)0xFF8500,
        CRGB::Orange,
        CRGB::OrangeRed,
        CRGB::Orange,
        CRGB::Orange,
        (CRGB)0xFF8500,
        CRGB::OrangeRed
    };

public:
    FireAnimation(FireCommand command) : _speed(command.speed)
    {
        _progress = _speed;
    }

    void virtual animate()
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            auto level = SpectacleLeds.level(i);

            for (uint8_t j = 0; j < 4; j++)
            {
                SpectacleLeds.leds[level[j]] = CRGB::Red;
            }
        }

        if (_progress++ > _speed)
        {
            _progress = 0;

            _fireProgress++;

            for (uint8_t i = 3; i < 7; i++)
            {
                auto level = SpectacleLeds.level(i);

                for (uint8_t j = 0; j < 4; j++)
                {
                    uint8_t c = (_fireProgress + j + i) % 7;

                    fill_solid(SpectacleLeds.leds + level[j], 1, _colors[c]);
                    fadeToBlackBy(SpectacleLeds.leds + level[j], 1, sin8(_fireProgress * 3));
                }
            }
        }
    }
};
