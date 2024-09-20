#pragma once

#include <FastLED.h>
#include <vector>

#include "./debugging/logger.hpp"

#include "./leds.hpp"

enum FadeMode : uint8_t
{
    none,
    fadeAll,
    oneByOne,
    sparkle
};

struct FadeState
{
    FadeState() : speed(0), mode(FadeMode::oneByOne) {};
    FadeState(uint8_t speed, FadeMode mode) : speed(speed), mode(mode) {};

    uint8_t speed;
    FadeMode mode;
};

class FaderHelper
{
private:
    std::vector<CRGB *> _leds;
    std::vector<std::vector<FadeState>> _fades;

public:
    FaderHelper()
    {
        _leds.resize(8);
        _leds[0] = leds0;
        _leds[1] = leds1;
        _leds[2] = leds2;
        _leds[3] = leds3;
        _leds[4] = leds4;
        _leds[5] = leds5;
        _leds[6] = leds6;
        _leds[7] = leds7;
        _fades.resize(8, std::vector<FadeState>(59));
    }

    void loop()
    {
        uint8_t ledMax = _fades.size();
        for (uint8_t led = 0; led < ledMax; led++)
        {
            auto states = _fades[led];
            uint8_t iMax = states.size();
            for (uint8_t i = 0; i < iMax; i++)
            {
                auto state = states[i];

                if (state.speed > 0)
                {
                    if (state.mode == FadeMode::fadeAll)
                    {
                        fadeToBlackBy(_leds[led] + i, 1, state.speed);
                    }
                    else if (state.mode == FadeMode::oneByOne)
                    {
                        if (random8() < state.speed)
                        {
                            _leds[led][i] = CRGB::Black;
                        }
                        else
                        {
                            fadeToBlackBy(_leds[led] + i, 1, 1);
                        }
                    }
                    else if (state.mode == FadeMode::sparkle)
                    {
                        if (state.speed == 255)
                        {
                            _fades[led][i].speed = 0;
                            _leds[led][i] = CRGB::Black;
                        }
                        else if (random8() < state.speed)
                        {
                            _fades[led][i].speed = 255;
                            _leds[led][i] = CRGB::White;
                        }
                        else
                        {
                            fadeToBlackBy(_leds[led] + i, 1, 1);
                        }
                    }
                }
            }
        }
    }

    inline void scheduleFade(uint8_t led, uint8_t index, uint8_t speed, FadeMode mode)
    {
        if (_leds[led][index] == CRGB::Black)
        {
            auto newState = FadeState(0, mode);
            _fades[led][index] = newState;
        }
        else
        {
            auto newState = FadeState(speed, mode);
            _fades[led][index] = newState;
        }
    }

    void scheduleFade(uint8_t led, uint8_t speed, FadeMode mode)
    {
        if (mode == FadeMode::none)
        {
            disableFade(led);
            return;
        }

        uint8_t size = _fades[led].size();
        for (uint8_t i = 0; i < size; i++)
        {
            scheduleFade(led, i, speed, mode);
        }
    }

    void scheduleFade(uint8_t speed, FadeMode mode)
    {
        if (mode == FadeMode::none)
        {
            disableFade();
            return;
        }

        uint8_t leds = _fades.size();
        for (uint8_t led = 0; led < leds; led++)
        {
            uint8_t size = _fades[led].size();
            for (uint8_t i = 0; i < size; i++)
            {
                scheduleFade(led, i, speed, mode);
            }
        }
    }

    void disableFade(uint8_t led)
    {
        uint8_t size = _fades[led].size();
        for (uint8_t i = 0; i < size; i++)
        {
            scheduleFade(led, i, 0, FadeMode::none);
        }
    }

    void disableFade()
    {
        uint8_t leds = _fades.size();
        for (uint8_t led = 0; led < leds; led++)
        {
            uint8_t size = _fades[led].size();
            for (uint8_t i = 0; i < size; i++)
            {
                scheduleFade(led, i, 0, FadeMode::none);
            }
        }
    }
} Fader;

extern FaderHelper Fader;
