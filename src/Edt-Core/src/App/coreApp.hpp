#pragma once

#include "blinker.hpp"
#include "stateMachine.hpp"
#include "time.hpp"

class CoreApp
{
private:
  StateMachine _stateMachine;
  Blinker _blinker;

public:
  Time time;

  CoreApp() : _blinker(Blinker(&this->time)) {}

  inline void setup(int ledPin, int offState)
  {
    _blinker.setup(ledPin, offState);
  }

  inline void loop()
  {
    time.loop();

    switch (_stateMachine.current())
    {
    case State::run:
      appLoop();
      break;

    case State::begin:
      _blinker.begin();
      _stateMachine.step();
      startSetupNetwork();
      break;

    case State::networking:
      _blinker.blink(false);
      if (setupNetwork())
      {
        _stateMachine.step();
        startSetupOsc();
      }
      break;

    case State::specifics:
      _blinker.blink(true);
      if (setupOsc())
      {
        _stateMachine.step();
      }
      break;

    case State::initialized:
      if (_blinker.initialized())
      {
        _stateMachine.step();
        _blinker.release();
        startApp();
      }
      break;
    }
  }

  virtual void startSetupNetwork() = 0;
  virtual bool setupNetwork() = 0;

  virtual void startSetupOsc() = 0;
  virtual bool setupOsc() = 0;

  virtual void startApp() = 0;
  virtual void appLoop() = 0;
};