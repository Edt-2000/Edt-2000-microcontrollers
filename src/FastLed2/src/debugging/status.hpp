#pragma once

#include "../fader.hpp"
#include "../settings.hpp"

#include "./leds.hpp"

class StatusHelper
{
public:
    void init() {
        setColor(CRGB::Maroon);
    }

    void setup() {
        setColor(CRGB::Gold);
    }

    void allOk()
    {
        setColor(CRGB::Lime);

        Fader.scheduleFade(16, FadeMode::fadeAll);
    }
private:
    void setColor(CRGB color) {
        // reset all leds
        applyToLeds([](CRGB* led) { fill_solid(led, 59, CRGB::Black); });
        applyToLeds([color](CRGB* led) { fill_solid(led, 1, color); });
        
        FastLED.show();
    }
} Status;

extern StatusHelper Status;