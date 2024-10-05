#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

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
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    fill_solid(leds, LEDS, CRGB::Black);
    Fader.disableFade();

    _isActive = false;
  }
};
