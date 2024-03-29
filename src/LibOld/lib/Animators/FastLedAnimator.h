#pragma once

#include <FastLED.h>

#include <Animation.h>
#include <Animations.h>
#include <AnimationType.h>
#include <FadeMode.h>
#include <LedState.h>

using namespace Animations;

namespace Animators
{
class FastLedAnimator
{
private:
    CRGB *_leds;
    LedState *_ledState;
    FadeMode _fadeMode;

    uint8_t _start;
    uint8_t _center;
    uint8_t _end;

    uint8_t normalizeLedNrDown(uint8_t percentage)
    {
        return floorf((percentage / 127.0) * nrOfLeds);
    }
    uint8_t normalizeLedNrUp(uint8_t percentage)
    {
        return ceilf((percentage / 127.0) * nrOfLeds);
    }

    Animations::Animations _animations;

public:
    uint8_t nrOfLeds;

    FastLedAnimator() {}
    FastLedAnimator(CRGB *leds, uint8_t nrOfLeds)
    {
        _leds = leds;
        _ledState = new LedState[nrOfLeds];
        this->nrOfLeds = nrOfLeds;

        for (int i = 0; i < nrOfLeds; i++)
        {
            _ledState[i].fade = 255;
        }
    }

    void solid(uint8_t start, uint8_t end, uint8_t h, uint8_t s, uint8_t v);
    void solid(uint8_t start, uint8_t end, CHSV color);
    void fade(uint8_t start, uint8_t end, uint8_t duration, FadeMode mode = FadeMode::FadeToBlack);
    void disableFade(uint8_t start, uint8_t end);
    void rainbow(uint8_t start, uint8_t end, uint8_t h, uint8_t dh);
    void rainbow(uint8_t start, uint8_t center, uint8_t end, uint8_t h, uint8_t dh, uint8_t intensity);
    void twinkle(uint8_t start, uint8_t end, uint8_t h, uint8_t s, uint8_t v, uint8_t intensity, bool blackOut = true);
    void strobo(uint8_t h, uint8_t intensity);
    void chase(uint8_t h, uint8_t speed, uint8_t fadeSpeed, bool direction);
    void chase(uint8_t h, uint8_t length);
    void bash(uint8_t h, uint8_t intensity);
    void berserk();

    void loop();
};
} // namespace Animators
