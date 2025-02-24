#pragma once

#include <FastLED.h>

#define DEFAULT_DELTA_HUE 25

CRGB leds[24];

// check for magic numbers to hide some functionality in HSVs
bool isRainbow(CHSV color)
{
    return color.s == 10;
}
