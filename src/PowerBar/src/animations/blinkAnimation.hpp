#pragma once

#include "../animation.hpp"
#include "../settings.hpp"
#include <FastLED.h>

extern Settings globalSettings;
extern CRGB *leds;

class BlinkAnimation : public Animation
{
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

    globalSettings.colors[0] = CHSV(158, 255, 255);
    globalSettings.colors[1] = CHSV(0, 255, 255);

    fill_solid(leds, 640, globalSettings.colors[1]);
    FastLED.show(globalSettings.brightness);
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    // every is true once every interval (this case once every 250ms)
    // so the animation is progressed 4 times per second
    if (every(250))
    {
      tick();
    }
  }

private:
  bool _on = false;

  void tick()
  {
    _on = !_on;

    fill_solid(leds, 640, _on ? globalSettings.colors[0] : globalSettings.colors[1]);
    FastLED.show(globalSettings.brightness);
  }
};