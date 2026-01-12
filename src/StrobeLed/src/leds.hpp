#pragma once

#include <FastLED.h>

#define DEFAULT_DELTA_HUE 5
#define DEFAULT_DELTA_HUE_SIDEWAYS 32

volatile bool doFastLed = true;
volatile bool fastLedSuspended = false;

CRGB leds0[64];

// universal buffer to store state for animations
uint8_t scratchpad[64];

uint8_t ledToStart(uint8_t section)
{
    if (section == 255 || (section & 1) != 0)
    {
        return 0;
    }
    else if ((section & 2) != 0)
    {
        return 7;
    }
    else if ((section & 4) != 0)
    {
        return 14;
    }
    else if ((section & 8) != 0)
    {
        return 21;
    }
    else if ((section & 16) != 0)
    {
        return 28;
    }
    else if ((section & 32) != 0)
    {
        return 35;
    }
    else if ((section & 64) != 0)
    {
        return 42;
    }
    else 
    {
        return 49;
    }
}

uint8_t ledToLength(uint8_t section)
{
    if (section == 255)
    {
        return 64;
    }
    else if ((section & 128) != 0)
    {
        return 10;
    }
    else
    {
        return 7;
    }
}

// check for magic numbers to hide some functionality in HSVs
bool isRainbow(CHSV color)
{
    return color.s == 10;
}
