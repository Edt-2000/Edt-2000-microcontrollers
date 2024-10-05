#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

#include "../debugging/logger.hpp"

class DoubleChaseAnimation : public Animation
{
private:
  uint8_t _state;
  uint8_t _step;
  uint8_t _stepSize;
  uint8_t _led;
  FadeMode _fadeMode;
  CHSV _color1;
  CHSV _color2;
  uint8_t _fadeSpeed;
  uint8_t _angle;

public:
  DoubleChaseAnimation()
  {
  }

  const char *name()
  {
    return "doubleChase";
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
    
    _led = globalSettings.led;
    _angle = globalSettings.angle;

    _state = _angle == 128 ? 58 : 0;
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

      auto isUp = _angle == 128;
      auto isDown = !isUp;

      if (isUp || isDown)
      {
        if (isRainbow(_color1))
        {
          applyToLeds(
              _led,
              [=](CRGB *leds, uint8_t index)
              {
                leds[_state] = CHSV(((_state / 3) % 2 == 0 ? (_state + 127) : _state) * DEFAULT_DELTA_HUE, 255, 255);
                Fader.scheduleFade(index, _state, _fadeSpeed, _fadeMode);
              });
        }
        else
        {
          applyToLeds(
              _led,
              [=](CRGB *leds, uint8_t index)
              {
                leds[_state] = (_state / 3) % 2 == 0 ? _color2 : _color1;
                Fader.scheduleFade(index, _state, _fadeSpeed, _fadeMode);
              });
        }

        _state += isDown ? 1 : -1;

        // when going down, the last led will be 58
        // when going up, the last led will be 0 so 0 - 1 == 255 which is also > 58
        if (_state > 58)
        {
          _isActive = false;
          return;
        }
      }
    }
  }
};
