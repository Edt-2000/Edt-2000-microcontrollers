#pragma once

#include "../animation.hpp"
#include "../settings.hpp"
#include "../time.hpp"

extern Settings globalSettings;
extern CRGB *led1;
extern CRGB *led2;

class BlinkAnimation : public Animation
{
private:
  bool _on = false;
  int _led = 0;

public:
  BlinkAnimation(int led)
  {
    _led = led;
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

    if (_led == 0) {
      fill_solid(led1, 1, _on ? globalSettings.colors[0] : globalSettings.colors[1]);
      FastLED.show(globalSettings.brightness);
    }
    else {
      fill_solid(led2, 1, _on ? globalSettings.colors[0] : globalSettings.colors[1]);
      FastLED.show(globalSettings.brightness);
    }
  }
};