#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

#include "../leds.hpp"

class AllDoubleAnimation : public Animation
{
public:
  AllDoubleAnimation()
  {
  }

  const char *name()
  {
    return "allDouble";
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

    applyToLeds([&, rainbow](CRGB *leds) { 
      for (uint8_t i = 0; i < 59; i++) 
      {
        if (rainbow) {
          if (globalSettings.percentage > random8()) {
            leds[i] = CHSV(i * DEFAULT_DELTA_HUE, 255, 255); 
          }
          else {
            leds[i] = CRGB::Black;
          }
        }
        else {
          if (globalSettings.percentage > random8()) {
            leds[i] = color1;
          }
          else {
            leds[i] = color2;
          }
        }
      } });

    Fader.scheduleFade(globalSettings.speed / 2, globalSettings.fadeMode());

    _isActive = false;
  }
};
