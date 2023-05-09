#pragma once

#include "fastLedCommand.h"
#include "fastLedDevice.h"

template <uint8_t DATA_PIN, bool PRIMARY, uint8_t INDEX>
void fastLedTask(void *parameters)
{
    auto queue = (QueueHandle_t)parameters;

    FastLedCommand message;
    FastLedDevice<DATA_PIN, PRIMARY, INDEX> device;

    device.init();

    while (true)
    {
        if (xQueueReceive(queue, &message, 12 * portTICK_PERIOD_MS))
        {
            device.handleMessage(message);
        }
        else
        {
            device.animate();
        }
    }
}
