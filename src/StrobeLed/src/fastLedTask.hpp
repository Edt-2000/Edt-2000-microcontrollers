#pragma once

#include <FastLED.h>

extern volatile bool doFastLed;
extern volatile bool fastLedSuspended;

void fastLedTask(void *parameters)
{
    // TODO: make sure this help -- probably not since we invoke it so frequently
    FastLED.setMaxRefreshRate(0, false);

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
