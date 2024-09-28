#pragma once

#include <FastLED.h>

#define DEFAULT_DELTA_HUE 5
#define DEFAULT_DELTA_HUE_SIDEWAYS 32

volatile bool doFastLed = true;
volatile bool fastLedSuspended = false;

CRGB leds0[59];
CRGB leds1[59];
CRGB leds2[59];
CRGB leds3[59];
CRGB leds4[59];
CRGB leds5[59];
CRGB leds6[59];
CRGB leds7[59];

// universal buffer to store state for animations
uint8_t scratchpad[8][59];

void applyToLeds(std::function<void(CRGB[])> action)
{
    action(leds0);
    action(leds1);
    action(leds2);
    action(leds3);
    action(leds4);
    action(leds5);
    action(leds6);
    action(leds7);
}

void applyToLeds(std::function<void(CRGB[], uint8_t)> action)
{
    action(leds0, 0);
    action(leds1, 1);
    action(leds2, 2);
    action(leds3, 3);
    action(leds4, 4);
    action(leds5, 5);
    action(leds6, 6);
    action(leds7, 7);
}

void applyToLeds(uint8_t led, std::function<void(CRGB[])> action)
{
    if ((led & 1) != 0)
    {
        action(leds0);
    }
    if ((led & 2) != 0)
    {
        action(leds1);
    }
    if ((led & 4) != 0)
    {
        action(leds2);
    }
    if ((led & 8) != 0)
    {
        action(leds3);
    }
    if ((led & 16) != 0)
    {
        action(leds4);
    }
    if ((led & 32) != 0)
    {
        action(leds5);
    }
    if ((led & 64) != 0)
    {
        action(leds6);
    }
    if ((led & 128) != 0)
    {
        action(leds7);
    }
}

void applyToLeds(uint8_t led, std::function<void(CRGB[], uint8_t)> action)
{
    if ((led & 1) != 0)
    {
        action(leds0, 0);
    }
    if ((led & 2) != 0)
    {
        action(leds1, 1);
    }
    if ((led & 4) != 0)
    {
        action(leds2, 2);
    }
    if ((led & 8) != 0)
    {
        action(leds3, 3);
    }
    if ((led & 16) != 0)
    {
        action(leds4, 4);
    }
    if ((led & 32) != 0)
    {
        action(leds5, 5);
    }
    if ((led & 64) != 0)
    {
        action(leds6, 6);
    }
    if ((led & 128) != 0)
    {
        action(leds7, 7);
    }
}

uint8_t ledToStart(uint8_t led)
{
    if (led == 255 || (led & 1) != 0)
    {
        return 0;
    }
    else if ((led & 2) != 0)
    {
        return 7;
    }
    else if ((led & 4) != 0)
    {
        return 14;
    }
    else if ((led & 8) != 0)
    {
        return 21;
    }
    else if ((led & 16) != 0)
    {
        return 28;
    }
    else if ((led & 32) != 0)
    {
        return 35;
    }
    else if ((led & 64) != 0)
    {
        return 42;
    }
    else 
    {
        return 49;
    }
}

uint8_t ledToLength(uint8_t led)
{
    if (led == 255)
    {
        return 59;
    }
    else if ((led & 128) != 0)
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
