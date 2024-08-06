#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

extern Settings globalSettings;
extern CRGB *led1;
extern CRGB *led2;

class SinglePulseAnimation : public Animation
{
private:
  uint8_t _led;

public:
  SinglePulseAnimation()
  {
  }

  const char *name()
  {
    return "singlePulse";
  }

  void start()
  {
    _isActive = true;
    _led = globalSettings.led;
  }

  void stop()
  {
    _isActive = false;
  }

  inline void loop()
  {
    fill_solid(_led == 0 ? led1 : led2, 1, globalSettings.color());

    FastLED.show();

    Fader.scheduleFade(_led, globalSettings.speed, FadeMode::fadeAll);

    _isActive = false;
  }
};
