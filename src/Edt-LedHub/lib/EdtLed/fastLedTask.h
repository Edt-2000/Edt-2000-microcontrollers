#pragma once

#include "core.h"

template <ESPIChipsets CHIPSET, uint8_t DATA_PIN, uint8_t CLOCK_PIN, EOrder RGB_ORDER, uint8_t NUMBER_OF_LEDS>
void fastLedTask(void *parameters)
{
    auto queue = (QueueHandle_t)parameters;

    Messages::CommandMessage message;
    // CRGB leds[params->numberOfLeds];
    // FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, RGB_ORDER>(leds, params->numberOfLeds);

    Devices::EdtFastLed<CHIPSET, DATA_PIN, CLOCK_PIN, RGB_ORDER, NUMBER_OF_LEDS> device;

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
