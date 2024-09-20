#pragma once

#include <FastLED.h>
#include "./fader.hpp"

struct Settings
{
  
  // settings
  uint8_t fade = FadeMode::fadeAll;
  uint8_t speed = 50;
  uint8_t brightness = 255;
  uint8_t percentage = 127;

  // experimental settings
  CHSV colors[5] = {CHSV(0, 255, 255), CHSV(158, 255, 255), CHSV(230, 255, 255), CHSV(0, 0, 0), CHSV(0, 0, 255)};
  uint8_t led = 0;
  uint8_t size = 10;

  inline CHSV primaryColor() { return colors[0]; }
  inline CHSV secondaryColor() { return colors[1]; }
  inline CHSV primaryAnimationColor() { return colors[2]; }
  inline CHSV secondaryAnimationColor() { return colors[3]; }
  inline CHSV alternativeColor() { return colors[4]; }

  inline FadeMode fadeMode()
  {
    if (fade >= (uint8_t)FadeMode::none && fade <= (uint8_t)FadeMode::sparkle) {
      return (FadeMode)fade;
    }
    else {
      return FadeMode::fadeAll;
    }
  }

} globalSettings;

extern Settings globalSettings;
