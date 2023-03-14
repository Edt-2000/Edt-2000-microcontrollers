#pragma once

#include "core.h"
#include "animationContainer.h"
#include "animations/stroboAnimation.h"

template <uint8_t DATA_PIN>
class FastLedDevice
{
private:
    OSC::StructMessage<FastLedCommand, uint32_t> _message;

public:
    Leds<DATA_PIN> fastLedLeds;

    AnimationContainer animations;

    FastLedDevice()
    {
        _message.messageStruct.mode = (ColorCommands)-1;
    }

    void init()
    {
        fastLedLeds.init();
    }

    void handleMessage(FastLedCommand message)
    {
        switch (message.mode)
        {

        case ColorCommands::SinglePulse:
        case ColorCommands::SingleSolid:
        case ColorCommands::SingleSpark:
        {
            auto start = fastLedLeds.normalizeLedNrDown(message.commands.singleColor.start);
            auto end = fastLedLeds.normalizeLedNrUp(message.commands.singleColor.end);

            if (message.commands.singleColor.value > 0)
            {
                fill_solid(fastLedLeds.leds + start, end - start, message.commands.singleColor.getColor());
            }

            if (message.mode == ColorCommands::SinglePulse || message.commands.singleColor.value == 0)
            {
                fastLedLeds.fade(start, end, message.commands.singleColor.duration, FadeMode::FadeToBlack);
            }
            else if (message.mode == ColorCommands::SingleSpark)
            {
                fastLedLeds.fade(start, end, message.commands.singleColor.duration, FadeMode::FadeOneByOne);
            }
            else
            {
                fastLedLeds.disableFade(start, end);
            }
        }
        break;

        case ColorCommands::DualPulse:
        case ColorCommands::DualSolid:
        case ColorCommands::DualSparkle:
        {
            auto start = fastLedLeds.normalizeLedNrDown(message.commands.dualColor.start);
            auto end = fastLedLeds.normalizeLedNrUp(message.commands.dualColor.end);

            fastLedLeds.randomize(start, end, message.commands.dualColor.percentage, message.commands.dualColor.getColor2(), message.commands.dualColor.getColor1());

            if (message.mode == ColorCommands::DualPulse)
            {
                fastLedLeds.fade(start, end, message.commands.dualColor.duration, FadeMode::FadeToBlack);
            }
            else if (message.mode == ColorCommands::DualSparkle)
            {
                fastLedLeds.fade(start, end, message.commands.dualColor.duration, FadeMode::FadeOneByOne);
            }
            else
            {
                fastLedLeds.disableFade(start, end);
            }
        }
        break;

        case ColorCommands::RainbowPulse:
        case ColorCommands::RainbowSolid:
        case ColorCommands::RainbowSpark:
        {
            auto start = fastLedLeds.normalizeLedNrDown(message.commands.rainbow.start);
            auto end = fastLedLeds.normalizeLedNrUp(message.commands.rainbow.end);

            if (message.commands.rainbow.deltaHue > 0)
            {
                fill_rainbow(fastLedLeds.leds + start, end - start, message.commands.rainbow.hue, (message.commands.rainbow.deltaHue / 127.0) * (255.0 / (end - start)));
            }

            if (message.mode == ColorCommands::RainbowPulse || message.commands.rainbow.deltaHue == 0)
            {
                fastLedLeds.fade(start, end, message.commands.rainbow.duration, FadeMode::FadeToBlack);
            }
            else if (message.mode == ColorCommands::RainbowSpark)
            {
                fastLedLeds.fade(start, end, message.commands.rainbow.duration, FadeMode::FadeOneByOne);
            }
            else
            {
                fastLedLeds.disableFade(start, end);
            }
        }
        break;

        case ColorCommands::VuMeter:
        {
            auto start = fastLedLeds.normalizeLedNrDown(message.commands.vuMeter.start);
            auto center = fastLedLeds.normalizeLedNrDown(message.commands.vuMeter.center);
            auto end = fastLedLeds.normalizeLedNrUp(message.commands.vuMeter.end);

            if (start != center)
            {
                int offset = (center - start) * (message.commands.vuMeter.intensity / 255.0);

                for (int i = start; i < center - offset; i++)
                {
                    fastLedLeds.fade(i, 127, FadeMode::FadeToBlack);
                }
                for (int i = center - offset; i < center; i++)
                {
                    fastLedLeds.fade(i, 255, FadeMode::FadeToBlack);
                }

                auto normalizedDeltaHue = 255 - (message.commands.vuMeter.deltaHue / (center - start));

                fill_rainbow(fastLedLeds.leds + (center - offset), offset, message.commands.vuMeter.hue + (offset * normalizedDeltaHue), 255 - normalizedDeltaHue);
            }
            if (center != end)
            {
                int offset = (end - center) * (message.commands.vuMeter.intensity / 255.0);

                for (int i = center + offset; i < end; i++)
                {
                    fastLedLeds.fade(i, 127, FadeMode::FadeToBlack);
                }
                for (int i = center; i < center + offset; i++)
                {
                    fastLedLeds.fade(i, 255, FadeMode::FadeToBlack);
                }

                auto normalizedDeltaHue = 255 - (message.commands.vuMeter.deltaHue / (end - center));

                fill_rainbow(fastLedLeds.leds + center, offset, message.commands.vuMeter.hue, normalizedDeltaHue);
            }
        }
        break;

        case ColorCommands::Twinkle:
        {
            auto start = fastLedLeds.normalizeLedNrDown(message.commands.twinkle.start);
            auto end = fastLedLeds.normalizeLedNrUp(message.commands.twinkle.end);

            fastLedLeds.randomize(start, end, message.commands.twinkle.intensity, message.commands.twinkle.getColor(), CRGB::Black);
            fastLedLeds.disableFade(start, end);

            if (message.commands.twinkle.intensity > 0)
            {
                fastLedLeds.randomize(start, end, message.commands.twinkle.intensity, message.commands.twinkle.getColor(), CRGB::Black);
            }
            else
            {
                fastLedLeds.fade(start, end, 127, FadeMode::FadeToBlack);
            }
        }
        break;

        case ColorCommands::Strobo:
        {
            fastLedLeds.disableFade();

            fill_solid(fastLedLeds.leds, fastLedLeds.nrOfLeds, CRGB::Black);

            animations.resetAnimations();

            if (message.commands.strobo.intensity > 0)
            {
                auto animation = new StroboAnimation(message.commands.strobo, &fastLedLeds);
                animations.insertAnimation(animation);
            }
        }
        break;

            // case ColorCommands::Chase:

            //     _animator.chase(message.commands.chase.hue, message.commands.chase.speed, (uint8_t)message.commands.chase.fadeSpeed, (bool)message.commands.chase.direction);

            //     break;

            // case ColorCommands::ChaseStill:

            //     _animator.chase(message.commands.chaseStill.hue, message.commands.chaseStill.length);

            //     break;

        default:
            // set to off
            fill_solid(fastLedLeds.leds, fastLedLeds.nrOfLeds, CRGB::Black);
            break;
        }
    }

    void animate()
    {
        animations.animate();
    }
};
