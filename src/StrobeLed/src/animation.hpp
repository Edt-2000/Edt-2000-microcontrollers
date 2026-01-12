#pragma once

#include "time.hpp"

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

  // calls FastLED.show() after checking if the animation should be interrupted
  // if the animation does not delay() the animation can call FastLED.show() directly 
  inline void show() {
    Time.yield();
    FastLED.show();
  }

  // calls FastLED.show() no matter what
  // NOTE: use sparingly
  inline void uninterruptibleShow() {
    FastLED.show();
  }

  // suspends the fastLed thread so the animation can gain fastLed control
  inline void takeFastLedControl() {
    doFastLed = false;

    uint8_t max = 50;
    while (!fastLedSuspended) {
      Time.delay(1);

      // do not wait for too long -- we don't want to hang
      if (--max == 0) {
        break;
      }
    }

    // no matter how we got here, the fastLed thread should be considered stopped
    fastLedSuspended = true;
  }

  // yields fastLed control back to the fastLed thread
  // TODO: this causes some glitches due to 2 threads doing FastLED.show() at the same time
  inline void yieldFastLedControl() {
    doFastLed = true;
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
