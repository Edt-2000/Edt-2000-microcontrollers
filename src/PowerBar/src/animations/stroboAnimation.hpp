#pragma once

#include "../animation.hpp"
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

  void start()
  {
    show();
    _isActive = true;
  }

  void stop()
  {
    _isActive = false;

    fill_solid(leds, NUM_LEDS, CRGB::Black);
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
      fill_solid(leds, NUM_LEDS, globalSettings.colors[0]);

      show();

      delay(10);

      fill_solid(leds, NUM_LEDS, CRGB::Black);
      
      show();

      delay(255 - globalSettings.speed);
      delay(255 - globalSettings.speed);
      delay(255 - globalSettings.speed);

    } while (_isActive);
  }
};