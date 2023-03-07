#include "fastLedDevice.h"

void FastLedDevice<DATA_PIN>::init()
{
    fastLedLeds.leds.init();
}

void FastLedDevice<DATA_PIN>::handleMessage(FastLedCommand message)
{
    switch (message.mode)
    {

    case ColorCommands::SinglePulse:
    case ColorCommands::SingleSolid:
    case ColorCommands::SingleSpark:
    {
        auto start = leds.fastLedLeds.leds.normalizeLedNrDown(message.commands.singleColor.start);
        auto end = fastLedLeds.leds.normalizeLedNrUp(message.commands.singleColor.end);

        if (message.commands.singleColor.value > 0)
        {
            fill_solid(leds + start, end - start, message.commands.singleColor.getColor());
        }

        if (message.command == ColorCommands::SinglePulse || message.commands.singleColor.value == 0)
        {
            fastLedLeds.leds.fade(start, end, message.commands.singleColor.duration, FadeMode::FadeToBlack);
        }
        else if (message.command == ColorCommands::SingleSpark)
        {
            fastLedLeds.leds.fade(start, end, message.commands.singleColor.duration, FadeMode::FadeOneByOne);
        }
        else
        {
            fastLedLeds.leds.disableFade(start, end);
        }
    }
    break;

    case ColorCommands::DualPulse:
    case ColorCommands::DualSolid:
    case ColorCommands::DualSparkle:
    {
        auto start = fastLedLeds.leds.normalizeLedNrDown(message.commands.dualColor.start);
        auto end = fastLedLeds.leds.normalizeLedNrUp(message.commands.dualColor.end);

        fastLedLeds.leds.randomize(start, end, message.commands.dualColor.percentage, message.commands.dualColor.getColor2(), message.commands.dualColor.getColor1());

        if (message.command == ColorCommands::DualPulse)
        {
            fastLedLeds.leds.fade(start, end, message.commands.dualColor.duration, FadeMode::FadeToBlack);
        }
        else if (message.command == ColorCommands::DualSparkle)
        {
            fastLedLeds.leds.fade(start, end, message.commands.dualColor.duration, FadeMode::FadeOneByOne);
        }
        else
        {
            fastLedLeds.leds.disableFade(start, end);
        }
    }
    break;

    case ColorCommands::RainbowPulse:
    case ColorCommands::RainbowSolid:
    case ColorCommands::RainbowSpark:
    {
        auto start = fastLedLeds.leds.normalizeLedNrDown(message.commands.rainbow.start);
        auto end = fastLedLeds.leds.normalizeLedNrUp(message.commands.rainbow.end);

        if (message.commands.rainbow.deltaHue > 0)
        {
            fill_rainbow(leds + start, end - start, message.commands.rainbow.hue, (message.commands.rainbow.deltaHue / 127.0) * (255.0 / (end - start)));
        }

        if (message.command == ColorCommands::RainbowPulse || message.commands.rainbow.deltaHue == 0)
        {
            fastLedLeds.leds.fade(start, end, message.commands.rainbow.duration, FadeMode::FadeToBlack);
        }
        else if (message.command == ColorCommands::RainbowSpark)
        {
            fastLedLeds.leds.fade(start, end, message.commands.rainbow.duration, FadeMode::FadeOneByOne);
        }
        else
        {
            fastLedLeds.leds.disableFade(start, end);
        }
    }
    break;

    case ColorCommands::VuMeter:
    {
        auto start = fastLedLeds.leds.normalizeLedNrDown(message.commands.vuMeter.start);
        auto center = fastLedLeds.leds.normalizeLedNrDown(message.commands.vuMeter.center);
        auto end = fastLedLeds.leds.normalizeLedNrUp(message.commands.vuMeter.end);

        if (start != center)
        {
            auto offset = (center - start) * (message.commands.vuMeter.intensity / 255.0);

            for (int i = start; i < center - offset; i++)
            {
                fastLedLeds.leds.fade(i, 127, FadeMode::FadeToBlack);
            }
            for (int i = center - offset; i < center; i++)
            {
                fastLedLeds.leds.fade(i, 255, FadeMode::FadeToBlack);
            }

            auto normalizedDeltaHue = 255 - (message.commands.vuMeter.deltaHue / (center - start));

            fill_rainbow(&fastLedLeds.leds[center - offset], offset, message.commands.vuMeter.hue + (offset * normalizedDeltaHue), 255 - normalizedDeltaHue);
        }
        if (center != end)
        {
            int offset = (end - center) * (message.commands.vuMeter.intensity / 255.0);

            for (int i = center + offset; i < end; i++)
            {
                fastLedLeds.leds.fade(i, 127, FadeMode::FadeToBlack);
            }
            for (int i = center; i < center + offset; i++)
            {
                fastLedLeds.leds.fade(i, 255, FadeMode::FadeToBlack);
            }

            auto normalizedDeltaHue = 255 - (message.commands.vuMeter.deltaHue / (end - center));

            fill_rainbow(&fastLedLeds.leds[center], offset, message.commands.vuMeter.hue, normalizedDeltaHue);
        }
    }
    break;

    case ColorCommands::Twinkle:
    {
        auto start = fastLedLeds.leds.normalizeLedNrDown(message.commands.twinkle.start);
        auto end = fastLedLeds.leds.normalizeLedNrUp(message.commands.twinkle.end);

        fastLedLeds.leds.randomize(start, end, message.commands.twinkle.intensity, message.commands.twinkle.getColor(), CRGB::Black);
        fastLedLeds.leds.disableFade(start, end);

        if (message.commands.twinkle.intensity > 0)
        {
            fastLedLeds.leds.randomize(start, end, message.commands.twinkle.intensity, message.commands.twinkle.getColor(), CRGB::Black);
        }
        else
        {
            fastLedLeds.leds.fade(start, end, 127, FadeMode::FadeToBlack);
        }
    }
    break;

    case ColorCommands::Strobo:
    {
        fastLedLeds.leds.disableFade();

        fill_solid(fastLedLeds.leds, fastLedLeds.nrOfLeds, CRGB::Black);

        animations.resetAnimations();

        if (message.commands.strobo.intensity > 0)
        {
            animations.insertAnimation(new StroboAnimation(message.commands.strobo));
        }

        _animator.strobo(message.commands.strobo.hue, message.commands.strobo.intensity);
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
        fill_solid(fastLedfastLedLeds.leds.leds, fastLedfastLedLeds.leds.nrOfLeds, CRGB::Black);
        break;
    }
}

void FastLedDevice::animate()
{
    _animator.loop();
}