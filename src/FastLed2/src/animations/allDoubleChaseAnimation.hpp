#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

#include "../debugging/logger.hpp"

class AllDoubleChaseAnimation : public Animation
{
private:
  uint8_t _state;
  uint8_t _step;
  uint8_t _stepSize;
  FadeMode _fadeMode;
  CRGB _color1;
  CRGB _color2;
  uint8_t _fadeSpeed;

public:
  AllDoubleChaseAnimation()
  {
  }

  const char *name()
  {
    return "allDoubleChase";
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
    _color1 = globalSettings.primaryColor();
    _color2 = globalSettings.secondaryColor();
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

      applyToLeds(
          [=](CRGB *leds, uint8_t index)
          { 
          leds[_state] = _state % 2 == 0 ? _color2 : _color1; 
          Fader.scheduleFade(index, _state, _fadeSpeed, _fadeMode); });

      _state++;

      if (_state > 58)
      {
        _isActive = false;
        return;
      }
    }
  }
};
