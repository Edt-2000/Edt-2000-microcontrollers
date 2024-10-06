#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

class FireAnimation : public Animation
{
private:
    uint8_t scratchpad[24];
    uint8_t levels[24] =
        {7, 17,
         8, 6, 16, 18,
         9, 5, 15, 19,
         10, 4, 14, 20,
         11, 3, 13, 21,
         0, 2, 12, 22,
         1, 23};

public:
    FireAnimation()
    {
    }

    const char *name()
    {
        return "fire";
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
        if (Time.t20ms)
        {

            // Step 1.  Cool down every cell a little
            for (uint8_t i = 0; i < 24; i++)
            {
                scratchpad[i] = qsub8(scratchpad[i], random8(0, (((255 - globalSettings.speed) * 10) / 24) + 2));
            }

            // Step 2.  Heat from each cell drifts 'up' and diffuses a little
            for (uint8_t k = 23; k >= 2; k--)
            {
                scratchpad[k] = (scratchpad[k - 1] + scratchpad[k - 2] + scratchpad[k - 2]) / 3;
            }

            // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
            if (random8() < 120)
            {
                auto y = random8(3);
                scratchpad[y] = qadd8(scratchpad[y], random8(160, 255));
            }

            // Step 4.  Map from heat cells to LED colors
            for (uint8_t j = 0; j < 24; j++)
            {
                leds[levels[j]] = HeatColor(scratchpad[j]);
            }
        }
    }
};
