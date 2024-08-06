#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

extern Settings globalSettings;
extern CRGB *led1;
extern CRGB *led2;

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
    fill_solid(led1, 1, globalSettings.colors[0]);
    fill_solid(led2, 1, globalSettings.colors[0]);
    FastLED.show();

    delay(1);

    fill_solid(led1, 1, CRGB::Black);
    fill_solid(led2, 1, CRGB::Black);
    FastLED.show();

    delay(1000.0 / globalSettings.speed);

    fill_solid(led1, 1, globalSettings.colors[1]);
    fill_solid(led2, 1, globalSettings.colors[1]);
    FastLED.show();

    delay(1);

    fill_solid(led1, 1, CRGB::Black);
    fill_solid(led2, 1, CRGB::Black);
    FastLED.show();

    delay(1000.0 / globalSettings.speed);
  }
};