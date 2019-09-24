#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include <OSCArduino.h>
#include <SimpleMessage.h>
#include <ColorFunction.h>

class GuitarMessageProducer : public OSC::MessageProducer<OSC::StructMessage<SimpleMessage, uint32_t>>
{
public:
    OSC::StructMessage<SimpleMessage, uint32_t> message;

    uint8_t pins[5] = {0, 4, 13, 12, 5};
    uint8_t state = 0;
    uint8_t previousState = 0;

    CRGB *leds;
    uint8_t nrOfLeds;

    bool firstRun = true;

    GuitarMessageProducer(const char *pattern, CRGB *leds, uint8_t nrOfLeds) : leds(leds), nrOfLeds(nrOfLeds)
    {
        message.setAddress(pattern);
    }

    virtual void loop()
    {
        // because pin 5 is uses as blinker, we cannot set it until here
        if (firstRun)
        {
            for (auto &pin : pins)
            {
                pinMode(pin, INPUT_PULLUP);
            }

            firstRun = false;
        }

        uint8_t i = 0;
        for (auto &pin : pins)
        {
            bool value = digitalRead(pin);

            if (!value)
            {
                state |= 1 << i;
            }
            else
            {
                state &= ~(1 << i);
            }

            i++;
        }
    };

    virtual OSC::StructMessage<SimpleMessage, uint32_t> *generateMessage()
    {
        blendColor(leds, nrOfLeds, state);

        message.setValidData(state != previousState && state != 0);

        message.messageStruct.id = state;

        previousState = state;

        return &message;
    };
};