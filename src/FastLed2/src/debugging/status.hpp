#pragma once

#include "../fader.hpp"
#include "../settings.hpp"

#include "./leds.hpp"

class StatusHelper
{
public:
    void init() {
        setColor(CRGB::Maroon);
        Fader.disableFade();
    }

    void setup() {
        setColor(CRGB::Gold);
        Fader.disableFade();
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
    }
} Status;

extern StatusHelper Status;
