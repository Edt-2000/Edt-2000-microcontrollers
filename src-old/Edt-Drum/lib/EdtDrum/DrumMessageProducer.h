#pragma once

#include <OSCArduino.h>
#include <SimpleMessage.h>

class DrumMessageProducer : public OSC::MessageProducer<OSC::StructMessage<SimpleMessage, uint32_t>>
{
public:
    OSC::StructMessage<SimpleMessage, uint32_t> message;

    uint8_t pins[5] = {A2, A1, A5, A4, A3};
    uint8_t state = 0;
    uint8_t previousState = 0;
    uint8_t cooldown[5] = {0, 0, 0, 0, 0};

    DrumMessageProducer(const char *pattern)
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
            auto value = analogRead(pin);

            if (value > 100 && cooldown[i] == 0)
            {
                state |= 1 << i;
                cooldown[i] = 255;
            }
            else
            {
                state &= ~(1 << i);
            }

            if (cooldown[i] > 0)
            {
                cooldown[i]--;
            }

            i++;
        }
    };

    virtual OSC::StructMessage<SimpleMessage, uint32_t> *generateMessage()
    {
        message.setValidData(state != previousState && state != 0);

        message.messageStruct.id = state;

        previousState = state;

        return &message;
    };
};