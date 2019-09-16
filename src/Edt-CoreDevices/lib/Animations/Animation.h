#pragma once

#include <FastLED.h>
#include <AnimationType.h>

namespace Animations
{
struct Animation
{
public:
    Animation() : color(CHSV(0, 0, 0)){};
    Animation(AnimationType type, CHSV color, uint8_t data, uint8_t state) : type(type), color(color), data(data), state(state){};

    AnimationType type;
    CHSV color;
    uint8_t data;
    uint8_t state;
};
}