#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

class FireAnimation : public Animation
{
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
        takeFastLedControl();
        _isActive = true;
    }

    void stop()
    {
        yieldFastLedControl();
        _isActive = false;
    }

    void loop()
    {
        do
        {
            // adapted from http://fastled.io/docs/_fire2012_8ino-example.html
            // Step 1.  Cool down every cell a little
            for (uint8_t i = 0; i < 64; i++)
            {
                scratchpad[i] = qsub8(scratchpad[i], random8(0, (((255 - globalSettings.speed) * 10) / 64) + 2));
            }

            // Step 2.  Heat from each cell drifts 'up' and diffuses a little
            for (uint8_t k = 63; k >= 2; k--)
            {
                scratchpad[k] = (scratchpad[k - 1] + scratchpad[k - 2] + scratchpad[k - 2]) / 3;
            }

            // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
            if (random8() < 120)
            {
                auto y = random8(7);
                scratchpad[y] = qadd8(scratchpad[y], random8(160, 255));
            }

            // Step 4.  Map from heat cells to LED colors
            for (uint8_t j = 0; j < 64; j++)
            {
                leds0[63 - j] = HeatColor(scratchpad[j]);
            }

            show();

            delay(16);

        } while (_isActive);
    }
};
