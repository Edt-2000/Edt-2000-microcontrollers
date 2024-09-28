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
            applyToLeds(
                [](CRGB *leds, uint8_t index)
                {
                    // Step 1.  Cool down every cell a little
                    for (uint8_t i = 0; i < 59; i++)
                    {
                        scratchpad[index][i] = qsub8(scratchpad[index][i], random8(0, (((255 - globalSettings.speed) * 10) / 59) + 2));
                    }

                    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
                    for (uint8_t k = 58; k >= 2; k--)
                    {
                        scratchpad[index][k] = (scratchpad[index][k - 1] + scratchpad[index][k - 2] + scratchpad[index][k - 2]) / 3;
                    }

                    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
                    if (random8() < 120)
                    {
                        auto y = random8(7);
                        scratchpad[index][y] = qadd8(scratchpad[index][y], random8(160, 255));
                    }

                    // Step 4.  Map from heat cells to LED colors
                    for (uint8_t j = 0; j < 59; j++)
                    {
                        leds[58 - j] = HeatColor(scratchpad[index][j]);
                    }
                });

            show();

        } while (_isActive);
    }
};
