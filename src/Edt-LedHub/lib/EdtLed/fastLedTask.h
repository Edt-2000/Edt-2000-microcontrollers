#include <FastLed.h>

struct FastLedTaskParameters {
    int numberOfLeds;
    int hueStart;
    int delay;
    FastLedTaskParameters(int numberOfLeds, int hueStart, int delay) 
        : numberOfLeds(numberOfLeds), hueStart(hueStart), delay(delay) {}
};

template<ESPIChipsets CHIPSET,  uint8_t DATA_PIN, uint8_t CLOCK_PIN >
void fastLedTask(void * parameters) {
    auto params = (FastLedTaskParameters*)parameters;

    CRGB leds[params->numberOfLeds];

    FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN>(leds, params->numberOfLeds);

    uint8_t hue = params->hueStart;

    while (true) {

        leds[0].setHSV(hue++, 255, 255);

        delay(params->delay);
    }
}

