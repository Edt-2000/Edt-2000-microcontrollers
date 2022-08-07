#pragma once

#include "core.h"

class SpectacleDevice : public OSC::MessageConsumer
{
private:
    OSC::StructMessage<SpectacleCommand, uint32_t> _message;

public:
    const char *const oscAddress;
    uint32_t progress = 20;

    SpectacleDevice(const char *oscAddress)
        : oscAddress(oscAddress)
    {
        _message.messageStruct.mode = 0;
    }

    const char *address()
    {
        return oscAddress;
    }

    OSC::IMessage *message()
    {
        return &_message;
    }

    void callbackMessage()
    {
    }

    void loop()
    {
        progress++;

        digitalWrite(13, progress > 500);

        if (progress > 1000)
        {
            progress = 0;
        }
    }
};
