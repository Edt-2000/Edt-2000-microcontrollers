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
        uint8_t led = 0;
        
        for (auto & states : _fades)
        {
            uint8_t i = 0;
            
            for (auto & state : states)
            {
                if (state.speed > 0)
                {
                    if (state.mode == FadeMode::fadeAll || state.mode == FadeMode::pulse5)
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
                            state.speed = 0;
                            //_fades[led][i].speed = 0;
                            _leds[led][i] = CRGB::Black;
                        }
                        else if (random8() < state.speed)
                        {
                            state.speed = 255;
                            //_fades[led][i].speed = 255;
                            _leds[led][i] = CRGB::White;
                        }
                        else
                        {
                            fadeToBlackBy(_leds[led] + i, 1, 1);
                        }
                    }
                    else if (state.mode == FadeMode::pulse)
                    {
                        state.color = _leds[led][i];
                        //_fades[led][i].color = _leds[led][i];
                        _leds[led][i] = CRGB::Black;
                        state.mode = FadeMode::pulse2;
                        //_fades[led][i].mode = FadeMode::pulse2;
                    }
                    else if (state.mode == FadeMode::pulse2)
                    {
                        _leds[led][i] = state.color;
                        state.mode = FadeMode::pulse3;
                        //_fades[led][i].mode = FadeMode::pulse3;
                    }
                    else if (state.mode == FadeMode::pulse3)
                    {
                        _leds[led][i] = CRGB::Black;
                        state.mode = FadeMode::pulse4;
                        //_fades[led][i].mode = FadeMode::pulse4;
                    }
                    else if (state.mode == FadeMode::pulse4)
                    {
                        _leds[led][i] = state.color;
                        state.mode = FadeMode::pulse5;
                        //_fades[led][i].mode = FadeMode::pulse5;
                    }
                }

                i++;
            }

            led++;
        }
    }

    inline void scheduleFade(uint8_t led, uint8_t begin, uint8_t length, uint8_t speed, FadeMode mode)
    {
        for (auto index = begin; index < begin + length; index++)
        {
            scheduleFade(led, index, speed, mode);
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
