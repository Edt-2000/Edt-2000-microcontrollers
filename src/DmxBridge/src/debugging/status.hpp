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
        fill_solid(leds, 59, CRGB::Black);
        fill_solid(leds, 1, color);
    }
} Status;

extern StatusHelper Status;
