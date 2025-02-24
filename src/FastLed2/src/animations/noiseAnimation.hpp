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
            applyToLeds(
                [](CRGB *leds, uint8_t index)
                {
                    for (uint8_t i = 0; i < 59; i++) {
                        if (globalSettings.speed > random8()) {
                            auto s = random8(180, 255);

                            if (s > 220) {
                                leds[i] = CRGB::White;
                            }
                            else {
                                leds[i] = CHSV(158, s, 255);
                            }
                        }
                        else {
                            leds[i] = CRGB::Black;
                        }
                    }
                });

            show();

            delay(16);

        } while (_isActive);
    }
};
