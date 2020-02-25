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
    EdtRgbLed(Drivers::RgbLedDriver *driver)
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
        switch (message.command)
        {

        case Messages::ColorCommands::SinglePulse:
        case Messages::ColorCommands::SingleSolid:
        case Messages::ColorCommands::SingleSpark:

            if (message.commands.singleColor.value > 0)
            {
                _animator.solid(message.commands.singleColor.hue, message.commands.singleColor.saturation, message.commands.singleColor.value);
            }

            if (message.command == Messages::ColorCommands::SinglePulse || message.commands.singleColor.value == 0)
            {
                _animator.fade(message.commands.singleColor.duration, FadeMode::FadeToBlack);
            }
            else if (message.command == Messages::ColorCommands::SingleSpark)
            {
                _animator.fade(message.commands.singleColor.duration, FadeMode::FadeOneByOne);
            }
            else
            {
                _animator.disableFade();
            }

            break;

        case Messages::ColorCommands::DualPulse:
        case Messages::ColorCommands::DualSolid:
        case Messages::ColorCommands::DualSparkle:

            _animator.solid(message.commands.dualColor.hue1, message.commands.dualColor.hue2, 255, 254, message.commands.dualColor.percentage);

            if (message.command == Messages::ColorCommands::DualPulse)
            {
                _animator.fade(message.commands.dualColor.duration, FadeMode::FadeToBlack);
            }
            else if (message.command == Messages::ColorCommands::DualSparkle)
            {
                _animator.fade(message.commands.dualColor.duration, FadeMode::FadeOneByOne);
            }
            else
            {
                _animator.disableFade();
            }

            break;

        case Messages::ColorCommands::RainbowPulse:
        case Messages::ColorCommands::RainbowSolid:
        case Messages::ColorCommands::RainbowSpark:

            if (message.commands.rainbow.deltaHue > 0)
            {
                _animator.rainbow(message.commands.rainbow.hue, message.commands.rainbow.deltaHue);
            }

            if (message.command == Messages::ColorCommands::RainbowPulse || message.commands.rainbow.deltaHue == 0)
            {
                _animator.fade(message.commands.rainbow.duration, FadeMode::FadeToBlack);
            }
            else if (message.command == Messages::ColorCommands::RainbowSpark)
            {
                _animator.fade(message.commands.rainbow.duration, FadeMode::FadeOneByOne);
            }
            else
            {
                _animator.disableFade();
            }

            break;

        case Messages::ColorCommands::VuMeter:

            if (message.commands.vuMeter.intensity > 0)
            {
                _animator.intensity(message.commands.vuMeter.intensity);
            }
            else
            {
                _animator.fade(127);
            }

            break;

        case Messages::ColorCommands::Twinkle:

            _animator.disableFade();

            if (message.commands.twinkle.intensity > 0)
            {
                _animator.solid(message.commands.twinkle.hue, 255, message.commands.twinkle.intensity - 1);
            }
            else
            {
                _animator.fade(127);
            }

            break;

        case Messages::ColorCommands::ChaseStill:

            _animator.chase(message.commands.chaseStill.hue, message.commands.chaseStill.length);

            break;

        case Messages::ColorCommands::Strobo:

            _animator.strobo(message.commands.strobo.hue, message.commands.strobo.intensity);

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