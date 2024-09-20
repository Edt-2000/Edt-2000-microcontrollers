#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

#include "../debugging/logger.hpp"

class AllChaseAnimation : public Animation
{
private:
  uint8_t _state;
  uint8_t _step;
  uint8_t _stepSize;
  FadeMode _fadeMode;
  CRGB _color;
  uint8_t _fadeSpeed;

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
    _step = 0;
    _stepSize = 1 + (globalSettings.speed / 5);
    _fadeMode = globalSettings.fadeMode();
    _color = globalSettings.primaryAnimationColor();
    _fadeSpeed = globalSettings.speed / 2;
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    if (Time.t1ms)
    {
      _step = qadd8(_step, _stepSize);
      if (_step != 255)
      {
        return;
      }

      _step = 0;

      auto state = _state;
      auto mode = _fadeMode;
      auto fadeSpeed = _fadeSpeed;

      applyToLeds(
          [=](CRGB *leds, uint8_t index)
          { 
          leds[state] = _color; 
          Fader.scheduleFade(index, state, fadeSpeed, mode); });

      _state++;

      if (_state > 58)
      {
        _isActive = false;
        return;
      }
    }
  }
};
