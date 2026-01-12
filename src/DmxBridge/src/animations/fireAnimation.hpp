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
            for (uint8_t i = 0; i < 59; i++)
            {
                auto s = random8(0, 40);

                leds[i] = CHSV(s, 255, 255);
            }

            show();

            delay(100);

        } while (_isActive);
    }
};
