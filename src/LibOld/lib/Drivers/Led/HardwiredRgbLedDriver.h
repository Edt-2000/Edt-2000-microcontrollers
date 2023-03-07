#pragma once

#include "../Drivers/Led/RgbLedDriver.h"
#include <Arduino.h>

namespace Drivers
{
    namespace Led
    {
        template <int redPin, int greenPin, int bluePin>
        class HardwiredRgbLedDriver : public RgbLedDriver
        {
        private:
        public:
            HardwiredRgbLedDriver()
            {
                pinMode(redPin, OUTPUT);
                pinMode(greenPin, OUTPUT);
                pinMode(bluePin, OUTPUT);
            }

            void reset()
            {
            }

            void output(int r, int g, int b)
            {
                // there is no analogWrite on ESP32..
                // we will use a i2c / spi enabled darlington array anyways, so this
                // is here purely for testing
                // if you want to use analogWrite on ESP32, review https://github.com/espressif/arduino-esp32/issues/4
                digitalWrite(redPin, r > 30);
                digitalWrite(greenPin, g > 30);
                digitalWrite(bluePin, b > 30);
            }
        };
    }
}