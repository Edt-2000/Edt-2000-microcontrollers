#pragma once

#include "core.h"
#include "animationContainer.h"
#include "animations/stroboAnimation.h"

template <uint8_t DATA_PIN>
class FastLedDevice
{
private:
    OSC::StructMessage<FastLedCommand, uint32_t> _message;

public:
    Leds<DATA_PIN> fastLedLeds;

    AnimationContainer animations;

    FastLedDevice()
    {
        _message.messageStruct.mode = (ColorCommands)-1;
    }
    
    void init();

    void handleMessage(FastLedCommand message);

    void animate();
};
