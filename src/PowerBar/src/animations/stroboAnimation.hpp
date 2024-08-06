#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

extern Settings globalSettings;
extern CRGB *leds;

class StroboAnimation : public Animation
{
public:
  StroboAnimation() {

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
    fill_solid(leds, 1, globalSettings.colors[0]);
    FastLED.show();

    delay(1);

    fill_solid(leds, 1, CRGB::Black);
    FastLED.show();

    delay(1000.0 / globalSettings.speed);

    fill_solid(leds, 1, globalSettings.colors[1]);
    FastLED.show();

    delay(1);

    fill_solid(leds, 1, CRGB::Black);
    FastLED.show();

    delay(1000.0 / globalSettings.speed);
  }
};