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
        _isActive = true;
    }

    void stop()
    {
        _isActive = false;
    }

    void loop()
    {
        if (Time.t1ms)
        {
            Fader.disableFade();

            for (uint8_t i = 0; i < 24; i++)
            {
                if (globalSettings.speed / 2 > random8())
                {
                    auto s = random8(180, 255);

                    if (s > 220)
                    {
                        leds[i] = CRGB::White;
                    }
                    else
                    {
                        leds[i] = CHSV(158, s, 255);
                    }
                }
                else
                {
                    leds[i] = CRGB::Black;
                }
            }
        }
    }
};
