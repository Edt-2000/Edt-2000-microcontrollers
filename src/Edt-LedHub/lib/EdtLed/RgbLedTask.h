#pragma once

#include "core.h"

template <uint8_t NUMBER_OF_LEDS>
void rgbLedTask(void *parameters)
{
    auto queue = (QueueHandle_t)parameters;

    Messages::CommandMessage message;
    Devices::EdtRgbLed<NUMBER_OF_LEDS> device(new Drivers::HardwiredRgbLedDriver<3, 32, 0>());

    device.init();

    while (true)
    {
        if (xQueueReceive(queue, &message, 20 * portTICK_PERIOD_MS))
        {
            device.handleMessage(message);
        }
        else
        {
            device.animate();
        }
    }
}
