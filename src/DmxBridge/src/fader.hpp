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
    sparkle,
    pulse,
    pulse2 = 250,
    pulse3 = 251,
    pulse4 = 252,
    pulse5 = 253
};

struct FadeState
{
    FadeState() : speed(0), mode(FadeMode::oneByOne) {};
    FadeState(uint8_t speed, FadeMode mode) : speed(speed), mode(mode) {};

    uint8_t speed;
    FadeMode mode;
    CRGB color;
};

class FaderHelper
{
private:
    std::vector<FadeState> _fades;

public:
    FaderHelper()
    {
        _fades.resize(59);
    }

    void loop()
    {
        uint8_t i = 0;
        
        for (auto & state : _fades)
        {
            if (state.speed > 0)
            {
                if (state.mode == FadeMode::fadeAll || state.mode == FadeMode::pulse5)
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
                        state.speed = 0;
                        leds[i] = CRGB::Black;
                    }
                    else if (random8() < state.speed)
                    {
                        state.speed = 255;
                        leds[i] = CRGB::White;
                    }
                    else
                    {
                        fadeToBlackBy(leds + i, 1, 1);
                    }
                }
                else if (state.mode == FadeMode::pulse)
                {
                    state.color = leds[i];
                    leds[i] = CRGB::Black;
                    state.mode = FadeMode::pulse2;
                }
                else if (state.mode == FadeMode::pulse2)
                {
                    leds[i] = state.color;
                    state.mode = FadeMode::pulse3;
                }
                else if (state.mode == FadeMode::pulse3)
                {
                    leds[i] = CRGB::Black;
                    state.mode = FadeMode::pulse4;
                }
                else if (state.mode == FadeMode::pulse4)
                {
                    leds[i] = state.color;
                    state.mode = FadeMode::pulse5;
                }
            }

            i++;
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

        uint8_t size = _fades.size();
        for (uint8_t i = 0; i < size; i++)
        {
            scheduleFade(i, speed, mode);
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
