#pragma once

#include <FastLED.h>
#include <AnimationType.h>

namespace Animations
{
struct Animation
{
public:
    Animation() : color(CHSV(0, 0, 0)){};
    Animation(AnimationType type, CHSV color, uint8_t data, uint8_t data2, uint8_t state) : type(type), color(color), data(data), data2(data2), state(state){};

    AnimationType type;
    CHSV color;
    uint8_t data;
    uint8_t data2;
    uint8_t state;
};
}