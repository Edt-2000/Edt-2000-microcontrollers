#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

extern Settings globalSettings;
extern CRGB *leds;

class BlinkAnimation : public Animation
{
public:
  BlinkAnimation() {

  }

  const char *name()
  {
    return "blink";
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

    Serial.println("Blink active");
  }
};