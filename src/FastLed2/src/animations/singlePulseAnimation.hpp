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
    auto const color = globalSettings.primaryColor();

    if (isRainbow(color))
    {
      applyToLeds(
          globalSettings.led,
          [](CRGB *leds, uint8_t index)
          {
            fill_rainbow(leds, 59, 0, DEFAULT_DELTA_HUE);
            Fader.scheduleFade(index, globalSettings.speed / 2, globalSettings.fadeMode());
          });
    }
    else
    {
      applyToLeds(
          globalSettings.led,
          [&](CRGB *leds, uint8_t index)
          {
            fill_solid(leds, 59, color);
            Fader.scheduleFade(index, globalSettings.speed / 2, globalSettings.fadeMode());
          });
    }

    _isActive = false;
  }
};
