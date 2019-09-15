#pragma once

#include <Arduino.h>
#include <FastLed.h>
#include <commandMessage.h>

struct FastLedTaskParameters
{
    int numberOfLeds;
    QueueHandle_t queue;
    FastLedTaskParameters(int numberOfLeds, QueueHandle_t queue)
        : numberOfLeds(numberOfLeds), queue(queue) {}
};

template <ESPIChipsets CHIPSET, uint8_t DATA_PIN, uint8_t CLOCK_PIN, EOrder RGB_ORDER>
void fastLedTask(void *parameters)
{
    auto params = (FastLedTaskParameters *)parameters;

    OSC::CommandMessage message;
    CRGB leds[params->numberOfLeds];
    FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, RGB_ORDER>(leds, params->numberOfLeds);

    while (true)
    {
        if (xQueueReceive(params->queue, &message, 20 * portTICK_PERIOD_MS))
        {
            leds[0] = CHSV(message.commands.twinkle.hue, 255, message.commands.twinkle.intensity);
        }
        else
        {
            fadeToBlackBy(leds, 1, 10);
        }
    }
}
