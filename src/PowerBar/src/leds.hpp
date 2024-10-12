#pragma once

#include <FastLED.h>

#define DEFAULT_DELTA_HUE 1

CRGB *leds = new CRGB[NUM_LEDS];

// check for magic numbers to hide some functionality in HSVs
bool isRainbow(CHSV color)
{
    return color.s == 10;
}
