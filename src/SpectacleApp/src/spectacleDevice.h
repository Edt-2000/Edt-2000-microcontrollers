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
        Serial.println("MESSAGE");
    }

    void loop(App::Time time)
    {
        if (time.t100ms) 
        {
            digitalWrite(13, progress > _message.messageStruct.mode);

            if (++progress > 2 * _message.messageStruct.mode)
            {
                progress = 0;
            }
        }
    }
};
