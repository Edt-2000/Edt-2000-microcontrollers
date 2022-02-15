#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include <OSCArduino.h>
#include <SimpleMessage.h>
#include <ColorFunction.h>

class DrumMessageConsumer : public OSC::MessageConsumer<OSC::StructMessage<SimpleMessage, uint32_t>>
{
private:
    const char *_pattern;

public:
    CRGB *leds;
    uint8_t nrOfLeds;

    DrumMessageConsumer(const char *pattern, CRGB *leds, uint8_t nrOfLeds) : _pattern(pattern), leds(leds), nrOfLeds(nrOfLeds)
    {
    }

    virtual const char *pattern()
    {
        return _pattern;
    }

    virtual void callbackMessage(OSC::StructMessage<SimpleMessage, uint32_t> *message)
    {
        blendColor(leds, nrOfLeds, message->messageStruct.id);
    }
};