#pragma once

// Base abstract animation class 
class Animation
{
protected:
  bool _isActive;

public:
  virtual const char *name() = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual bool isActive() {
    return _isActive;
  }
  virtual void loop() = 0;
};