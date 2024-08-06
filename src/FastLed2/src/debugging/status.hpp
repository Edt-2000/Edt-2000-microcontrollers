#pragma once

#include "../fader.hpp"
#include "../settings.hpp"

extern Settings globalSettings;
extern CRGB *led1;
extern CRGB *led2;

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

        Fader.scheduleFade(0, 16, FadeMode::oneByOne);
        Fader.scheduleFade(1, 16, FadeMode::oneByOne);
    }
private:
    void setColor(CRGB color) {
        // reset all leds
        fill_solid(led1, 1, CRGB::Black);
        fill_solid(led2, 1, CRGB::Black);
        
        // set colors
        fill_solid(led1, 1, color);
        fadeToBlackBy(led1, 1, 220);
        fill_solid(led2, 1, color);
        fadeToBlackBy(led2, 1, 220);
        
        FastLED.show();
    }
} Status;

extern StatusHelper Status;
