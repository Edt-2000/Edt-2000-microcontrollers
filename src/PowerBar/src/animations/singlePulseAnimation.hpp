#pragma once

#include "../animation.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"

class SinglePulseAnimation : public Animation
{
public:
  SinglePulseAnimation()
  {
  }

  const char *name()
  {
    return "singlePulse";
  }

  void start()
  {
    _isActive = true;
  }

  void stop()
  {
    _isActive = false;
  }

  inline void loop()
  {
    _isActive = false;

    auto const color = globalSettings.primaryColor();

    if (isRainbow(color))
    {
      fill_rainbow(leds, NUM_LEDS, 0, DEFAULT_DELTA_HUE);
      //Fader.scheduleFade(index, globalSettings.speed / 2, globalSettings.fadeMode());
    }
    else
    {
      fill_solid(leds, NUM_LEDS, color);
      //Fader.scheduleFade(index, globalSettings.speed / 2, globalSettings.fadeMode());
    }

    show();
  }
};