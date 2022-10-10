#pragma once

#include "core.h"

#define NUM_LEDS 24
CRGB leds[NUM_LEDS];

class SpectacleDevice : public OSC::MessageConsumer
{
private:
    OSC::StructMessage<SpectacleCommand, uint32_t> _message;

public:
    const char *const oscAddress;
    uint32_t progress = 0;

    SpectacleDevice(const char *oscAddress)
        : oscAddress(oscAddress)
    {
        _message.messageStruct.mode = 0;
    }

    void init()
    {
        FastLED.addLeds<WS2811, 4, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
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
        progress = 0;
        Serial.println("MESSAGE");
    }

    void loop(App::Time time)
    {
        if (time.tVISUAL)
        {
            progress += _message.messageStruct.speed;
            if (progress >= 256)
            {
                progress = 0;
            }
        }

        switch (_message.messageStruct.mode)
        {
        case 0:

            // set to off
            fill_solid(leds, NUM_LEDS, CRGB::Black);
            FastLED.show();

            break;

        case 1:
        {
            // RGBLoop - no parameters
            CHSV color = CHSV(progress, 0xff, 0xff);
            fill_solid(leds, NUM_LEDS, CRGB(color));
            FastLED.show();
        }
        break;

        case 2:
            fill_rainbow(leds, NUM_LEDS, progress, 21);
            FastLED.show();
            break;

        case 3:

            digitalWrite(13, progress < _message.messageStruct.speed);
            break;

        case 4:
        {
            CHSV color = CHSV(
                _message.messageStruct.hue1,
                _message.messageStruct.hue1 == 255 ? 0x00 : 0xff,
                0xff);
            fill_solid(leds, NUM_LEDS, CRGB(color));
            FastLED.show();
        }
        // set to magenta
        break;

        case 5:
        {
            
            fill_solid(leds, NUM_LEDS, CRGB(0xff, 0x00, 0xff));
            FastLED.show();
        }
        // set to magenta
        break;

        case 6:
        {
            
            fill_solid(leds, NUM_LEDS, CRGB(0xff, 0x00, 0x00));
            leds[2] = CRGB:: Blue;
            leds[3] = CRGB:: Blue;
            leds[4] = CRGB:: Blue;
            leds[5] = CRGB:: Blue;
            leds[6] = CRGB:: Blue;
            leds[7] = CRGB:: Blue;
            leds[12] = CRGB:: Blue;
            leds[13] = CRGB:: Blue;
            leds[14] = CRGB:: Blue;
            leds[15] = CRGB:: Blue;
            leds[16] = CRGB:: Blue;
            leds[17] = CRGB:: Blue;
            FastLED.show();
        }
        // set to red/blue cops
        break;
        }
    }
};
