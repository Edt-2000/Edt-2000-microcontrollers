#pragma once

#include "core.h"
#include "leds.h"

extern Leds SpectacleLeds;

class SwipeAnimation : public BaseAnimation
{
private:
    uint8_t _speed;
    uint8_t _angle;
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

public:
    SwipeAnimation(SwipeCommand command) : _angle(command.angle), _speed(command.speed), _color(command.getColor())
    {
    }

    void virtual animate()
    {
        if (_progress == 255)
        {
            finished = true;
        }

        uint8_t fraction = _progress / 5;

        uint8_t currentAngle = _progressToAngle[fraction];

        uint8_t led1 = SpectacleLeds.angleLeft(currentAngle + _angle);
        uint8_t led2 = SpectacleLeds.angleLeft((255 + _angle) - currentAngle);

        uint8_t led3 = SpectacleLeds.angleRight(127 + currentAngle - _angle);
        uint8_t led4 = SpectacleLeds.angleRight(127 + (255 - _angle) - currentAngle);

        SpectacleLeds.leds[led1] = _color;
        SpectacleLeds.leds[led2] = _color;
        SpectacleLeds.fade(led1, 80, FadeMode::FadeToBlack);
        SpectacleLeds.fade(led2, 80, FadeMode::FadeToBlack);

        SpectacleLeds.leds[led3] = _color;
        SpectacleLeds.leds[led4] = _color;
        SpectacleLeds.fade(led3, 80, FadeMode::FadeToBlack);
        SpectacleLeds.fade(led4, 80, FadeMode::FadeToBlack);

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
