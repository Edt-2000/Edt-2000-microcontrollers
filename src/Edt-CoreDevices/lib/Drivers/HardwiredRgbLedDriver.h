#pragma once

#include <RgbLedDriver.h>
#include <Arduino.h>

namespace Drivers
{
template <int redPin, int greenPin, int bluePin>
class HardwiredRgbLedDriver : public RgbLedDriver
{
private:
public:
    void reset()
    {
        pinMode(redPin, OUTPUT);
        pinMode(greenPin, OUTPUT);
        pinMode(bluePin, OUTPUT);
    }

    void output(int r, int g, int b)
    {
        // there is no analogWrite in ESP32..
        // we will use a i2c / spi enabled darlington array anyways, so this
        // is here purely for testing
         digitalWrite(redPin, r > 30);
         digitalWrite(greenPin, g > 30);
         digitalWrite(bluePin, b > 30);
    }
};
} // namespace Drivers