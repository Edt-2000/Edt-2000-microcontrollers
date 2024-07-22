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

    Serial.println("Strobo active");
  }
};