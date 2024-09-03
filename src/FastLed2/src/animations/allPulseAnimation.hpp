#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

#include "../leds.hpp"

extern Settings globalSettings;

class AllSparkleAnimation : public Animation
{
public:
  AllSparkleAnimation()
  {
  }

  const char *name()
  {
    return "allPulse";
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

    FastLED.show();

    Fader.scheduleFade(globalSettings.speed, FadeMode::fadeAll);

    _isActive = false;
  }
};
