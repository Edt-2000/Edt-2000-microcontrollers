#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

#include "../leds.hpp"

class AllSingleAnimation : public Animation
{
public:
  AllSingleAnimation()
  {
  }

  const char *name()
  {
    return "allSingle";
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
    applyToLeds([](CRGB* leds) { fill_solid(leds, 59, globalSettings.primaryColor()); });

    Fader.scheduleFade(globalSettings.speed / 2, globalSettings.fadeMode());

    _isActive = false;
  }
};
