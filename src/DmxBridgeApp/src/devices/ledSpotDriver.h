#pragma once

#include "dmxCommand.h"
#include "dmxDriver.h"
#include "dmxSerial.h"

class LedSpotDriver : public DmxDriver
{
private:
    enum Mode
    {
        Uninitialized = 0,
        Color = 1,
        Strobo = 2
    } _mode;

    CRGB _color[2];

    uint8_t _stroboIntensity = 0;
    bool _stroboOn = false;

    CRGB _fadeBackup[2];

    uint8_t _fade;

    inline void switchMode(Mode mode)
    {
        if (mode == _mode)
        {
            return;
        }

        if (mode == Mode::Color)
        {
            // switch to brightness control
            DmxSerial::Write(_address, 255);
        }
        else if (mode == Mode::Strobo)
        {
            // switch to brightness control
            DmxSerial::Write(_address, 255);
        }

        _mode = mode;
    }

    inline void output()
    {
        DmxSerial::Write(_address + 1, _color[0].r);
        DmxSerial::Write(_address + 2, _color[0].g);
        DmxSerial::Write(_address + 3, _color[0].b);

        // use second color's red channel for white channel
        DmxSerial::Write(_address + 4, _color[1].r);
    }

public:
    void initialize(uint16_t address, uint8_t maximumBrightness, uint8_t minimumBrightness)
    {
        _address = address;
        _maximumBrightness = maximumBrightness;
        _minimumBrightness = minimumBrightness;

        DmxSerial::Write(_address, 0);
    }

    void loop()
    {
        if (_mode == Mode::Strobo)
        {
            if (_stroboOn)
            {
                _color[0] = CRGB::HTMLColorCode::Black;
                _color[1] = CRGB::HTMLColorCode::Black;
                _stroboOn = false;
            }
            else
            {
                if (_stroboIntensity >= 254)
                {
                    _stroboOn = true;
                    _color[0] = CRGB::HTMLColorCode::White;
                    _color[1] = CRGB::HTMLColorCode::White;
                }
                else if (_stroboIntensity / 8 > random8())
                {
                    _stroboOn = true;
                    _color[0] = CRGB::HTMLColorCode::White;
                    _color[1] = CRGB::HTMLColorCode::White;
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

                fadeToBlackBy(_color, 2, _fade);
            }

            output();
        }
    }

    void solid(CHSV color)
    {
        switchMode(Mode::Color);

        // use white led when h & s are zero (grey scale)
        if (color.h == 255)
        {
            _color[0] = CRGB::HTMLColorCode::Black;
            _color[1].r = clampValue(color).v;
        }
        else
        {
            _color[0] = clampValue(color);
            _color[1] = CRGB::HTMLColorCode::Black;
        }

        output();
    }

    void solid(CHSV color1, CHSV color2, uint8_t percentage)
    {
        switchMode(Mode::Color);

        if (percentage > random8())
        {
            _color[0] = clampValue(color2);
            _color[1] = CRGB::HTMLColorCode::Black;
        }
        else
        {
            _color[0] = clampValue(color1);
            _color[1] = CRGB::HTMLColorCode::Black;
        }

        output();
    }

    void intensity(uint8_t intensity)
    {
        switchMode(Mode::Color);

        if (intensity == 0)
        {
            _color[0] = CRGB::HTMLColorCode::Black;
        }
        else
        {
            _color[0].setHSV(85 - (intensity / 2.5), 255, intensity);
        }

        _color[1] = CRGB::HTMLColorCode::Black;

        output();
    }

    void fade(uint8_t fade, FadeMode mode = FadeMode::FadeToBlack)
    {
        _fade = fade;
    }

    void disableFade()
    {
        _fade = 255;
    }

    void strobo(CHSV color, uint8_t intensity)
    {
        if (intensity == 0)
        {
            switchMode(Mode::Color);

            _color[0] = CRGB::HTMLColorCode::Black;
            _color[1] = CRGB::HTMLColorCode::Black;
        }
        else
        {
            switchMode(Mode::Strobo);

            _stroboIntensity = 255 - intensity;

            _color[0] = CRGB::HTMLColorCode::White;
            _color[1] = CRGB::HTMLColorCode::White;
        }

        output();
    }
};
