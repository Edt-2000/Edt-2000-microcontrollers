#pragma once

#include "core.h"
#include "spectacleDevice.h"
#include "baseAnimation.h"

class FireAnimation : public BaseAnimation
{
private:
    uint8_t _speed;
    uint8_t _progress;
    uint8_t _fireProgress = 0;
    const uint8_t _fireLeds[2][7] = {
        {1, 0, 3, 11, 2, 10, 4},
        {22, 23, 13, 21, 12, 20, 14}};
    const CRGB _colors[7] = {
        CRGB::Black,
        (CRGB)0xFF8500,
        CRGB::Orange,
        CRGB::OrangeRed,
        CRGB::Orange,
        (CRGB)0xFF8500,
        CRGB::OrangeRed,
    };

public:
    FireAnimation(FireCommand command) : _speed(command.speed)
    {
        _progress = _speed;
    }

    void virtual animate(SpectacleDevice *device)
    {
        fill_solid(device->leds + 5, 5, CRGB::Red);
        fill_solid(device->leds + 15, 5, CRGB::Red);

        if (_progress++ > _speed)
        {
            _progress = 0;

            _fireProgress = (_fireProgress + 1) % 7;

            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 7; j++)
                {
                    int c = (_fireProgress + j + i) % 7;

                    fill_solid(device->leds + _fireLeds[i][j], 1, _colors[c]);
                    fadeToBlackBy(device->leds + _fireLeds[i][j], 1, sin8(_fireProgress));
                }
            }
        }
    }
};
