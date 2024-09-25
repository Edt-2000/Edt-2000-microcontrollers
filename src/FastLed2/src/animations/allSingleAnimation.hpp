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
    auto color = globalSettings.primaryColor();

    if (isRainbow(color)) {
      applyToLeds([](CRGB* leds) { fill_rainbow(leds, 59, 0, DEFAULT_DELTA_HUE); });
    }
    else {
      applyToLeds([&](CRGB* leds) { fill_solid(leds, 59, color); });
    }

    Fader.scheduleFade(globalSettings.speed / 2, globalSettings.fadeMode());

    _isActive = false;
  }
};
