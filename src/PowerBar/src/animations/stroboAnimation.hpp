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
    takeFastLedControl();
    _isActive = true;
  }

  void stop()
  {
    _isActive = false;

    fill_solid(leds, LEDS, CRGB::Black);

    yieldFastLedControl();
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

      uninterruptibleShow();

      uninterruptibleDelay(5);

      fill_solid(leds, LEDS, CRGB::Black);
      
      uninterruptibleShow();

      delay(1000.0 / globalSettings.speed);

    } while (_isActive);
  }
};