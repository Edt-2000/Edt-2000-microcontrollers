#pragma once

#include "core.h"
#include "fastLedCommand.h"
#include "fastLedDevice.h"

template <uint8_t DATA_PIN>
void fastLedTask(void *parameters)
{
    auto queue = (QueueHandle_t)parameters;

    FastLedCommand message;
    FastLedDevice<DATA_PIN> device;

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
