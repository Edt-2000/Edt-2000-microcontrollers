#pragma once

#include <FastLED.h>

extern volatile bool doFastLed;

void fastLedTask(void *parameters)
{
    while (true) 
    {
        if (doFastLed) {
            FastLED.show();

            doFastLed = false;
        }
        delay(1);
    }
}
