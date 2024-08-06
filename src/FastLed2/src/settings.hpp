#pragma once

#include <FastLED.h>

struct Settings
{
  CHSV colors[5] = {CHSV(0, 255, 255), CHSV(158, 255, 255), CHSV(230, 255, 255), CHSV(0, 0, 0), CHSV(0, 0, 255)};
  uint8_t led = 0;
  uint8_t colorIndex = 0;
  uint8_t speed = 10;
  uint8_t brightness = 255;
  uint8_t size = 10;

  inline CHSV primaryColor() { return colors[0]; }
  inline CHSV secondaryColor() { return colors[1]; }
  inline CHSV primaryAnimationColor() { return colors[2]; }
  inline CHSV secondaryAnimationColor() { return colors[3]; }
  inline CHSV alternativeColor() { return colors[4]; }

  inline CHSV color() { return colors[colorIndex > 0 ? 1 : 0]; }
  inline CHSV animationColor() { return colors[colorIndex > 0 ? 3 : 2]; }

} globalSettings;

extern Settings globalSettings;
