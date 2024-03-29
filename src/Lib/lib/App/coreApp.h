#pragma once

#include "blinker.h"
#include "state.h"
#include "stateMachine.h"
#include "time.h"

namespace App
{
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
    int i = 0;

    switch (_stateMachine.current())
    {
    case State::run:
      // run the app loop 1000 times before checking if it needs to be restarted
      while (++i < 1000)
      {
        time.loop();
        appLoop();
      }
      if (appRestartRequired())
      {
#ifdef ESP_H
        ESP.restart();
#endif
      }
      if (appWarningRequired())
      {
        _blinker.warning();
      }
      break;

    case State::begin:
      _blinker.begin();
      _stateMachine.step();

      Serial.println("START NETWORK");

      startSetupNetwork();

      break;

    case State::networking:
      _blinker.blink(false);
      if (setupNetwork())
      {
        _stateMachine.step();

        Serial.println("START OSC");

        startSetupOsc();
      }
      break;

    case State::specifics:
      _blinker.blink(true);
      if (setupOsc())
      {
        Serial.println("INITING");

        _stateMachine.step();
      }
      break;

    case State::initialized:
      Serial.println("INIT");

      _blinker.release();
      _stateMachine.step();

      Serial.println("APP START");

      startApp();
      break;
    }
  }

  // start network setup
  virtual void startSetupNetwork() = 0;
  // monitor network setup
  virtual bool setupNetwork() = 0;

  // start osc setup
  virtual void startSetupOsc() = 0;
  // monitor osc setup
  virtual bool setupOsc() = 0;

  // start the app
  virtual void startApp() = 0;
  // main application loop
  virtual void appLoop() = 0;

  // monitor app fail states, if true, app is reset
  virtual bool appRestartRequired() = 0;

  // monitor app warning states, if true, signal for warning
  virtual bool appWarningRequired() = 0;
};
} // namespace App