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
    auto const color = globalSettings.primaryColor();
    auto const rainbow = isRainbow(color);

    applyToLeds(
        globalSettings.led,
        [&, rainbow](CRGB *leds, uint8_t index)
        {
          for (uint8_t i = 0; i < 59; i++)
          {
            if (globalSettings.percentage > random8())
            {
              if (rainbow)
              {
                leds[i] = CHSV(i * DEFAULT_DELTA_HUE, 255, 255);
              }
              else
              {
                leds[i] = color;
              }

              Fader.scheduleFade(index, i, globalSettings.speed / 2, globalSettings.fadeMode());
            }
          }
        });

    _isActive = false;
  }
};
