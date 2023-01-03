#pragma once

#include "core.h"
#include "animationContainer.h"

struct LedState
{
public:
    uint8_t fade;
};

enum FadeMode
{
    FadeToBlack = 0,
    FadeOneByOne = 1
};

class SpectacleDevice : public OSC::MessageConsumer
{
private:
    OSC::StructMessage<SpectacleCommand, uint32_t> _message;

public:
    const char *const oscAddress;

    const uint8_t nrOfLeds = 24;
    CRGB leds[24];
    LedState ledState[24];

    FadeMode activeFadeMode;
    AnimationContainer animations;

    SpectacleDevice(const char *oscAddress)
        : oscAddress(oscAddress)
    {
        _message.messageStruct.mode = (ColorCommands)-1;
    }

    void init();

    const char *address();

    OSC::IMessage *message();

    void callbackMessage();

    void loop(App::Time time);

    uint8_t normalizeLedNrDown(uint8_t percentage);

    uint8_t normalizeLedNrUp(uint8_t percentage);

    void fade(uint8_t start, uint8_t end, uint8_t speed, FadeMode fadeMode);

    void disableFade(uint8_t start, uint8_t end);

    void randomize(uint8_t start, uint8_t end, uint8_t percentage, CRGB color1, CRGB color2);

    void fadeLoop();
};
