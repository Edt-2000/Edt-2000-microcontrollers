#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

#include "../leds.hpp"

class PartialSingleAnimation : public Animation
{
public:
  PartialSingleAnimation()
  {
  }

  const char *name()
  {
    return "partialSingle";
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
    applyToLeds([](CRGB *leds, uint8_t index) {
      for (uint8_t i = 0; i < 59; i++) 
      {
        if (globalSettings.percentage > random8()) {
          leds[i] = globalSettings.primaryColor();
          Fader.scheduleFade(index, i, globalSettings.speed, globalSettings.fadeMode());
        }
      } });
    
    FastLED.show();

    _isActive = false;
  }
};
