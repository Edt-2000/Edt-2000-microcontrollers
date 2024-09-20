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
    applyToLeds([](CRGB *leds) { 
      for (uint8_t i = 0; i < 59; i++) 
      {
        if (globalSettings.percentage > random8()) {
          leds[i] = globalSettings.primaryColor();
        }
        else {
          leds[i] = globalSettings.secondaryColor();
        }
      } });

    Fader.scheduleFade(globalSettings.speed / 2, globalSettings.fadeMode());

    _isActive = false;
  }
};
