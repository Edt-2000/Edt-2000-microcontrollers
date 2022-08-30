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
            progress++;
            if (progress > 256)
            {
                progress = 0;
            }
        }

        switch (_message.messageStruct.mode)
        {
        case 0:

            // set to off
            setAll(0x00, 0x00, 0x00);


            break;

        case 1:

            // RGBLoop - no parameters
            RGBLoop();
            break;

        case 2:
            rainbowCycle(_message.messageStruct.speed);
            break;

        case 3:
            
            digitalWrite(13, progress < _message.messageStruct.speed);
            break;

            //}

            // if (time.t100ms)
            // {
            //     digitalWrite(13, progress > _message.messageStruct.mode);

            //     if (++progress > 2 * _message.messageStruct.mode)
            //     {
            //         progress = 0;
            //     }
            // }
        }
    }

    void RGBLoop()
    {
        setAll(progress, progress, progress);
        // for (int j = 0; j < 3; j++)
        //{
        //  Fade IN
        // for (int k = 0; k < 256; k++)
        //{
        // switch (j)
        //{
        // case 0:
        //      setAll(k, 0, 0);
        //      break;
        //  case 1:
        //      setAll(0, k, 0);
        //      break;
        //  case 2:
        //      setAll(0, 0, k);
        //      break;
        //  }
        //  showStrip();
        //  delay(3);
        //}
        //     // Fade OUT
        // //    for (int k = 255; k >= 0; k--)
        // //    {
        //         switch (j)
        //         {
        //         case 0:
        //             setAll(k, 0, 0);
        //             break;
        //         case 1:
        //             setAll(0, k, 0);
        //             break;
        //         case 2:
        //             setAll(0, 0, k);
        //             break;
        //         }
        //         showStrip();
        //         delay(3);
        //     }
        //}
    }
    void rainbowCycle(int SpeedDelay)
    {
                fill_rainbow(leds, NUM_LEDS, progress, 21);
                showStrip();
        // byte *c;

        //     for (int i = 0; i < NUM_LEDS; i++)
        //     {

        //         c = Wheel(((i * 256 / NUM_LEDS) + progress) & 255);
        //         setPixel(i, *c, *(c + 1), *(c + 2));
        //     }
        //     showStrip();
        
    }
    byte *Wheel(byte WheelPos)
    {
        static byte c[3];

        if (WheelPos < 85)
        {
            c[0] = WheelPos * 3;
            c[1] = 255 - WheelPos * 3;
            c[2] = 0;
        }
        else if (WheelPos < 170)
        {
            WheelPos -= 85;
            c[0] = 255 - WheelPos * 3;
            c[1] = 0;
            c[2] = WheelPos * 3;
        }
        else
        {
            WheelPos -= 170;
            c[0] = 0;
            c[1] = WheelPos * 3;
            c[2] = 255 - WheelPos * 3;
        }

        return c;
    }

    void setAll(byte red, byte green, byte blue)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            setPixel(i, red, green, blue);
        }
        showStrip();
    }
    void setPixel(int Pixel, byte red, byte green, byte blue)
    {
        // FastLED
        leds[Pixel].r = red;
        leds[Pixel].g = green;
        leds[Pixel].b = blue;
    }
    void showStrip()
    {
        FastLED.show();
    }
};
