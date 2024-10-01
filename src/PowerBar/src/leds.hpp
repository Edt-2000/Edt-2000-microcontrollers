#pragma once

#include <FastLED.h>

volatile bool doFastLed = true;
volatile bool fastLedSuspended = false;

CRGB *leds = new CRGB[LEDS];
