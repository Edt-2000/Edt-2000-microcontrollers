#pragma once

#include "core.h"

// this is not reusable
struct Leds : public BaseLeds
{
private:
    CRGB realLeds[24];

    uint8_t levels[7][4] = {
        {9, 9, 21, 21},
        {10, 8, 22, 20},
        {11, 7, 23, 19},
        {0, 6, 12, 18},
        {1, 5, 13, 17},
        {2, 4, 14, 16},
        {3, 3, 15, 15}};

public:
    Leds()
    {
        initLeds(24);
    }

    void init()
    {
        FastLED.addLeds<WS2811, 4, GRB>(realLeds, nrOfLeds).setCorrection(TypicalLEDStrip);
        fill_solid(leds, 24, CRGB::Black);
        fill_solid(leds, 1, CRGB::Green);
        ledState[0].fade = 2;
    }

    void show()
    {
        realLeds[10] = leds[0];
        realLeds[11] = leds[1];
        realLeds[0] = leds[2];
        realLeds[1] = leds[3];
        realLeds[2] = leds[4];
        realLeds[3] = leds[5];
        realLeds[4] = leds[6];
        realLeds[5] = leds[7];
        realLeds[6] = leds[8];
        realLeds[7] = leds[9];
        realLeds[8] = leds[10];
        realLeds[9] = leds[11];

        realLeds[14] = leds[12];
        realLeds[13] = leds[13];
        realLeds[12] = leds[14];
        realLeds[23] = leds[15];
        realLeds[22] = leds[16];
        realLeds[21] = leds[17];
        realLeds[20] = leds[18];
        realLeds[19] = leds[19];
        realLeds[18] = leds[20];
        realLeds[17] = leds[21];
        realLeds[16] = leds[22];
        realLeds[15] = leds[23];

        FastLED.show();
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
};
