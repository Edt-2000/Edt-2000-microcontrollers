#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../debugging/logger.hpp"

extern Settings globalSettings;
extern CRGB *led1;
extern CRGB *led2;

class AllSolidAnimation : public Animation
{
public:
  AllSolidAnimation()
  {
  }

  const char *name()
  {
    return "allSolid";
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

    Fader.disableFade(0);
    Fader.disableFade(1);

    _isActive = false;
  }
};
