#pragma once

#include "core.h"

template <int address, uint8_t NUMBER_OF_LEDS>
void pca9685RgbLedTask(void *parameters)
{
    auto queue = (QueueHandle_t)parameters;

    Messages::CommandMessage message;
    Devices::EdtRgbLed<NUMBER_OF_LEDS> device(new Drivers::Pca9685RgbLedDriver<address>());

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
