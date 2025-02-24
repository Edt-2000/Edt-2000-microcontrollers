#pragma once

#include "../animation.hpp"
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
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    show();

    _isActive = false;
  }
};
