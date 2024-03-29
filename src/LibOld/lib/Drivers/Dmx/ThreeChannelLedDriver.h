#pragma once

#include "DmxDriver.h"
#include "FadeMode.h"
#include "DmxSerial.h"

namespace Drivers
{
    namespace Dmx
    {
        class ThreeChannelLedDriver : public DmxDriver
        {
        private:
            enum Mode
            {
                Uninitialized = 0,
                Color = 1,
                Strobo = 2
            } _mode;

            CRGB _color;
            CRGB _colorBackup;

            uint8_t _fade;

            uint8_t _stroboIntensity = 0;
            bool _stroboOn = false;

            inline void switchMode(Mode mode)
            {
                _mode = mode;
            }

            inline void output()
            {
                DmxSerial::Write(_address + 0, _color.r);
                DmxSerial::Write(_address + 1, _color.g);
                DmxSerial::Write(_address + 2, _color.b);
            }

        public:
            void initialize(uint16_t address, uint8_t maximumBrightness, uint8_t minimumBrightness)
            {
                _address = address;
                _maximumBrightness = maximumBrightness;
                _minimumBrightness = minimumBrightness;

                _color = CRGB::HTMLColorCode::Black;

                output();
            }

            void loop()
            {
                // this is an random strobo since each dmx device is somewhere and could be different
                if (_mode == Mode::Strobo)
                {
                    if (_stroboOn)
                    {
                        _color = CRGB::HTMLColorCode::Black;
                        _stroboOn = false;
                    }
                    else
                    {
                        if (_stroboIntensity / 8 > random8())
                        {
                            _stroboOn = true;
                            _color = _colorBackup;
                        }
                    }

                    output();
                }
                else if (_mode == Mode::Color)
                {
                    if (_fade < 255)
                    {
                        if (_fade > 255 - 62)
                        {
                            _fade = 255;
                        }
                        else
                        {
                            _fade += ((_fade) / 4) + 1;
                        }

                        fadeToBlackBy(&_color, 1, _fade);
                    }

                    output();
                }
            }

            void solid(uint8_t h, uint8_t s, uint8_t v)
            {
                switchMode(Mode::Color);

                _color.setHSV(h, s, clampValue(v));

                output();
            }

            void solid(uint8_t h1, uint8_t h2, uint8_t s, uint8_t v, uint8_t percentage)
            {
                switchMode(Mode::Color);

                if (percentage > random8())
                {
                    _color.setHSV(h2, s, clampValue(v));
                }
                else
                {
                    _color.setHSV(h1, s, clampValue(v));
                }

                output();
            }

            void intensity(uint8_t intensity)
            {
                switchMode(Mode::Color);

                if (intensity == 0)
                {
                    _color = CRGB::HTMLColorCode::Black;
                }
                else
                {
                    _color.setHSV(85 - (intensity / 2.5), 255, clampValue(intensity));
                }

                output();
            }

            void fade(uint8_t fade, Animations::FadeMode mode = Animations::FadeMode::FadeToBlack)
            {
                _fade = fade;
            }

            void disableFade()
            {
                _fade = 255;
            }

            void strobo(uint8_t h, uint8_t intensity)
            {
                _color = CRGB::HTMLColorCode::Black;

                if (intensity == 0)
                {
                    switchMode(Mode::Color);
                }
                else
                {
                    switchMode(Mode::Strobo);

                    _colorBackup.setHSV(h, 255, 255);
                    _stroboIntensity = intensity;
                }

                output();
            }
        };
    }
}