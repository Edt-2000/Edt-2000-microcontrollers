#pragma once

#include "core.h"

class SmokeDevice : public OSC::MessageConsumer
{
private:
    OSC::StructMessage<SmokeCommand, uint32_t> _message;

public:
    const char *const oscAddress;
    uint32_t progress = 20;

    SmokeDevice(const char *oscAddress)
        : oscAddress(oscAddress)
    {
        _message.messageStruct.dutyCycle = 120;
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

        if (progress > _message.messageStruct.dutyCycle) {
            progress = 0;
        }

        auto output = progress < 10 ? HIGH : LOW;

        digitalWrite(5, output);
        digitalWrite(0, output);
    }
};
