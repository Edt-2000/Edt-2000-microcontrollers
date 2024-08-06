#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

extern Settings globalSettings;
extern CRGB *led1;
extern CRGB *led2;

class StopAnimation : public Animation
{
public:
  StopAnimation()
  {
  }

  const char *name()
  {
    return "stop";
  }

  bool mustRunSolo()
  {
    return true;
  }

  void start()
  {
    _isActive = true;

    fill_solid(led1, 1, CRGB::Black);
    fill_solid(led2, 1, CRGB::Black);
    FastLED.show();

    Fader.disableFade(0);
    Fader.disableFade(1);
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    fill_solid(led1, 1, CRGB::Black);
    fill_solid(led2, 1, CRGB::Black);
    FastLED.show();

    Fader.disableFade(0);
    Fader.disableFade(1);

    _isActive = false;
  }
};
