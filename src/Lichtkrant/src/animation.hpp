#pragma once

// Base abstract animation class 
class Animation
{
protected:
  bool _isActive;

public:
  virtual const char *name() = 0;

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