#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

class NoiseAnimation : public Animation
{
public:
    NoiseAnimation()
    {
    }

    const char *name()
    {
        return "noise";
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
            for (uint8_t i = 0; i < 64; i++)
            {
                if (globalSettings.speed > random8())
                {
                    auto s = random8(180, 255);

                    if (s > 220)
                    {
                        leds0[i] = CRGB::White;
                    }
                    else
                    {
                        leds0[i] = CHSV(158, s, 255);
                    }
                }
                else
                {
                    leds0[i] = CRGB::Black;
                }
            }

            show();

            delay(16);

        } while (_isActive);
    }
};
