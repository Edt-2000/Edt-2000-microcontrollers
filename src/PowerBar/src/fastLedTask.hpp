#pragma once

#include <FastLED.h>

extern volatile bool doFastLed;
extern volatile bool fastLedSuspended;

void fastLedTask(void *parameters)
{
    while (true)
    {
        if (doFastLed)
        {
            FastLED.show();
        }
        else
        {
            fastLedSuspended = true;
        }
        vTaskDelay(1);
    }
}
