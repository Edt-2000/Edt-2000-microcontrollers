#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

#include "../leds.hpp"

class DoublePulseAnimation : public Animation
{
public:
  DoublePulseAnimation()
  {
  }

  const char *name()
  {
    return "doublePulse";
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
    auto const color1 = globalSettings.primaryColor();
    auto const color2 = globalSettings.secondaryColor();
    auto const rainbow = isRainbow(color1);

    for (uint8_t i = 0; i < 64; i++)
    {
      if (rainbow)
      {
        if (globalSettings.percentage > random8())
        {
          leds0[i] = CHSV(i * DEFAULT_DELTA_HUE, 255, 255);
        }
        else
        {
          leds0[i] = CRGB::Black;
        }
      }
      else
      {
        if (globalSettings.percentage > random8())
        {
          leds0[i] = color1;
        }
        else
        {
          leds0[i] = color2;
        }
      }
    }

    Fader.scheduleFade(0, globalSettings.speed / 2, globalSettings.fadeMode());

    _isActive = false;
  }
};
