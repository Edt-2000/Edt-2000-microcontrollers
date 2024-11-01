#pragma once

#include <FastLED.h>
#include "./fader.hpp"

struct Settings
{
  
  // settings
  CHSV colors[2] = {CHSV(0, 255, 255), CHSV(158, 255, 255)};
  uint8_t fade = FadeMode::fadeAll;
  uint8_t percentage = 127;
  uint8_t speed = 50;
  uint8_t angle = 0;

  // experimental settings
  
  inline CHSV primaryColor() { return colors[0]; }
  inline CHSV secondaryColor() { return colors[1]; }

  inline FadeMode fadeMode()
  {
    if (fade >= (uint8_t)FadeMode::none && fade <= (uint8_t)FadeMode::pulse) {
      return (FadeMode)fade;
    }
    else {
      return FadeMode::fadeAll;
    }
  }

} globalSettings;

extern Settings globalSettings;
