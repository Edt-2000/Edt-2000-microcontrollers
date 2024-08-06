#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

extern Settings globalSettings;
extern CRGB *led1;
extern CRGB *led2;

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
    fill_solid(led1, 1, globalSettings.color());
    fill_solid(led2, 1, globalSettings.color());

    FastLED.show();

    Fader.scheduleFade(0, globalSettings.speed, FadeMode::fadeAll);
    Fader.scheduleFade(1, globalSettings.speed, FadeMode::fadeAll);

    _isActive = false;
  }
};
