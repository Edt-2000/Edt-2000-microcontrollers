#pragma once

#include <FastLED.h>

struct LedState
{
public:
    uint8_t fade;
};

enum FadeMode
{
    FadeToBlack = 0,
    FadeOneByOne = 1
};

struct BaseLeds
{
protected:
    void initLeds(uint8_t numberOfLeds)
    {
        nrOfLeds = numberOfLeds;
        leds = new CRGB[numberOfLeds];
        ledState = new LedState[numberOfLeds];
    }

    virtual void show();

public:
    uint8_t nrOfLeds;
    CRGB *leds;
    LedState *ledState;
    FadeMode activeFadeMode;

    virtual void init();

    uint8_t normalizeLedNrDown(uint8_t percentage)
    {
        return floorf((percentage / 127.0) * nrOfLeds);
    }

    uint8_t normalizeLedNrUp(uint8_t percentage)
    {
        return ceilf((percentage / 127.0) * nrOfLeds);
    }

    void randomize(uint8_t start, uint8_t end, uint8_t percentage, CRGB color1, CRGB color2)
    {
        for (int i = start; i < end; i++)
        {
            if (percentage > random8())
            {
                leds[i] = color1;
            }
            else
            {
                leds[i] = color2;
            }
        }
    }

    void fade(uint8_t start, uint8_t end, uint8_t speed, FadeMode fadeMode)
    {
        activeFadeMode = fadeMode;

        for (int i = start; i < end; i++)
        {
            ledState[i].fade = speed;
        }
    }

    void fade(uint8_t led, uint8_t speed, FadeMode fadeMode)
    {
        activeFadeMode = fadeMode;

        ledState[led].fade = speed;
    }

    void disableFade(uint8_t start, uint8_t end)
    {
        for (int i = start; i < end; i++)
        {
            ledState[i].fade = 255;
        }
    }

    void disableFade()
    {
        disableFade(0, nrOfLeds);
    }

    void loop()
    {
        fadeLoop();
        show();
    }

    void fadeLoop()
    {
        switch (activeFadeMode)
        {
        case FadeMode::FadeToBlack:
            for (int i = 0; i < nrOfLeds; i++)
            {
                if (ledState[i].fade < 255)
                {
                    if (ledState[i].fade > 255 - 5)
                    {
                        ledState[i].fade = 255;
                    }
                    else
                    {
                        ledState[i].fade += 1;
                    }

                    fadeToBlackBy(leds + i, 1, ledState[i].fade);
                }
            }
            break;
        case FadeMode::FadeOneByOne:
            for (int i = 0; i < nrOfLeds; i++)
            {
                if (ledState[i].fade < 255)
                {
                    if (ledState[i].fade / 8 > random8())
                    {
                        ledState[i].fade = 255;

                        fadeToBlackBy(leds + i, 1, 255);
                    }
                    else
                    {
                        fadeToBlackBy(leds + i, 1, 2);
                    }
                }
            }
            break;
        }
    }
};