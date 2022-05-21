#pragma once

#include <Arduino.h>
#include <OSCArduino.h>
#include <CommandMessage.h>
#include <IMessage.h>
#include <OSCStructMessage.h>

struct SmokeCommand
{
    uint32_t dutyCycle;
};

class SmokeDevice : public OSC::MessageConsumer
{
private:
    OSC::StructMessage<SmokeCommand, uint32_t> _message;

public:
    const char *const oscAddress;

    SmokeDevice(const char *oscAddress)
        : oscAddress(oscAddress)
    {
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
        if (_message.messageStruct.dutyCycle > 0)
        {
            digitalWrite(5, HIGH);
        }
        else
        {
            digitalWrite(5, LOW);
        }
    }
};
