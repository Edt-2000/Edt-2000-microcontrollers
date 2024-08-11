#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

extern Settings globalSettings;
extern CRGB *leds;

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
    // the animate function takes about 2000/speed ms (200ms if speed is 10) to complete
    // animate will be interrupted if another animation should be running
    animate();
  }

private:
  void animate()
  {
    fill_solid(leds, 640, globalSettings.colors[0]);
    FastLED.show();

    delay(1);

    fill_solid(leds, 640, CRGB::Black);
    FastLED.show();

    delay(1000.0 / globalSettings.speed);

    fill_solid(leds, 640, globalSettings.colors[1]);
    FastLED.show();

    delay(1);

    fill_solid(leds, 640, CRGB::Black);
    FastLED.show();

    delay(1000.0 / globalSettings.speed);
  }
};