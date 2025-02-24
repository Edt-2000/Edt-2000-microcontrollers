#pragma once

#include "core.h"
#include "animationContainer.h"
#include "animations/chaseAnimation.h"
#include "animations/fireAnimation.h"
#include "animations/stroboAnimation.h"
#include "animations/swipeAnimation.h"
#include "animations/theaterChaseAnimation.h"

class SpectacleDevice : public OSC::MessageConsumer
{
private:
    OSC::StructMessage<SpectacleCommand, uint32_t> _message;

public:
    const char *const oscAddress;

    AnimationContainer animations;

    SpectacleDevice(const char *oscAddress) : oscAddress(oscAddress)
    {
        _message.messageStruct.mode = (ColorCommands)-1;
    }
    
    void init();

    const char *address();

    OSC::IMessage *message();

    void callbackMessage();

    void loop(App::Time time);
};
