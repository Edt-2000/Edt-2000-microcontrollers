#pragma once

#include "../animation.hpp"
#include "../settings.hpp"
#include "../time.hpp"

extern Settings globalSettings;
extern CRGB *leds;

class BlinkAnimation : public Animation
{
private:
  bool _on = false;

public:
  BlinkAnimation()
  {
  }

  const char *name()
  {
    return "blink";
  }

  void start()
  {
    _isActive = true;

    _on = false;
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    if (Time.t1000ms)
    {
      _on = !_on;
    }

    fill_solid(leds, 1, _on ? globalSettings.colors[0] : globalSettings.colors[1]);
    FastLED.show(globalSettings.brightness);
  }
};