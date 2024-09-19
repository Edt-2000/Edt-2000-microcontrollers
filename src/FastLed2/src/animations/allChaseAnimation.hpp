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
  uint8_t _limit;
  uint8_t _step;
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
    _limit = 25 - (globalSettings.speed / 10);
    _step = 1;
    _speed = (255 - globalSettings.speed) / 10;
    _fadeMode = globalSettings.fadeMode();
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    // this every does not work correctly if the loops are not keeping up
    // need to make it as the old chase animation (progress + speed)
    if (every(_speed)) {
      if (_state == 59) {
        _isActive = false;
        return;
      }

      // PrintDebug("Step ");
      // PrintLnDebug(_step);

      //_step--;

      //if (_step == 0) {
        _state++;
        //_step = _limit;
        
       PrintDebug("State ");
       PrintLnDebug(_state);

        auto state = _state;
        auto mode = _fadeMode;
        applyToLeds([=](CRGB* leds, uint8_t index) { 
          leds[state] = globalSettings.primaryAnimationColor(); 
          Fader.scheduleFade(index, state, 30, mode);
          });
      //}
    }


    // TODO: find a good way to get the timing correct
  //   if (every(255 - _speed)) {
  //     if (_state == 59) {
  //       _isActive = false;
  //       return;
  //     }

  //     _state++;

  //     auto state = _state;
  //     auto mode = _fadeMode;
  //     applyToLeds([state, mode](CRGB* leds, uint8_t index) { 
  //       leds[state] = globalSettings.primaryAnimationColor(); 
  //       Fader.scheduleFade(index, state, globalSettings.speed, mode);
  //       });
  //   }
  }
};
