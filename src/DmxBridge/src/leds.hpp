#pragma once

#include <FastLED.h>

#define DEFAULT_DELTA_HUE 5
#define DEFAULT_DELTA_HUE_SIDEWAYS 32

CRGB leds[59];

// universal buffer to store state for animations
uint8_t scratchpad[59];

// check for magic numbers to hide some functionality in HSVs
bool isRainbow(CHSV color)
{
    return color.s == 10;
}
