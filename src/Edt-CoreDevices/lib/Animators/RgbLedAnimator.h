#pragma once

#include <FastLED.h>

#include <Animation.h>
#include <Animations.h>
#include <AnimationType.h>
#include <FadeMode.h>
#include <LedState.h>
#include <RgbLedDriver.h>

using namespace Animations;

namespace Animators
{
class RgbLedAnimator
{
private:
    CRGB *_leds;
    LedState _ledState;

    Drivers::RgbLedDriver *_driver;

    void _output();

    Animations::Animations _animations;

public:
    uint8_t nrOfLeds;

    RgbLedAnimator() {}
    RgbLedAnimator(CRGB *leds, uint8_t nrOfLeds, Drivers::RgbLedDriver *driver)
    {
        _leds = leds;
        this->nrOfLeds = nrOfLeds;

        fill_solid(_leds, nrOfLeds, CRGB::HTMLColorCode::Black);

        _ledState.fade = 255;

        _driver = driver;
    }

    void solid(uint8_t h, uint8_t s, uint8_t v);
    void solid(CHSV color);
    void solid(uint8_t h1, uint8_t h2, uint8_t s, uint8_t v, uint8_t percentage);
    void fade(uint8_t duration, Animations::FadeMode mode = Animations::FadeMode::FadeToBlack);
    void disableFade();
    void rainbow(uint8_t h, uint8_t dh);
    void intensity(uint8_t intensity);
    void strobo(uint8_t h, uint8_t intensity);

    void loop();
};
} // namespace Animators