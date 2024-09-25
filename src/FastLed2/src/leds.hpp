#pragma once

#include <FastLED.h>

#define DEFAULT_DELTA_HUE 5

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

void applyToLed(uint8_t led, std::function<void(CRGB[])> action)
{
    switch (led)
    {
    case 7:
        action(leds7);
        break;
    case 6:
        action(leds6);
        break;
    case 5:
        action(leds5);
        break;
    case 4:
        action(leds4);
        break;
    case 3:
        action(leds3);
        break;
    case 2:
        action(leds2);
        break;
    case 1:
        action(leds1);
        break;
    default:
        action(leds0);
        break;
    }
}

// check for magic numbers to hide some functionality in HSVs
bool isRainbow(CHSV color) {
    return color.s == 10;
}
