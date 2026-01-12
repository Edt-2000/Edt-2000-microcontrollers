#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

#include "../leds.hpp"

class SingleChaseAnimation : public Animation
{
public:
  SingleChaseAnimation()
  {
  }

  const char *name()
  {
    return "singleChase";
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
      fill_rainbow(leds, 59, 0, DEFAULT_DELTA_HUE);
    }
    else
    {
      fill_solid(leds, 59, color);
    }
    Fader.scheduleFade(1, globalSettings.fadeMode());
  }
};
