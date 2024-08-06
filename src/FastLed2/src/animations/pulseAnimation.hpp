#pragma once

#include "../animation.hpp"
#include "../settings.hpp"
#include "../time.hpp"

#include "../debugging/logger.hpp"

extern Settings globalSettings;
extern CRGB *led1;
extern CRGB *led2;

class PulseAnimation : public Animation
{
private:
  uint8_t _fade = 0;
  uint8_t _speed = 0;
  uint8_t _led = 0;

public:
  PulseAnimation(int led)
  {
    _led = led;
  }

  const char *name()
  {
    return "pulse";
  }

  void start()
  {
    _isActive = true;
    _speed = globalSettings.speed;
    _fade = 0;

    if (_led == 0)
    {
      fill_solid(led1, 1, globalSettings.colors[0]);
    }
    else
    {
      fill_solid(led2, 1, globalSettings.colors[1]);
    }
    FastLED.show(globalSettings.brightness);
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    if (Time.t10ms)
    {
      if ( _fade >= 255 - _speed) {
        PrintDebug("Animation ");
        PrintDebug(_led);
        PrintLnDebug(" done!");
        
        _isActive = false;
      }

      _fade += _speed;

      if (_led == 0)
      {
        fadeToBlackBy(led1, 1, _fade);
      }
      else
      {
        fadeToBlackBy(led2, 1, _fade);
      }
      
      FastLED.show(globalSettings.brightness);
    }

  }
};