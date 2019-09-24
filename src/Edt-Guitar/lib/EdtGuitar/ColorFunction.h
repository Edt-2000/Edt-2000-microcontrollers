#pragma once

#include "FastLED.h"

void blendColor(CRGB *leds, uint8_t nrOfLeds, uint8_t state)
{
    CRGB color = CRGB::Black;
    uint8_t fiftyFifty = 127;

    if ((state & 1) > 0)
    {
        color = blend(color, CRGB::Red, fiftyFifty);
    }

    if ((state & 2) > 0)
    {
        color = blend(color, CRGB::Orange, fiftyFifty);
    }

    if ((state & 4) > 0)
    {
        color = blend(color, CRGB::Yellow, fiftyFifty);
    }

    if ((state & 8) > 0)
    {
        color = blend(color, CRGB::Green, fiftyFifty);
    }

    if ((state & 16) > 0)
    {
        color = blend(color, CRGB::Blue, fiftyFifty);
    }

    for (uint8_t i = 0; i < nrOfLeds; i++)
    {
        leds[i] = color;
    }
};