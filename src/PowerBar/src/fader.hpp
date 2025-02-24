#pragma once

#include "leds.hpp"

class FaderHelper
{
public:
    void fadeOnOff(int8_t progress)
    {
        if (progress < 0)
        {
            fadeToBlackBy(leds, NUM_LEDS, 255);
        }
    }

    void fadeInOut(int8_t progress)
    {
        fadeToBlackBy(leds, NUM_LEDS, cos8(progress));
    }

    void fadeSawIn(int8_t progress)
    {
        fadeToBlackBy(leds, NUM_LEDS, 255 - ((uint8_t)progress));
    }

    void fadeSawOut(int8_t progress)
    {
        fadeToBlackBy(leds, NUM_LEDS, ((uint8_t)progress));
    }

} Fader;

extern FaderHelper Fader;