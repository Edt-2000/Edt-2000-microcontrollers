#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

#include "../leds.hpp"

class SinglePartialPulseAnimation : public Animation
{
public:
  SinglePartialPulseAnimation()
  {
  }

  const char *name()
  {
    return "singlePartialPulse";
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
    auto const rainbow = isRainbow(color);

    for (uint8_t i = 0; i < 64; i++)
    {
      if (globalSettings.percentage > random8())
      {
        if (rainbow)
        {
          leds0[i] = CHSV(i * DEFAULT_DELTA_HUE, 255, 255);
        }
        else
        {
          leds0[i] = color;
        }

        Fader.scheduleFade(0, i, globalSettings.speed / 2, globalSettings.fadeMode());
      }
    }
  }
};
