#include <RgbLedAnimator.h>
#include <ColorHelper.h>

using namespace Animations;

void Animators::RgbLedAnimator::fade(uint8_t speed, FadeMode fadeMode)
{
	_ledState.fade = speed;
}

void Animators::RgbLedAnimator::disableFade()
{
	_ledState.fade = 255;
}

void Animators::RgbLedAnimator::solid(uint8_t hue, uint8_t saturation, uint8_t value)
{
	fill_solid(_leds, nrOfLeds, ColorHelper::CreateColor(hue, saturation, value));
}

void Animators::RgbLedAnimator::solid(CHSV color)
{
	fill_solid(_leds, nrOfLeds, color);
}

void Animators::RgbLedAnimator::solid(uint8_t hue1, uint8_t hue2, uint8_t saturation, uint8_t value, uint8_t percentage)
{
	for (int i = 0; i < nrOfLeds; i++)
	{
		if (percentage > random8())
		{
			auto color = ColorHelper::CreateColor(hue2, saturation, value);
			_leds[i].setHSV(color.hue, color.saturation, color.value);
		}
		else
		{
			auto color = ColorHelper::CreateColor(hue1, saturation, value);
			_leds[i].setHSV(color.hue, color.saturation, color.value);
		}
	}
}

void Animators::RgbLedAnimator::rainbow(uint8_t hue, uint8_t deltaHue)
{
	fill_rainbow(_leds, nrOfLeds, hue, (deltaHue / 127.0) * (255.0 / nrOfLeds));
}

void Animators::RgbLedAnimator::intensity(uint8_t intensity)
{
	if (intensity == 0)
	{
		fill_solid(_leds, nrOfLeds, CRGB::HTMLColorCode::Black);
	}
	else
	{
		fill_solid(_leds, nrOfLeds, ColorHelper::CreateColor(0 + (85 - (intensity / 2.5)), 255, intensity));
	}
}

void Animators::RgbLedAnimator::strobo(uint8_t hue, uint8_t fps)
{
	disableFade();

	fill_solid(_leds, nrOfLeds, CRGB::HTMLColorCode::Black);

	if (fps == 0)
	{
		_animations.resetAnimations();
	}
	else
	{
		_animations.insertAnimation(Animation(AnimationType::Strobo, ColorHelper::CreateColor(hue, 255, 255), 255.0 / fps, 0));
	}
}

void Animators::RgbLedAnimator::chase(uint8_t hue, uint8_t length)
{
	auto existingChase = _animations.getAnimation(AnimationType::ChaseStill);

	if (existingChase != nullptr)
	{
		if (existingChase->state >= 120 - length)
		{
			_animations.removeAnimation(AnimationType::ChaseStill);
			fade(127, FadeMode::FadeToBlack);
		}
		else
		{
			existingChase->state += length;
		}
	}
	else
	{
		_animations.addAnimation(Animation(AnimationType::ChaseStill, ColorHelper::CreateColor(hue, 255, 255), length, 0));
	}
}

void Animators::RgbLedAnimator::loop()
{
	uint8_t from;
	uint8_t to;

	for (auto &animation : _animations.animations)
	{
		switch (animation.type)
		{
		case AnimationType::Strobo:

			fill_solid(_leds, nrOfLeds, ColorHelper::CreateColor(0, 0, 0));

			if ((animation.state++) > animation.data)
			{
				animation.state = 0;

				fill_solid(_leds, nrOfLeds, animation.color);
			}

			// there is nothing else to animate besides flashing of the strobo
			_output();
			return;
		case AnimationType::ChaseStill:

			from = animation.state;
			to = animation.state + animation.data;

			solid(from, to, animation.color);

			break;
		}
	}

	if (_ledState.fade < 255)
	{
		if (_ledState.fade > 255 - 62)
		{
			_ledState.fade = 255;
		}
		else
		{
			_ledState.fade += ((_ledState.fade) / 4) + 1;
		}

		fadeToBlackBy(_leds, nrOfLeds, _ledState.fade);
	}

	_output();
}

inline void Animators::RgbLedAnimator::_output()
{
	_driver->reset();

	for (int i = 0; i < nrOfLeds; i++)
	{
		_driver->output(_leds[i].red, _leds[i].green, _leds[i].blue);
	}
}

void Animators::RgbLedAnimator::solid(uint8_t start, uint8_t end, CHSV color)
{
	_start = normalizeLedNrDown(start);
	_end = normalizeLedNrUp(end);

	fill_solid(_leds + _start, _end - _start, color);
}