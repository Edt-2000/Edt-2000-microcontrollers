#pragma once

#include "core.h"
#include "leds.h"

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
        CRGB::Black,
        (CRGB)0xFF8500,
        CRGB::OrangeRed};

    BaseLeds *_baseLeds;

public:
    FireAnimation(FireCommand command, BaseLeds *baseLeds) : _speed(command.speed), _baseLeds(baseLeds)
    {
        _progress = _speed;
        _fireProgress = baseLeds->animationSeed;
    }

    bool virtual animate(bool progressAnimation)
    {
        if (progressAnimation)
        {
            for (uint8_t i = 0; i < 3; i++)
            {
                auto level = _baseLeds->level(i);

                for (uint8_t j = 0; j < _baseLeds->nrOfLedsInLevel; j++)
                {
                    _baseLeds->leds[level[j]] = CRGB::Red;
                }
            }

            if (_progress++ > _speed)
            {
                _progress = 0;

                _fireProgress++;

                for (uint8_t i = 3; i < 7; i++)
                {
                    auto level = _baseLeds->level(i);

                    for (uint8_t j = 0; j < _baseLeds->nrOfLedsInLevel; j++)
                    {
                        uint8_t c = (_fireProgress + j + i) % 7;

                        fill_solid(_baseLeds->leds + level[j], 1, _colors[c]);
                        fadeToBlackBy(_baseLeds->leds + level[j], 1, sin8(_fireProgress * 3));
                    }
                }
            }
            return true;
        }

        return false;
    }
};
