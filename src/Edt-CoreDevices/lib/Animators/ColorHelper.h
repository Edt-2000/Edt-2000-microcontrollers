#pragma once

#include <FastLED.h>

namespace Animators
{
    class ColorHelper
    {
    public:
        static CHSV CreateColor(uint8_t hue, uint8_t saturation = 255, uint8_t value = 255)
        {
            return (hue < 255)
                       ? CHSV(hue, saturation, value)
                       : CHSV(0, 0, value);
        }
    };
}
