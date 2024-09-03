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
    _isActive = true;
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    do
    {
      applyToLeds([](CRGB* leds) { fill_solid(leds, 59, globalSettings.alternativeColor()); });

      // going back to black is uninterruptible, otherwise the leds might stay on full blast
      uninterruptibleShow();

      uint8_t onDelay = 
        globalSettings.speed <= 5 ? 20 :
        globalSettings.speed <= 10 ? 10 : 5;        

      uninterruptibleDelay(onDelay);
      
      applyToLeds([](CRGB* leds) { fill_solid(leds, 59, CRGB::Black); });
      
      uninterruptibleShow();

      // from this point the animation is interruptible
      delay(1000.0 / globalSettings.speed);

    } while (_isActive);
  }
};
