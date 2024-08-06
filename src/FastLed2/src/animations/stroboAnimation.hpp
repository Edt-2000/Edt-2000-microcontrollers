#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

extern Settings globalSettings;
extern CRGB *led1;
extern CRGB *led2;

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
      fill_solid(led1, 1, globalSettings.alternativeColor());
      fill_solid(led2, 1, globalSettings.alternativeColor());

      uninterruptibleShow();

      uint8_t onDelay = 
        globalSettings.speed <= 5 ? 20 :
        globalSettings.speed <= 10 ? 10 : 5;        

      // going back to black is uninterruptible, otherwise the leds might stay on full blast
      uninterruptibleDelay(onDelay);
      fill_solid(led1, 1, CRGB::Black);
      fill_solid(led2, 1, CRGB::Black);
      uninterruptibleShow();

      delay(1000.0 / globalSettings.speed);

    } while (_isActive);
  }
};
