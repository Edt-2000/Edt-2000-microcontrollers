#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

#include "../leds.hpp"

class OneSingleAnimation : public Animation
{
public:
  OneSingleAnimation()
  {
  }

  const char *name()
  {
    return "oneSingle";
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

    if (isRainbow(color)) {
      applyToLed(globalSettings.led, [](CRGB* leds) { fill_rainbow(leds, 59, 0, DEFAULT_DELTA_HUE); });
    }
    else {
      applyToLed(globalSettings.led, [&](CRGB* leds) { fill_solid(leds, 59, color); });
    }

    Fader.scheduleFade(globalSettings.led, globalSettings.speed / 2, globalSettings.fadeMode());

    _isActive = false;
  }
};
