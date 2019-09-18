#pragma once

#include <CommandMessage.h>
#include <EdtDevice.h>
#include <FastLED.h>
#include <RgbLedDriver.h>
#include <RgbLedAnimator.h>

#include <Animation.h>
#include <Animations.h>
#include <AnimationType.h>
#include <FadeMode.h>
#include <LedState.h>

using namespace Animations;

namespace Devices
{
template <uint8_t NUMBER_OF_LEDS>
class EdtRgbLed : public EdtDevice
{
private:
    CRGB _leds[NUMBER_OF_LEDS];
    Animators::RgbLedAnimator _animator;

public:
    EdtRgbLed(Drivers::RgbLedDriver * driver)
    {
        _animator = Animators::RgbLedAnimator(_leds, NUMBER_OF_LEDS, driver);
    }

    void init()
    {
        _animator.solid(120, 240, 255);
        _animator.fade(2);
    }

    void handleMessage(Messages::CommandMessage message)
    {
        // todo: remove these variables
        auto command = message.command;
        auto dualColor = message.commands.dualColor;
        auto rainbow = message.commands.rainbow;
        auto singleColor = message.commands.singleColor;
        auto strobo = message.commands.strobo;
        auto twinkle = message.commands.twinkle;
        auto vuMeter = message.commands.vuMeter;

        switch (command)
        {

        case Messages::ColorCommands::SinglePulse:
        case Messages::ColorCommands::SingleSolid:
        case Messages::ColorCommands::SingleSpark:

            if (singleColor.value > 0)
            {
                _animator.solid(singleColor.hue, singleColor.saturation, singleColor.value);
            }

            if (command == Messages::ColorCommands::SinglePulse || singleColor.value == 0)
            {
                _animator.fade(singleColor.duration, FadeMode::FadeToBlack);
            }
            else if (command == Messages::ColorCommands::SingleSpark)
            {
                _animator.fade(singleColor.duration, FadeMode::FadeOneByOne);
            }
            else
            {
                _animator.disableFade();
            }

            break;

        case Messages::ColorCommands::DualPulse:
        case Messages::ColorCommands::DualSolid:
        case Messages::ColorCommands::DualSparkle:

            _animator.solid(dualColor.hue1, dualColor.hue2, 255, 254, dualColor.percentage);

            if (command == Messages::ColorCommands::DualPulse)
            {
                _animator.fade(dualColor.duration, FadeMode::FadeToBlack);
            }
            else if (command == Messages::ColorCommands::DualSparkle)
            {
                _animator.fade(dualColor.duration, FadeMode::FadeOneByOne);
            }
            else
            {
                _animator.disableFade();
            }

            break;

        case Messages::ColorCommands::RainbowPulse:
        case Messages::ColorCommands::RainbowSolid:
        case Messages::ColorCommands::RainbowSpark:

            if (rainbow.deltaHue > 0)
            {
                _animator.rainbow(rainbow.hue, rainbow.deltaHue);
            }

            if (command == Messages::ColorCommands::RainbowPulse || rainbow.deltaHue == 0)
            {
                _animator.fade(rainbow.duration, FadeMode::FadeToBlack);
            }
            else if (command == Messages::ColorCommands::RainbowSpark)
            {
                _animator.fade(rainbow.duration, FadeMode::FadeOneByOne);
            }
            else
            {
                _animator.disableFade();
            }

            break;

        case Messages::ColorCommands::VuMeter:

            if (vuMeter.intensity > 0)
            {
                _animator.intensity(vuMeter.intensity);
            }
            else
            {
                _animator.fade(127);
            }

            break;

        case Messages::ColorCommands::Twinkle:

            _animator.disableFade();

            if (twinkle.intensity > 0)
            {
                _animator.solid(twinkle.hue, 255, twinkle.intensity - 1);
            }
            else
            {
                _animator.fade(127);
            }

            break;

        case Messages::ColorCommands::Strobo:

            _animator.strobo(strobo.hue, strobo.intensity);

            break;

        default:

            break;
        }
    }

    void animate()
    {
        _animator.loop();
    }
};
} // namespace Devices