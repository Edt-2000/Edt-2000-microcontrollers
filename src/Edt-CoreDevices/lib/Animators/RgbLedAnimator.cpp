#include "RgbLedAnimator.h"

#define HUE(h) h
#define VALUE(v) v // + ((255 - v) * INTENSITY_BOOST)

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
	fill_solid(_leds, nrOfLeds, CHSV(HUE(hue), saturation, VALUE(value)));
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
			_leds[i].setHSV(HUE(hue2), saturation, VALUE(value));
		}
		else
		{
			_leds[i].setHSV(HUE(hue1), saturation, VALUE(value));
		}
	}
}

void Animators::RgbLedAnimator::rainbow(uint8_t hue, uint8_t deltaHue)
{
	fill_rainbow(_leds, nrOfLeds, HUE(hue), (deltaHue / 127.0) * (255.0 / nrOfLeds));
}

void Animators::RgbLedAnimator::intensity(uint8_t intensity)
{
	if (intensity == 0)
	{
		fill_solid(_leds, nrOfLeds, CRGB::HTMLColorCode::Black);
	}
	else
	{
		fill_solid(_leds, nrOfLeds, CHSV(HUE(0) + (85 - (intensity / 2.5)), 255, VALUE(intensity)));
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
		if (hue < 255)
		{
			_animations.insertAnimation(Animation(AnimationType::Strobo, CHSV(HUE(hue), 255, 255), 255.0 / fps, 0));
		}
		else
		{
			_animations.insertAnimation(Animation(AnimationType::Strobo, CHSV(0, 0, 255), 255.0 / fps, 0));
		}
	}
}

void Animators::RgbLedAnimator::loop()
{
	int i = 0;

	while (i < _animations.animationsActive)
	{
		switch (_animations.animations[i].type)
		{
		case AnimationType::Strobo:

			fill_solid(_leds, nrOfLeds, CHSV(0, 0, 0));

			if ((_animations.animations[i].state++) > _animations.animations[i].data)
			{
				_animations.animations[i].state = 0;

				fill_solid(_leds, nrOfLeds, _animations.animations[i].color);
			}

			// there is nothing else to animate besides flashing of the strobo
			_output();
			return;
		}

		i++;
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