#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

class StroboAnimation : public Animation
{
public:
  StroboAnimation()
  {
  }

  const char *name()
  {
    return "strobo";
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
    if (every(1000.0 / globalSettings.speed))
    {
      auto const color = globalSettings.primaryColor();

      if (isRainbow(color))
      {
        fill_rainbow(leds, 24, 0, DEFAULT_DELTA_HUE);
        Fader.disableFade();
      }
      else
      {
        fill_solid(leds, 24, color);
        Fader.disableFade();
      }

      show();

      delay(10);

      fill_solid(leds, 24, CRGB::Black);
      Fader.disableFade();

      show();

      delay(10);
    }
  }
};
