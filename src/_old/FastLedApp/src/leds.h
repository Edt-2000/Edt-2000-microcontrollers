#pragma once

#include "core.h"

template <uint8_t DATA_PIN, uint8_t INDEX>
struct Leds : public BaseLeds
{
private:
    uint8_t levels[7][9] = {
        {54, 55, 56, 57, 58, 59, 59, 59, 59},
        {45, 46, 47, 48, 49, 50, 51, 52, 53},
        {36, 37, 38, 39, 40, 41, 42, 43, 44},
        {27, 28, 29, 30, 31, 32, 33, 34, 35},
        {18, 19, 20, 21, 22, 23, 24, 25, 26},
        {9, 10, 11, 12, 13, 14, 15, 16, 17},
        {0, 1, 2, 3, 4, 5, 6, 7, 8}};

public:
    Leds()
    {
        initLeds(59, 9, INDEX);
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
        // FastLED.show();
    }

    uint8_t *level(uint8_t level)
    {
        switch (level)
        {
        case 0:
            return levels[0];
        case 1:
            return levels[1];
        case 2:
            return levels[2];
        case 3:
            return levels[3];
        case 4:
            return levels[4];
        case 5:
            return levels[5];
        case 6:
            return levels[6];
        default:
            return levels[6];
        }
    }

    uint8_t angleLeft(uint8_t angle)
    {
        return nrOfLeds - (angle / 4.4);
    }

    uint8_t angleRight(uint8_t angle)
    {
        return angleLeft(angle);
    }
};
