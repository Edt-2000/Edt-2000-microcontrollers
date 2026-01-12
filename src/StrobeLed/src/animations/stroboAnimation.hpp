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

  bool mustRunSolo()
  {
    return true;
  }

  void start()
  {
    takeFastLedControl();
    _isActive = true;
  }

  void stop()
  {
    yieldFastLedControl();
    _isActive = false;
  }

  void loop()
  {
    do
    {
      auto color = globalSettings.primaryColor();

      if (isRainbow(color))
      {
        fill_rainbow(leds0, 64, 0, DEFAULT_DELTA_HUE);
      }
      else
      {
        fill_solid(leds0, 64, color);
      }

      // going back to black is uninterruptible, otherwise the leds might stay on full blast
      uninterruptibleShow();

      uint8_t onDelay =
          globalSettings.speed <= 5 ? 12 : globalSettings.speed <= 20 ? 6
                                                                      : 3;

      uninterruptibleDelay(onDelay);

      fill_solid(leds0, 64, CRGB::Black);

      uninterruptibleShow();

      // from this point the animation is interruptable
      delay(255 - globalSettings.speed);
      delay(255 - globalSettings.speed);
      delay(255 - globalSettings.speed);

    } while (_isActive);
  }
};
