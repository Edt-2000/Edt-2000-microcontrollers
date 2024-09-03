#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

class GlowAnimation : public Animation
{
private:
  uint8_t _state;
  uint8_t _led;

public:
  GlowAnimation(uint8_t led)
  {
    _led = led;
  }

  const char *name()
  {
    return "glow";
  }

  bool mustRunSolo()
  {
    return true;
  }

  void start()
  {
    _isActive = true;
    _state = 0;
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    if (every(40)) {
      _state++;

      if (_led == 0) {
        fill_solid(leds1, 1, globalSettings.alternativeColor());
        leds1[0].fadeToBlackBy(sin8(_state));
        Fader.disableFade(0);
      } 
      else {
        fill_solid(leds2, 1, globalSettings.alternativeColor());
        leds2[0].fadeToBlackBy(sin8(_state));
        Fader.disableFade(1);
      }

      FastLED.show();
    }
  }
};
