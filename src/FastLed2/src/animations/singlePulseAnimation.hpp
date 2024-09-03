#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

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
    applyToLed(_led, [](CRGB* leds) { fill_solid(leds, 59, globalSettings.primaryColor()); });

    FastLED.show();

    Fader.scheduleFade(_led, globalSettings.speed, FadeMode::fadeAll);

    _isActive = false;
  }
};
