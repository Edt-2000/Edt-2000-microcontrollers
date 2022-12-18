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
    bool processed = false;

    SpectacleDevice(const char *oscAddress)
        : oscAddress(oscAddress)
    {
        _message.messageStruct.mode = (ColorCommands)-1;
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
        processed = false;
        Serial.println("MESSAGE");
    }

    void loop(App::Time time)
    {
        if (processed)
        {
            return;
        }

        if (time.tVISUAL)
        {
            progress += 1; //_message.messageStruct.speed;
            if (progress >= 256)
            {
                progress = 0;
            }
        }

        switch (_message.messageStruct.mode)
        {
        case ColorCommands::SingleSolid:
        {
            processed = true;

            auto start = normalizeLedNrDown(_message.messageStruct.commands.singleColor.start);
            auto end = normalizeLedNrUp(_message.messageStruct.commands.singleColor.end);

            fill_solid(leds + start, end - start, _message.messageStruct.commands.singleColor.getColor());
            FastLED.show();
        }
        break;
        case ColorCommands::Twinkle:
        {
            processed = _message.messageStruct.commands.twinkle.intensity > 10;

            auto start = normalizeLedNrDown(_message.messageStruct.commands.twinkle.start);
            auto end = normalizeLedNrUp(_message.messageStruct.commands.twinkle.end);
            auto color = _message.messageStruct.commands.twinkle.getColor();
            for (int i = start; i < end; i++)
            {
                if (_message.messageStruct.commands.twinkle.intensity > random8())
                {
                    leds[i] = color;
                }
                else
                {
                    leds[i] = CRGB::Black;
                }
            }
            FastLED.show();
        }
        break;
        case ColorCommands::DualSolid:
        case (ColorCommands)11:
        {
            processed = true;

            auto start = normalizeLedNrDown(_message.messageStruct.commands.twinkle.start);
            auto end = normalizeLedNrUp(_message.messageStruct.commands.twinkle.end);

            auto color1 = _message.messageStruct.commands.dualColor.getColor1();
            auto color2 = _message.messageStruct.commands.dualColor.getColor2();

            for (int i = start; i < end; i++)
            {
                if (_message.messageStruct.commands.dualColor.percentage > random8())
                {
                    leds[i] = color1;
                }
                else
                {
                    leds[i] = color2;
                }
            }
            FastLED.show();
        }
        break;
        case ColorCommands::TheathreChase:
        {
            if (time.t100ms)
            {
                _message.messageStruct.commands.theatre.progress++;
                int offset = _message.messageStruct.commands.theatre.progress % 2;

                fill_solid(leds, NUM_LEDS, CRGB::Black);

                for (int i = offset; i < 12; i = i + 2)
                {
                    fill_solid(leds + i, 1, (CRGB)CHSV(_message.messageStruct.commands.theatre.hue1, 255, 255));
                }
                for (int i = offset + 12; i < 24; i = i + 2)
                {
                    fill_solid(leds + i, 1, (CRGB)CHSV(_message.messageStruct.commands.theatre.hue2, 255, 255));
                }

                FastLED.show();
            }
        }
        break;
        case ColorCommands::FillSolid:
        {
            if (time.t100ms)
            {
                        }
        }
        break;
        case ColorCommands::Fire:
        {
            // bottom
            fill_solid(leds + 5, 5, CRGB::Red);
            fill_solid(leds + 15, 5, CRGB::Red);

            // 0, 1, 2, 3, 4, 10, 11,
            // 12, 13, 14, 20, 21, 22, 23

            int fireLeds[][7] = {
                {1, 0, 3, 11, 2, 10, 4},
                {22, 23, 13, 21, 12, 20, 14}};
            CRGB colors[] = {
                CRGB::Black,
                (CRGB)0xFF8500,
                CRGB::Orange,
                CRGB::OrangeRed,
                CRGB::Orange,
                (CRGB)0xFF8500,
                CRGB::OrangeRed,
            };

            if (time.t100ms)
            {
                _message.messageStruct.commands.fire.progress = (_message.messageStruct.commands.fire.progress + 1) % 7;

                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 7; j++)
                    {
                        int c = (_message.messageStruct.commands.fire.progress + j + i) % 7;

                        fill_solid(leds + fireLeds[i][j], 1, colors[c]);

                        fadeToBlackBy(leds + fireLeds[i][j], 1, sin8(progress));
                    }
                }
            }

            FastLED.show();
        }
        break;
        default:
            // set to off
            fill_solid(leds, NUM_LEDS, CRGB::Black);
            FastLED.show();
            break;
        }
    }

    uint8_t
    normalizeLedNrDown(uint8_t percentage)
    {
        return floorf((percentage / 127.0) * NUM_LEDS);
    }

    uint8_t normalizeLedNrUp(uint8_t percentage)
    {
        return ceilf((percentage / 127.0) * NUM_LEDS);
    }
};
