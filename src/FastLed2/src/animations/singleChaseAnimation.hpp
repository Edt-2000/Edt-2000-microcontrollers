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
  uint8_t _angle;

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
    auto isHorizontal = (_angle == 64 || _angle == 192);

    _isActive = true;
    _step = 255;
    _stepSize = 1 + (globalSettings.speed / (isHorizontal ? 10 : 5));
    _fadeMode = globalSettings.fadeMode();
    _color = globalSettings.primaryColor();
    _fadeSpeed = globalSettings.speed / (isHorizontal ? 1 : 2);

    _led = globalSettings.led;
    _angle = globalSettings.angle;

    _state = _angle == 64 ? 7 : _angle == 128 ? 58 : 0;
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
      auto isLeft = _angle == 64;
      auto isRight = _angle == 192;

      if (isLeft || isRight)
      {
        int startIndex = ledToStart(_led);
        int length = ledToLength(_led);

        if (isRainbow(_color))
        {
          applyToLeds(
              1 << _state,
              [=](CRGB *leds, uint8_t index)
              {
                fill_solid(leds + startIndex, length, CHSV(_state * DEFAULT_DELTA_HUE_SIDEWAYS, 255, 255));
                Fader.scheduleFade(index, startIndex, length, _fadeSpeed, _fadeMode);
              });
        }
        else
        {
          applyToLeds(
              1 << _state,
              [=](CRGB *leds, uint8_t index)
              {
                fill_solid(leds + startIndex, length, _color);
                Fader.scheduleFade(index, startIndex, length, _fadeSpeed, _fadeMode);
              });
        }

        _state += isLeft ? -1 : 1;

        // when going right, the last led will be 7
        // when going left, the last led will be 0 so 0 - 1 == 255 which is also > 7
        if (_state > 7)
        {
          _isActive = false;
          return;
        }
      }
      else
      {
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

        _state += isUp ? -1 : 1;

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
