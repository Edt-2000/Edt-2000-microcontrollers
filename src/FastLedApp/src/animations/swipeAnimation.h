#pragma once

#include "core.h"
#include "leds.h"

class SwipeAnimation : public BaseAnimation
{
private:
    uint8_t _angle;
    uint8_t _speed;
    CRGB _color;

    uint8_t _progress = 0;

    const uint8_t _progressToAngle[52]{
        0,
        16,
        22,
        27,
        32,
        36,
        39,
        43,
        46,
        48,
        51,
        54,
        56,
        59,
        61,
        63,
        66,
        68,
        70,
        72,
        74,
        76,
        78,
        80,
        82,
        84,
        85,
        87,
        89,
        91,
        93,
        94,
        96,
        98,
        99,
        101,
        103,
        104,
        106,
        108,
        109,
        111,
        113,
        114,
        116,
        117,
        119,
        121,
        122,
        124,
        125,
        127};
        
    BaseLeds *_baseLeds;

public:
    SwipeAnimation(SwipeCommand command, BaseLeds* baseLeds) : _angle(command.angle), _speed(command.speed), _color(command.getColor()), _baseLeds(baseLeds)
    {
    }

    void virtual animate()
    {
        if (_progress == 255)
        {
            finished = true;
        }

        uint8_t offset = map(_angle, 0, 255, 255 - (32 * _baseLeds->index), (32 * _baseLeds->index));

        uint8_t fraction = (_progress + offset);

        // uint8_t currentAngle = _progressToAngle[fraction] * 2;

        uint8_t led1 = _baseLeds->angleLeft(fraction);
        
        _baseLeds->leds[led1] = _color;
        _baseLeds->fade(led1, 80, FadeMode::FadeToBlack);
        
        if (_progress > 255 - _speed)
        {
            _progress = 255;
        }
        else
        {
            _progress += _speed;
        }
    }
};
