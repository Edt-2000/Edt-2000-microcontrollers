#pragma once

#include <OSCArduino.h>
#include <TrakMessage.h>

class TrakMessageProducer : public OSC::MessageProducer<OSC::StructMessage<TrakMessage, uint32_t>>
{
public:
    OSC::StructMessage<TrakMessage, uint32_t> message;

    uint8_t pins[6] = {A2, A1, A0, A5, A4, A3};

    TrakMessageProducer(const char *pattern)
    {
        message.setAddress(pattern);

        for (auto &pin : pins)
        {
            pinMode(pin, INPUT);
        }
    }

    virtual void loop()
    {
        uint8_t i = 0;
        for (auto &pin : pins)
        {
            auto value = 1024 - nalogRead(pin);

            if (value > 100)
            {
                message.messageStruct.data[i++] = value;
            }
            else
            {
                message.messageStruct.data[i++] = 0;
            }
        }
    };

    virtual OSC::StructMessage<TrakMessage, uint32_t> *generateMessage()
    {
        bool send = false;
        for (auto &out : message.messageStruct.data)
        {
            if (out > 0)
            {
                send = true;
            }
        }

        message.setValidData(send);

        return &message;
    };
};