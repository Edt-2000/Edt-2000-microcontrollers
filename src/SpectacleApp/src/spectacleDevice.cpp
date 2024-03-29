#include "spectacleDevice.h"

void SpectacleDevice::init()
{
    SpectacleLeds.init();
}

const char *SpectacleDevice::address()
{
    return oscAddress;
}

OSC::IMessage *SpectacleDevice::message()
{
    return &_message;
}

void SpectacleDevice::callbackMessage()
{
    auto message = _message.messageStruct;

    switch (message.mode)
    {
    case ColorCommands::SingleSolid:
    case ColorCommands::SinglePulse:
    case ColorCommands::SingleSpark:
    {
        auto start = SpectacleLeds.normalizeLedNrDown(message.commands.singleColor.start);
        auto end = SpectacleLeds.normalizeLedNrUp(message.commands.singleColor.end);

        if (message.commands.singleColor.value > 0)
        {
            fill_solid(SpectacleLeds.leds + start, end - start, message.commands.singleColor.getColor());
        }

        if (message.mode == ColorCommands::SinglePulse || message.commands.singleColor.value == 0)
        {
            SpectacleLeds.fade(start, end, message.commands.singleColor.duration, FadeMode::FadeToBlack);
        }
        else if (message.mode == ColorCommands::SingleSpark)
        {
            SpectacleLeds.fade(start, end, message.commands.singleColor.duration, FadeMode::FadeOneByOne);
        }
        else
        {
            SpectacleLeds.disableFade(start, end);
        }
    }
    break;

    case ColorCommands::DualPulse:
    case ColorCommands::DualSolid:
    case ColorCommands::DualSparkle:
    {
        auto start = SpectacleLeds.normalizeLedNrDown(message.commands.dualColor.start);
        auto end = SpectacleLeds.normalizeLedNrUp(message.commands.dualColor.end);

        SpectacleLeds.randomize(start, end, message.commands.dualColor.percentage, message.commands.dualColor.getColor2(), message.commands.dualColor.getColor1());

        if (message.mode == ColorCommands::DualPulse)
        {
            SpectacleLeds.fade(start, end, message.commands.dualColor.duration, FadeMode::FadeToBlack);
        }
        else if (message.mode == ColorCommands::DualSparkle)
        {
            SpectacleLeds.fade(start, end, message.commands.dualColor.duration, FadeMode::FadeOneByOne);
        }
        else
        {
            SpectacleLeds.disableFade(start, end);
        }
    }
    break;

    case ColorCommands::RainbowPulse:
    case ColorCommands::RainbowSolid:
    case ColorCommands::RainbowSpark:
    {
        auto start = SpectacleLeds.normalizeLedNrDown(message.commands.rainbow.start);
        auto end = SpectacleLeds.normalizeLedNrUp(message.commands.rainbow.end);

        if (message.commands.rainbow.deltaHue > 0)
        {
            fill_rainbow(SpectacleLeds.leds + start, end - start, message.commands.rainbow.hue, (message.commands.rainbow.deltaHue / 127.0) * (255.0 / (end - start)));
        }

        if (message.mode == ColorCommands::RainbowPulse || message.commands.rainbow.deltaHue == 0)
        {
            SpectacleLeds.fade(start, end, message.commands.rainbow.duration, FadeMode::FadeToBlack);
        }
        else if (message.mode == ColorCommands::RainbowSpark)
        {
            SpectacleLeds.fade(start, end, message.commands.rainbow.duration, FadeMode::FadeOneByOne);
        }
        else
        {
            SpectacleLeds.disableFade(start, end);
        }
    }
    break;

    case ColorCommands::Twinkle:
    {
        auto start = SpectacleLeds.normalizeLedNrDown(message.commands.twinkle.start);
        auto end = SpectacleLeds.normalizeLedNrUp(message.commands.twinkle.end);

        SpectacleLeds.randomize(start, end, message.commands.twinkle.intensity, message.commands.twinkle.getColor(), CRGB::Black);
        SpectacleLeds.disableFade(start, end);
    }
    break;

    case ColorCommands::VuMeter:
    {
        auto intensity = (uint8_t)(message.commands.vuMeter.intensity == 0
                                       ? 0.0
                                       : message.commands.vuMeter.intensity / 36.0);

        SpectacleLeds.disableFade();
        fill_solid(SpectacleLeds.leds, SpectacleLeds.nrOfLeds, CRGB::Black);

        for (uint8_t i = 0; i < intensity; i++)
        {
            auto leds = SpectacleLeds.level(i);

            for (uint8_t j = 0; j < 4; j++)
            {
                SpectacleLeds.leds[leds[j]] = CHSV(85 - (i * 16), 255, 255);
            }
        }
    }
    break;

    case ColorCommands::Strobo:
    {
        SpectacleLeds.disableFade();

        fill_solid(SpectacleLeds.leds, SpectacleLeds.nrOfLeds, CRGB::Black);

        animations.resetAnimations();

        if (message.commands.strobo.intensity > 0)
        {
            animations.insertAnimation(new StroboAnimation(message.commands.strobo));
        }
    }
    break;

    case ColorCommands::Chase:
    {
        animations.insertAnimation(new ChaseAnimation(
            message.commands.chase));
    }
    break;
    case ColorCommands::Fire:
    {
        SpectacleLeds.disableFade();

        fill_solid(SpectacleLeds.leds, SpectacleLeds.nrOfLeds, CRGB::Black);

        animations.resetAnimations();

        animations.insertAnimation(new FireAnimation(message.commands.fire));
    }
    break;

    case ColorCommands::TheaterChase:
    {
        SpectacleLeds.disableFade();

        fill_solid(SpectacleLeds.leds, SpectacleLeds.nrOfLeds, CRGB::Black);

        animations.resetAnimations();

        animations.insertAnimation(new TheaterChaseAnimation(message.commands.theater));
    }
    break;

    case ColorCommands::Swipe:
    {
        SpectacleLeds.disableFade();

        fill_solid(SpectacleLeds.leds, SpectacleLeds.nrOfLeds, CRGB::Black);

        animations.addAnimation(new SwipeAnimation(message.commands.swipe));
    }
    break;

    default:
        // set to off
        fill_solid(SpectacleLeds.leds, SpectacleLeds.nrOfLeds, CRGB::Black);
        break;
    }
}

void SpectacleDevice::loop(App::Time time)
{
    if (time.tVISUAL)
    {
        animations.animate();
        SpectacleLeds.loop();
    }
}