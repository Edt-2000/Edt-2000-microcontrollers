#pragma once

#include <FastLED.h>
#include <vector>

#include "./debugging/logger.hpp"

extern CRGB *led1;
extern CRGB *led2;

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
    std::vector<CRGB **> _leds;
    std::vector<std::vector<FadeState>> _fades;

public:
    FaderHelper()
    {
        _leds.resize(2);
        _leds[0] = &led1;
        _leds[1] = &led2;
        _fades.resize(2, std::vector<FadeState>(1));
    }

    void loop()
    {
        uint8_t led = 0;
        for (auto &states : _fades)
        {
            uint8_t i = 0;
            for (auto &state : states)
            {
                if (state.speed > 0)
                {
                    if (state.mode == FadeMode::fadeAll)
                    {
                        fadeToBlackBy(*_leds[led] + i, 1, state.speed);
                    }
                    else if (state.mode == FadeMode::oneByOne)
                    {
                        if (random8() < state.speed)
                        {
                            *_leds[led][i] = CRGB::Black;
                        }
                        else
                        {
                            fadeToBlackBy(*_leds[led] + i, 1, 1);
                        }
                    }
                    else if (state.mode == FadeMode::sparkle)
                    {
                        if (state.speed == 255)
                        {
                            _fades[led][i].speed = 0;
                            *_leds[led][i] = CRGB::Black;
                        }
                        else if (random8() < state.speed)
                        {
                            _fades[led][i].speed = 255;
                            *_leds[led][i] = CRGB::White;
                        }
                        else
                        {
                            fadeToBlackBy(*_leds[led] + i, 1, 1);
                        }
                    }
                }

                ++i;
            }

            ++led;
        }

        FastLED.show();
    }

    void scheduleFade(uint8_t led, uint8_t index, uint8_t speed, FadeMode mode)
    {
        auto newState = FadeState(speed, mode);
        _fades[led][index] = newState;
    }

    void scheduleFade(uint8_t led, uint8_t speed, FadeMode mode)
    {
        for (uint8_t i = 0; i < _fades[led].size(); i++)
        {
            auto newState = FadeState(speed, mode);
            _fades[led][i] = newState;
        }
    }

    void disableFade(uint8_t led)
    {
        for (uint8_t i = 0; i < _fades[led].size(); i++)
        {
            auto newState = FadeState(0, FadeMode::oneByOne);
            _fades[led][i] = newState;
        }
    }
} Fader;

extern FaderHelper Fader;
