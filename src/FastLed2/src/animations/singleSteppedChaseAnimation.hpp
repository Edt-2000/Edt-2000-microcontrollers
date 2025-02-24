#pragma once

#include "../animation.hpp"
#include "../fader.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

#include "../debugging/logger.hpp"

class SingleSteppedChaseAnimation : public Animation
{
private:
  uint8_t _state;
  uint8_t _color;

public:
  SingleSteppedChaseAnimation()
  {
    _color = 0;
  }

  const char *name()
  {
    return "singleSteppedChase";
  }

  bool mustRunSolo()
  {
    return false;
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
    _isActive = false;

    auto isUp = globalSettings.angle == 128;

    uint8_t section = 1 << _state;
    uint8_t startIndex = ledToStart(section);
    uint8_t length = ledToLength(section);

    auto color = _color == 0 ? globalSettings.primaryColor() : globalSettings.secondaryColor();

    if (isRainbow(color))
    {
      applyToLeds(
          globalSettings.led,
          [=](CRGB *leds, uint8_t index)
          {
            fill_rainbow(leds + startIndex, length, ((_color * 127) + startIndex) * DEFAULT_DELTA_HUE, DEFAULT_DELTA_HUE);
            Fader.scheduleFade(index, startIndex, length, globalSettings.speed, globalSettings.fadeMode());
          });
    }
    else
    {
      applyToLeds(
          globalSettings.led,
          [=](CRGB *leds, uint8_t index)
          {
            fill_solid(leds + startIndex, length, color);
            Fader.scheduleFade(index, startIndex, length, globalSettings.speed, globalSettings.fadeMode());
          });
    }

    _state += isUp ? -1 : 1;

    if (_state > 7) {
      _state = isUp ? 7 : 0;
      _color++;
      if (_color > 1) {
        _color = 0;
      }
    }
  }
};
