#pragma once

#include <RgbLedDriver.h>
#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

namespace Drivers
{
template <int address>
class Pca9685RgbLedDriver : public RgbLedDriver
{
private:
    Adafruit_PWMServoDriver _pwm = Adafruit_PWMServoDriver(address);
    int _i = 0;

    void setPin(int value)
    {
        if (_i > 15)
        {
            reset();
        }

        // scale 0-255 to 0-4095
        _pwm.setPin(_i++, value * 16);
    }

public:
    Pca9685RgbLedDriver()
    {
        _pwm.begin();
        _pwm.setPWMFreq(1600);
    }

    void reset()
    {
        _i = 0;
    }

    void output(int r, int g, int b)
    {
        setPin(r);
        setPin(g);
        setPin(b);
    }
};
} // namespace Drivers