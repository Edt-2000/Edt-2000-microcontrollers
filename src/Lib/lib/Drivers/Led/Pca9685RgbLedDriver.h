#pragma once

#include "../Drivers/Led/RgbLedDriver.h"
#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

namespace Drivers
{
    namespace Led
    {
        template <int address, int numberOfLeds>
        class Pca9685RgbLedDriver : public RgbLedDriver
        {
        private:
            Adafruit_PWMServoDriver _pwms[numberOfLeds / 4];

            int _currentLed = 0;
            int _currentDevice = 0;

            int _outputs[4][3] = {{1, 2, 0}, {4, 5, 3}, {9, 10, 8}, {12, 13, 11}};

            inline int mapValue(int input)
            {
                return input == 0 ? 0 : (input * 16) + 15;
            }

        public:
            Pca9685RgbLedDriver()
            {
                int delta = 0;
                for (auto &pwm : _pwms)
                {
                    pwm = Adafruit_PWMServoDriver(address + delta);

                    pwm.begin();
                    pwm.setPWMFreq(1600);

                    delta++;
                }
            }

            void reset()
            {
                _currentLed = 0;
                _currentDevice = 0;
            }

            void output(int r, int g, int b)
            {
                if (_currentLed > 3)
                {
                    _currentDevice++;
                    _currentLed = 0;
                }

                if (_currentDevice > numberOfLeds / 4)
                {
                    _currentDevice = 0;
                }

                // scale 0-255 to 15-4095
                _pwms[_currentDevice].setPin(_outputs[_currentLed][0], mapValue(r));
                _pwms[_currentDevice].setPin(_outputs[_currentLed][1], mapValue(g));
                _pwms[_currentDevice].setPin(_outputs[_currentLed][2], mapValue(b));

                _currentLed++;
            }
        };
    }
}