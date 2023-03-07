#pragma once

#include "core.h"

template <uint8_t DATA_PIN>
struct Leds : public BaseLeds
{
public:
    Leds()
    {
        initLeds(59);
    }

    void init()
    {
        FastLED.addLeds<APA102, DATA_PIN, 32, BGR, DATA_RATE_KHZ(500)>(leds, nrOfLeds).setCorrection(TypicalLEDStrip);

        fill_solid(leds, nrOfLeds, CRGB::Black);
        fill_solid(leds, nrOfLeds, CRGB::Green);
        fade(0, nrOfLeds, 2, FadeMode::FadeToBlack);
    }

    void show()
    {
        FastLED.show();
    }
};
