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
    show();
    _isActive = true;
  }

  void stop()
  {
    _isActive = false;

    fill_solid(leds, LEDS, CRGB::Black);
    show();
  }

  void loop()
  {
    animate();
  }

private:
  void animate()
  {
    do
    {
      fill_solid(leds, LEDS, globalSettings.colors[0]);

      show();

      delay(10);

      fill_solid(leds, LEDS, CRGB::Black);
      
      show();

      delay(1000.0 / globalSettings.speed);

    } while (_isActive);
  }
};