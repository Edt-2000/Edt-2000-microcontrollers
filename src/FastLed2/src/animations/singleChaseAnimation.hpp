#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

#include "../debugging/logger.hpp"

class SingleChaseAnimation : public Animation
{
private:
  uint8_t _state;
  uint8_t _step;
  uint8_t _stepSize;
  uint8_t _led;
  FadeMode _fadeMode;
  CHSV _color;
  uint8_t _fadeSpeed;

public:
  SingleChaseAnimation()
  {
  }

  const char *name()
  {
    return "singleChase";
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
    _led = globalSettings.led;
    _fadeMode = globalSettings.fadeMode();
    _color = globalSettings.primaryColor();
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

      if (isRainbow(_color))
      {
        applyToLeds(
            _led,
            [=](CRGB *leds, uint8_t index)
            {
              leds[_state] = CHSV(_state * DEFAULT_DELTA_HUE, 255, 255);
              Fader.scheduleFade(index, _state, _fadeSpeed, _fadeMode);
            });
      }
      else
      {
        applyToLeds(
            _led,
            [=](CRGB *leds, uint8_t index)
            {
              leds[_state] = _color;
              Fader.scheduleFade(index, _state, _fadeSpeed, _fadeMode);
            });
      }

      _state++;

      if (_state > 58)
      {
        _isActive = false;
        return;
      }
    }
  }
};
