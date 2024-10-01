#pragma once

#include "../settings.hpp"
#include "../time.hpp"

extern Settings globalSettings;
extern CRGB *leds;

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

        Time.delay(1000);

        fill_solid(leds, 1, CRGB::Black);
    }
private:
    void setColor(CRGB color) {
        // reset all leds
        fill_solid(leds, LEDS, CRGB::Black);
        
        // set colors
        fill_solid(leds, 1, color);
        fadeToBlackBy(leds, 1, 220);
    }
} Status;

extern StatusHelper Status;
