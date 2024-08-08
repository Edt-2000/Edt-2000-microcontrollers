#pragma once

#include "../animation.hpp"
#include "../settings.hpp"
#include "../time.hpp"
#include "../debugging/logger.hpp"
#include <FastLED.h>

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
    globalSettings.colors[0] = CHSV(180, 255, 255);
    globalSettings.colors[1] = CHSV(0, 255, 255);
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
      PrintLnDebug("1sec");
      _on = !_on;
    }

    fill_solid(leds, 640, _on ? globalSettings.colors[0] : globalSettings.colors[1]);
    FastLED.show(globalSettings.brightness);
  }
};