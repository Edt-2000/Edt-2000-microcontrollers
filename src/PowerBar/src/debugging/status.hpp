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

        setColor(CRGB::Black);
    }
private:
    void setColor(CRGB color) {
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        fill_solid(leds, 1, color);
        FastLED.show();
    }
} Status;

extern StatusHelper Status;
