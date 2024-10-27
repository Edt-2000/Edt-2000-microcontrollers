#pragma once

#include "../animation.hpp"
#include "../settings.hpp"
#include <FastLED.h>

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
        _isActive = true;
    }

    void stop()
    {
        _isActive = false;
    }

    void loop()
    {
        do
        {
            for (uint16_t i = 0; i < NUM_LEDS; i++)
            {
                if (globalSettings.speed > random8())
                {
                    auto s = random8();

                    if (s > 220)
                    {
                        leds[i] = globalSettings.colorAt(0);
                    }
                    else if (s > 180)
                    {
                        leds[i] = globalSettings.colorAt(1);
                    }
                    else if (s > 150)
                    {
                        leds[i] = globalSettings.colorAt(2);
                    }
                }
                else
                {
                    leds[i] = CRGB::Black;
                }
            }

            show();

            delay(16);

        } while (_isActive);
    }
};
