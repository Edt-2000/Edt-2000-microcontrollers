#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

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
      fill_rainbow(leds0, 64, 0, DEFAULT_DELTA_HUE);
      Fader.scheduleFade(0, globalSettings.speed / 2, globalSettings.fadeMode());
    }
    else
    {
      fill_solid(leds0, 64, color);
      Fader.scheduleFade(0, globalSettings.speed / 2, globalSettings.fadeMode());
    }
  }
};
