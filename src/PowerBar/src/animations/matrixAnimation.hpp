#pragma once

#include "../animation.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"

#define MAX_STATE 64

class MatrixAnimation : public Animation
{
private:
    uint8_t rows[MAX_WIDTH];

public:
    MatrixAnimation()
    {
        for (uint8_t i = 0; i < MAX_WIDTH; i++)
        {
            rows[i] = random8(MAX_STATE);
        }
    }

    const char *name()
    {
        return "matrix";
    }

    bool mustRunSolo()
    {
        return true;
    }

    void start()
    {
        _isActive = true;
    }

    void stop()
    {
        _isActive = false;
    }

    void loop()
    {
        for (uint8_t x = 0; x < MAX_WIDTH; x++)
        {
            uint8_t state = rows[x] + 1;

            if (state < 8)
            {
                for (uint8_t y = state; y < 8; y--)
                {
                    uint16_t ledIndex = x * 8 + (7 - y);

                    if (y == state)
                    {
                        leds[ledIndex] = globalSettings.colorAt(0);
                    }
                    else
                    {
                        leds[ledIndex] = globalSettings.colorAt(1);
                    }
                }
            }
            
            if (state == 8) {
                uint16_t ledIndex = x * 8;
                leds[ledIndex] = globalSettings.colorAt(1);
            }

            for (uint8_t y = 0; y < 8; y++)
            {
                uint16_t ledIndex = x * 8 + y;

                if (y != state)
                {
                    fadeToBlackBy(leds + ledIndex, 1, 60);
                }
            }

            if (state > MAX_STATE) {
                state = 255;
            }

            rows[x] = state;
        }

        show();

        delay(100 / globalSettings.speed);
    }
};
