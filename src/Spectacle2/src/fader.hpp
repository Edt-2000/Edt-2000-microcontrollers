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
    std::vector<FadeState> _fades = std::vector<FadeState>(LEDS);

public:
    FaderHelper()
    {
    }

    void loop()
    {
        uint8_t iMax = _fades.size();
        for (uint8_t i = 0; i < iMax; i++)
        {
            auto state = _fades[i];

            if (state.speed > 0)
            {
                if (state.mode == FadeMode::fadeAll)
                {
                    fadeToBlackBy(leds + i, 1, state.speed);
                }
                else if (state.mode == FadeMode::oneByOne)
                {
                    if (random8() < state.speed)
                    {
                        leds[i] = CRGB::Black;
                    }
                    else
                    {
                        fadeToBlackBy(leds + i, 1, 1);
                    }
                }
                else if (state.mode == FadeMode::sparkle)
                {
                    if (state.speed == 255)
                    {
                        _fades[i].speed = 0;
                        leds[i] = CRGB::Black;
                    }
                    else if (random8() < state.speed)
                    {
                        _fades[i].speed = 255;
                        leds[i] = CRGB::White;
                    }
                    else
                    {
                        fadeToBlackBy(leds + i, 1, 1);
                    }
                }
            }
        }
    }

    inline void scheduleFade(uint8_t begin, uint8_t length, uint8_t speed, FadeMode mode)
    {
        for (auto index = begin; index < begin + length; index++)
        {
            scheduleFade(index, speed, mode);
        }
    }

    inline void scheduleFade(uint8_t index, uint8_t speed, FadeMode mode)
    {
        if (leds[index] == CRGB::Black)
        {
            auto newState = FadeState(0, mode);
            _fades[index] = newState;
        }
        else
        {
            auto newState = FadeState(speed, mode);
            _fades[index] = newState;
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
            uint8_t size = _fades.size();
            for (uint8_t i = 0; i < size; i++)
            {
                scheduleFade(i, speed, mode);
            }
        }
    }

    void disableFade()
    {
        uint8_t size = _fades.size();
        for (uint8_t i = 0; i < size; i++)
        {
            scheduleFade(i, 0, FadeMode::none);
        }
    }
} Fader;

extern FaderHelper Fader;
