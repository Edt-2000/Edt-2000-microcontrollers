#pragma once

#define FASTLED_FORCE_SOFTWARE_SPI

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
		// TODO: check if higher frequency is correct now
		FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, RGB_ORDER, DATA_RATE_KHZ(500)>(_leds, NUMBER_OF_LEDS);
		// FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, RGB_ORDER>(_leds, NUMBER_OF_LEDS);
		_animator = Animators::FastLedAnimator(_leds, NUMBER_OF_LEDS);
	}

	void init()
	{
		_animator.solid(0, 127, 120, 240, 255);
		_animator.fade(0, 127, 2);
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
				_animator.solid(message.commands.singleColor.start, message.commands.singleColor.end, message.commands.singleColor.hue, message.commands.singleColor.saturation, message.commands.singleColor.value);
			}

			if (message.command == Messages::ColorCommands::SinglePulse || message.commands.singleColor.value == 0)
			{
				_animator.fade(message.commands.singleColor.start, message.commands.singleColor.end, message.commands.singleColor.duration, FadeMode::FadeToBlack);
			}
			else if (message.command == Messages::ColorCommands::SingleSpark)
			{
				_animator.fade(message.commands.singleColor.start, message.commands.singleColor.end, message.commands.singleColor.duration, FadeMode::FadeOneByOne);
			}
			else
			{
				_animator.disableFade(message.commands.singleColor.start, message.commands.singleColor.end);
			}

			break;

		case Messages::ColorCommands::DualPulse:
		case Messages::ColorCommands::DualSolid:
		case Messages::ColorCommands::DualSparkle:

			_animator.solid(message.commands.dualColor.start, message.commands.dualColor.end, message.commands.dualColor.hue1, 255, 255);

			if (message.commands.dualColor.percentage > 0)
			{
				_animator.twinkle(message.commands.dualColor.start, message.commands.dualColor.end, message.commands.dualColor.hue2, 255, 255, message.commands.dualColor.percentage, false);
			}

			if (message.command == Messages::ColorCommands::DualPulse)
			{
				_animator.fade(message.commands.dualColor.start, message.commands.dualColor.end, message.commands.dualColor.duration, FadeMode::FadeToBlack);
			}
			else if (message.command == Messages::ColorCommands::DualSparkle)
			{
				_animator.fade(message.commands.dualColor.start, message.commands.dualColor.end, message.commands.dualColor.duration, FadeMode::FadeOneByOne);
			}
			else
			{
				_animator.disableFade(message.commands.dualColor.start, message.commands.dualColor.end);
			}

			break;

		case Messages::ColorCommands::RainbowPulse:
		case Messages::ColorCommands::RainbowSolid:
		case Messages::ColorCommands::RainbowSpark:

			if (message.commands.rainbow.deltaHue > 0)
			{
				_animator.rainbow(message.commands.rainbow.start, message.commands.rainbow.end, message.commands.rainbow.hue, message.commands.rainbow.deltaHue);
			}

			if (message.command == Messages::ColorCommands::RainbowPulse || message.commands.rainbow.deltaHue == 0)
			{
				_animator.fade(message.commands.rainbow.start, message.commands.rainbow.end, message.commands.rainbow.duration, FadeMode::FadeToBlack);
			}
			else if (message.command == Messages::ColorCommands::RainbowSpark)
			{
				_animator.fade(message.commands.rainbow.start, message.commands.rainbow.end, message.commands.rainbow.duration, FadeMode::FadeOneByOne);
			}
			else
			{
				_animator.disableFade(message.commands.rainbow.start, message.commands.rainbow.end);
			}

			break;

		case Messages::ColorCommands::VuMeter:

			_animator.rainbow(message.commands.vuMeter.start, message.commands.vuMeter.center, message.commands.vuMeter.end, message.commands.vuMeter.hue, message.commands.vuMeter.deltaHue, message.commands.vuMeter.intensity);

			break;

		case Messages::ColorCommands::Twinkle:

			_animator.disableFade(message.commands.twinkle.start, message.commands.twinkle.end);

			if (message.commands.twinkle.intensity > 0)
			{
				_animator.twinkle(message.commands.twinkle.start, message.commands.twinkle.end, message.commands.twinkle.hue, 255, 255, message.commands.twinkle.intensity);
			}
			else
			{
				_animator.fade(message.commands.twinkle.start, message.commands.twinkle.end, 127);
			}

			break;

		case Messages::ColorCommands::Strobo:

			_animator.strobo(message.commands.strobo.hue, message.commands.strobo.intensity);

			break;

		case Messages::ColorCommands::Berserk:

			_animator.berserk();

			break;

		case Messages::ColorCommands::Chase:

			_animator.chase(message.commands.chase.hue, message.commands.chase.speed, (uint8_t)message.commands.chase.style);

			break;

		case Messages::ColorCommands::ChaseStill:

			_animator.chase(message.commands.chaseStill.hue, message.commands.chaseStill.length);

			break;

		case Messages::ColorCommands::Bash:

			_animator.bash(message.commands.bash.hue, message.commands.bash.intensity);

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