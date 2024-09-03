#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

class AllChaseAnimation : public Animation
{
private:
  uint8_t _state;
  uint8_t _speed;
  FadeMode _fadeMode;

public:
  AllChaseAnimation()
  {
  }

  const char *name()
  {
    return "allChase";
  }

  bool mustRunSolo()
  {
    return false;
  }

  void start()
  {
    _isActive = true;
    _state = 0;
    _speed = globalSettings.speed;
    _fadeMode = globalSettings.fadeMode();
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    // TODO: find a good way to get the timing correct
    if (every(255 - _speed)) {
      if (_state == 59) {
        _isActive = false;
        return;
      }

      _state++;

      auto state = _state;
      auto mode = _fadeMode;
      applyToLeds([state, mode](CRGB* leds, uint8_t index) { 
        leds[state] = globalSettings.primaryAnimationColor(); 
        Fader.scheduleFade(index, state, globalSettings.speed, mode);
        });

      FastLED.show();
    }
  }
};
