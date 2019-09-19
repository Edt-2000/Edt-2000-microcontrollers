#pragma once

#include "core.h"

template <int redPin, int greenPin, int bluePin, uint8_t NUMBER_OF_LEDS>
void hardwiredRgbLedTask(void *parameters)
{
    auto queue = (QueueHandle_t)parameters;

    Messages::CommandMessage message;
    Devices::EdtRgbLed<NUMBER_OF_LEDS> device(new Drivers::HardwiredRgbLedDriver<redPin, greenPin, bluePin>());

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
