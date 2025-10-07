#pragma once

#include "time.hpp"
#include "dmx/devices.hpp"

// Base abstract animation class 
class Animation
{
protected:
  bool _isActive;

  // delay the animation for the given milliseconds
  // will interrupt and end animation automatically
  inline void delay(unsigned int ms) {
    Time.delay(ms);
  }

  // delay the animation uninterrupted
  // all other processing must wait until this is finished
  // NOTE: use sparingly
  inline void uninterruptibleDelay(unsigned int ms) {
    ::delay(ms);
  }

  // calls DmxDevices.loop() after checking if the animation should be interrupted
  // if the animation does not delay() the animation can call DmxDevices.loop() directly 
  inline void show() {
    Time.yield();
    DmxDevices.loop();
  }

  // calls DmxDevices.loop() no matter what
  // NOTE: use sparingly
  inline void uninterruptibleShow() {
    DmxDevices.loop();
  }
  
public:
  virtual const char *name() = 0;
  
  virtual bool mustRunSolo() {
    return false;
  }
  
  // start must reset the complete state of the animation
  virtual void start() = 0;

  // stop must stop the animation without breaking any code in the loop
  // as the stopping animation might have a running loop during the interrupt
  virtual void stop() = 0;

  virtual bool isActive() {
    return _isActive;
  }

  virtual void loop() = 0;
};
