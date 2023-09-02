#pragma once

#include <FastLED.h>

extern volatile bool doFastLed;

void fastLedTask(void *parameters)
{
    while (true)
    {
        if (doFastLed)
        {
            FastLED.show();

            doFastLed = false;
        }
        delayMicroseconds(1);
    }
}
