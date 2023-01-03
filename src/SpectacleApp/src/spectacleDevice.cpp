#include "spectacleDevice.h"
#include "animations/chaseAnimation.h"
#include "animations/fireAnimation.h"
#include "animations/stroboAnimation.h"
#include "animations/theaterChaseAnimation.h"

void SpectacleDevice::init()
{
    FastLED.addLeds<WS2811, 4, GRB>(leds, nrOfLeds).setCorrection(TypicalLEDStrip);

    fill_solid(leds, 1, CRGB::Green);
    ledState[0].fade = 2;
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
        auto start = normalizeLedNrDown(message.commands.singleColor.start);
        auto end = normalizeLedNrUp(message.commands.singleColor.end);

        if (message.commands.singleColor.value > 0)
        {
            fill_solid(leds + start, end - start, message.commands.singleColor.getColor());
        }

        if (message.mode == ColorCommands::SinglePulse || message.commands.singleColor.value == 0)
        {
            fade(start, end, message.commands.singleColor.duration, FadeMode::FadeToBlack);
        }
        else if (message.mode == ColorCommands::SingleSpark)
        {
            fade(start, end, message.commands.singleColor.duration, FadeMode::FadeOneByOne);
        }
        else
        {
            disableFade(start, end);
        }
    }
    break;
    case Messages::ColorCommands::DualPulse:
    case Messages::ColorCommands::DualSolid:
    case Messages::ColorCommands::DualSparkle:
    {
        auto start = normalizeLedNrDown(message.commands.singleColor.start);
        auto end = normalizeLedNrUp(message.commands.singleColor.end);

        randomize(start, end, message.commands.dualColor.percentage, _message.messageStruct.commands.dualColor.getColor2(), message.commands.dualColor.getColor1());

        if (message.mode == ColorCommands::DualPulse)
        {
            fade(start, end, message.commands.dualColor.duration, FadeMode::FadeToBlack);
        }
        else if (message.mode == ColorCommands::DualSparkle)
        {
            fade(start, end, message.commands.dualColor.duration, FadeMode::FadeOneByOne);
        }
        else
        {
            disableFade(start, end);
        }
    }
    break;
    case ColorCommands::RainbowPulse:
    case ColorCommands::RainbowSolid:
    case ColorCommands::RainbowSpark:
    {
        auto start = normalizeLedNrDown(message.commands.rainbow.start);
        auto end = normalizeLedNrUp(message.commands.rainbow.end);

        if (message.commands.rainbow.deltaHue > 0)
        {
            fill_rainbow(leds + start, end - start, message.commands.rainbow.hue, (message.commands.rainbow.deltaHue / 127.0) * (255.0 / (end - start)));
        }

        if (message.mode == ColorCommands::RainbowPulse || message.commands.rainbow.deltaHue == 0)
        {
            fade(start, end, message.commands.rainbow.duration, FadeMode::FadeToBlack);
        }
        else if (message.mode == ColorCommands::RainbowSpark)
        {
            fade(start, end, message.commands.rainbow.duration, FadeMode::FadeOneByOne);
        }
        else
        {
            disableFade(start, end);
        }
    }
    break;
    case ColorCommands::Twinkle:
    {
        auto start = normalizeLedNrDown(_message.messageStruct.commands.twinkle.start);
        auto end = normalizeLedNrUp(_message.messageStruct.commands.twinkle.end);

        randomize(start, end, _message.messageStruct.commands.twinkle.intensity, _message.messageStruct.commands.twinkle.getColor(), CRGB::Black);
        disableFade(start, end);
    }
    break;
    case ColorCommands::Strobo:
    {
        disableFade(0, nrOfLeds);

        fill_solid(leds, nrOfLeds, CRGB::Black);

        animations.resetAnimations();

        if (_message.messageStruct.commands.strobo.intensity > 0)
        {
            animations.insertAnimation(new StroboAnimation(
                _message.messageStruct.commands.strobo));
        }
    }
    break;
    case ColorCommands::Chase:
    {
        animations.insertAnimation(new ChaseAnimation(
            _message.messageStruct.commands.chase));
    }
    break;
    case ColorCommands::Fire:
    {
        disableFade(0, nrOfLeds);

        fill_solid(leds, nrOfLeds, CRGB::Black);

        animations.resetAnimations();

        animations.insertAnimation(new FireAnimation(
            _message.messageStruct.commands.fire));
    }
    break;
    case ColorCommands::TheaterChase:
    {
        disableFade(0, nrOfLeds);

        fill_solid(leds, nrOfLeds, CRGB::Black);

        animations.resetAnimations();

        animations.insertAnimation(new TheaterChaseAnimation(
            _message.messageStruct.commands.theater));
    }
    break;
    default:
        // set to off
        fill_solid(leds, nrOfLeds, CRGB::Black);
        break;
    }
}

void SpectacleDevice::loop(App::Time time)
{
    if (time.tVISUAL)
    {
        animations.animate(this);

        fadeLoop();

        FastLED.show();
    }
}

uint8_t SpectacleDevice::normalizeLedNrDown(uint8_t percentage)
{
    return floorf((percentage / 127.0) * nrOfLeds);
}

uint8_t SpectacleDevice::normalizeLedNrUp(uint8_t percentage)
{
    return ceilf((percentage / 127.0) * nrOfLeds);
}

void SpectacleDevice::fade(uint8_t start, uint8_t end, uint8_t speed, FadeMode fadeMode)
{
    activeFadeMode = fadeMode;

    for (int i = start; i < end; i++)
    {
        ledState[i].fade = speed;
    }
}

void SpectacleDevice::disableFade(uint8_t start, uint8_t end)
{
    for (int i = start; i < end; i++)
    {
        ledState[i].fade = 255;
    }
}

void SpectacleDevice::randomize(uint8_t start, uint8_t end, uint8_t percentage, CRGB color1, CRGB color2)
{
    for (int i = start; i < end; i++)
    {
        if (percentage > random8())
        {
            leds[i] = color1;
        }
        else
        {
            leds[i] = color2;
        }
    }
}

void SpectacleDevice::fadeLoop()
{
    switch (activeFadeMode)
    {
    case FadeMode::FadeToBlack:
        for (int i = 0; i < nrOfLeds; i++)
        {
            if (ledState[i].fade < 255)
            {
                if (ledState[i].fade > 255 - 5)
                {
                    ledState[i].fade = 255;
                }
                else
                {
                    ledState[i].fade += 1;
                }

                fadeToBlackBy(leds + i, 1, ledState[i].fade);
            }
        }
        break;
    case FadeMode::FadeOneByOne:
        for (int i = 0; i < nrOfLeds; i++)
        {
            if (ledState[i].fade < 255)
            {
                if (ledState[i].fade / 8 > random8())
                {
                    ledState[i].fade = 255;

                    fadeToBlackBy(leds + i, 1, 255);
                }
                else
                {
                    fadeToBlackBy(leds + i, 1, 2);
                }
            }
        }
        break;
    }
}