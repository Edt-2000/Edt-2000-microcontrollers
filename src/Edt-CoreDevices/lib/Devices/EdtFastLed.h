#pragma once

#include <CommandMessage.h>
#include <EdtDevice.h>
#include <FastLED.h>
#include <FastLedAnimator.h>

#include <Animation.h>
#include <Animations.h>
#include <AnimationType.h>
#include <FadeMode.h>
#include <LedState.h>

using namespace Animations;

namespace Devices
{
template <ESPIChipsets CHIPSET, uint8_t DATA_PIN, uint8_t CLOCK_PIN, EOrder RGB_ORDER, uint8_t NUMBER_OF_LEDS>
class EdtFastLed : public EdtDevice
{
private:
	CRGB _leds[NUMBER_OF_LEDS];
	Animators::FastLedAnimator _animator;

public:
	EdtFastLed()
	{
		FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, RGB_ORDER>(_leds, NUMBER_OF_LEDS);
		_animator = Animators::FastLedAnimator(_leds, NUMBER_OF_LEDS);
	}

	void init()
	{
		_animator.solid(0, 127, 120, 240, 255);
		_animator.fade(0, 127, 2);
	}

	void handleMessage(Messages::CommandMessage message)
	{
		// todo: remove these variables
		const auto command = message.command;
		const auto dualColor = message.commands.dualColor;
		const auto chase = message.commands.chase;
		const auto bash = message.commands.bash;
		const auto rainbow = message.commands.rainbow;
		const auto singleColor = message.commands.singleColor;
		const auto strobo = message.commands.strobo;
		const auto twinkle = message.commands.twinkle;
		const auto vuMeter = message.commands.vuMeter;

		switch (command)
		{

		case Messages::ColorCommands::SinglePulse:
		case Messages::ColorCommands::SingleSolid:
		case Messages::ColorCommands::SingleSpark:

			if (singleColor.value > 0)
			{
				_animator.solid(singleColor.start, singleColor.end, singleColor.hue, singleColor.saturation, singleColor.value);
			}

			if (command == Messages::ColorCommands::SinglePulse || singleColor.value == 0)
			{
				_animator.fade(singleColor.start, singleColor.end, singleColor.duration, FadeMode::FadeToBlack);
			}
			else if (command == Messages::ColorCommands::SingleSpark)
			{
				_animator.fade(singleColor.start, singleColor.end, singleColor.duration, FadeMode::FadeOneByOne);
			}
			else
			{
				_animator.disableFade(singleColor.start, singleColor.end);
			}

			break;

		case Messages::ColorCommands::DualPulse:
		case Messages::ColorCommands::DualSolid:
		case Messages::ColorCommands::DualSparkle:

			_animator.solid(dualColor.start, dualColor.end, dualColor.hue1, 255, 255);

			if (dualColor.percentage > 0)
			{
				_animator.twinkle(dualColor.start, dualColor.end, dualColor.hue2, 255, 255, dualColor.percentage, false);
			}

			if (command == Messages::ColorCommands::DualPulse)
			{
				_animator.fade(dualColor.start, dualColor.end, dualColor.duration, FadeMode::FadeToBlack);
			}
			else if (command == Messages::ColorCommands::DualSparkle)
			{
				_animator.fade(dualColor.start, dualColor.end, dualColor.duration, FadeMode::FadeOneByOne);
			}
			else
			{
				_animator.disableFade(dualColor.start, dualColor.end);
			}

			break;

		case Messages::ColorCommands::RainbowPulse:
		case Messages::ColorCommands::RainbowSolid:
		case Messages::ColorCommands::RainbowSpark:

			if (rainbow.deltaHue > 0)
			{
				_animator.rainbow(rainbow.start, rainbow.end, rainbow.hue, rainbow.deltaHue);
			}

			if (command == Messages::ColorCommands::RainbowPulse || rainbow.deltaHue == 0)
			{
				_animator.fade(rainbow.start, rainbow.end, rainbow.duration, FadeMode::FadeToBlack);
			}
			else if (command == Messages::ColorCommands::RainbowSpark)
			{
				_animator.fade(rainbow.start, rainbow.end, rainbow.duration, FadeMode::FadeOneByOne);
			}
			else
			{
				_animator.disableFade(rainbow.start, rainbow.end);
			}

			break;

		case Messages::ColorCommands::VuMeter:

			_animator.rainbow(vuMeter.start, vuMeter.center, vuMeter.end, vuMeter.hue, vuMeter.deltaHue, vuMeter.intensity);

			break;

		case Messages::ColorCommands::Twinkle:

			_animator.disableFade(twinkle.start, twinkle.end);

			if (twinkle.intensity > 0)
			{
				_animator.twinkle(twinkle.start, twinkle.end, twinkle.hue, 255, 255, twinkle.intensity);
			}
			else
			{
				_animator.fade(twinkle.start, twinkle.end, 127);
			}

			break;

		case Messages::ColorCommands::Strobo:

			_animator.strobo(strobo.hue, strobo.intensity);

			break;

		case Messages::ColorCommands::Chase:

			_animator.chase(chase.hue, chase.speed, (uint8_t)chase.style);

			break;

		case Messages::ColorCommands::Bash:

			_animator.bash(bash.hue, bash.intensity);

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