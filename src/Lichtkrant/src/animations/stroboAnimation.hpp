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
    if (!_isActive) {
        return;
    }

    fill_solid(leds, 1, globalSettings.colors[0]);
    FastLED.show();

    Time.delay(1);

    fill_solid(leds, 1, CRGB::Black);
    FastLED.show();

    Time.delay(1000 / globalSettings.speed);

    fill_solid(leds, 1, globalSettings.colors[1]);
    FastLED.show();

    Time.delay(1);

    fill_solid(leds, 1, CRGB::Black);
    FastLED.show();

    Time.delay(1000 / globalSettings.speed);
  }
};