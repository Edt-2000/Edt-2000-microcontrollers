#include <FastLedAnimator.h>

using namespace Animations;

void Animators::FastLedAnimator::fade(uint8_t start, uint8_t end, uint8_t speed, FadeMode fadeMode)
{
	_start = normalizeLedNrDown(start);
	_end = normalizeLedNrUp(end);

	_fadeMode = fadeMode;

	for (int i = _start; i < _end; i++)
	{
		_ledState[i].fade = speed;
	}
}

void Animators::FastLedAnimator::disableFade(uint8_t start, uint8_t end)
{
	_start = normalizeLedNrDown(start);
	_end = normalizeLedNrUp(end);

	for (int i = _start; i < _end; i++)
	{
		_ledState[i].fade = 255;
	}
}

void Animators::FastLedAnimator::solid(uint8_t start, uint8_t end, uint8_t hue, uint8_t saturation, uint8_t value)
{
	solid(start, end, CHSV(hue, saturation, value));
}

void Animators::FastLedAnimator::solid(uint8_t start, uint8_t end, CHSV color)
{
	_start = normalizeLedNrDown(start);
	_end = normalizeLedNrUp(end);

	fill_solid(_leds + _start, _end - _start, color);
}

void Animators::FastLedAnimator::rainbow(uint8_t start, uint8_t end, uint8_t hue, uint8_t deltaHue)
{
	_start = normalizeLedNrDown(start);
	_end = normalizeLedNrUp(end);
	fill_rainbow(_leds + _start, _end - _start, hue, (deltaHue / 127.0) * (255.0 / (_end - _start)));
}

void Animators::FastLedAnimator::rainbow(uint8_t start, uint8_t center, uint8_t end, uint8_t hue, uint8_t deltaHue, uint8_t intensity)
{
	_start = normalizeLedNrDown(start);
	_center = normalizeLedNrDown(center);
	_end = normalizeLedNrUp(end);

	if (_start != _center)
	{
		int leds = (_center - _start) * (intensity / 255.0);

		for (int i = _start; i < _center - leds; i++)
		{
			_ledState[i].fade = 127;
		}
		for (int i = _center - leds; i < _center; i++)
		{
			_ledState[i].fade = 255;
		}

		auto normalizedDeltaHue = 255 - (deltaHue / (_center - _start));

		fill_rainbow(&_leds[_center - leds], leds, hue + (leds * normalizedDeltaHue), 255 - normalizedDeltaHue);
	}
	if (_center != _end)
	{
		int leds = (_end - _center) * (intensity / 255.0);

		for (int i = _center + leds; i < _end; i++)
		{
			_ledState[i].fade = 127;
		}
		for (int i = _center; i < _center + leds; i++)
		{
			_ledState[i].fade = 255;
		}

		auto normalizedDeltaHue = 255 - (deltaHue / (_end - _center));

		fill_rainbow(&_leds[_center], leds, hue, normalizedDeltaHue);
	}
}

void Animators::FastLedAnimator::twinkle(uint8_t start, uint8_t end, uint8_t hue, uint8_t saturation, uint8_t value, uint8_t intensity, bool blackOut)
{
	_start = normalizeLedNrDown(start);
	_end = normalizeLedNrDown(end);

	for (int i = _start; i < _end; i++)
	{
		if (intensity > random8())
		{
			_leds[i] = CHSV(hue, saturation, value);
		}
		else if (blackOut)
		{
			_leds[i] = CHSV(0, 0, 0);
		}
	}
}

void Animators::FastLedAnimator::chase(uint8_t hue, uint8_t length)
{
	auto existingChase = _animations.getAnimation(AnimationType::ChaseStill);

	if (existingChase != nullptr)
	{
		if (existingChase->state >= 127 - length)
		{
			_animations.removeAnimation(AnimationType::ChaseStill);
			fade(0, 127, 127, FadeMode::FadeToBlack);
		}
		else
		{
			existingChase->state += length;
		}
	}
	else
	{
		_animations.addAnimation(Animation(AnimationType::ChaseStill, CHSV(hue, 255, 255), length, 0));
	}
}

void Animators::FastLedAnimator::chase(uint8_t hue, uint8_t speed, uint8_t style)
{
	if (speed == 0 && style <= 3)
	{
		_animations.removeAnimation((AnimationType)style);
	}
	else if (speed == 0)
	{
		_animations.resetAnimations();
	}
	else
	{
		_fadeMode = FadeMode::FadeOneByOne;
		_animations.addAnimation(Animation((AnimationType)style, CHSV(hue, 255, 255), speed, 0));
	}
}

void Animators::FastLedAnimator::bash(uint8_t hue, uint8_t intensity)
{
	if (intensity == 0)
	{
		_animations.removeAnimation(AnimationType::Bash);
	}
	else
	{
		_animations.addAnimation(Animation(AnimationType::Bash, CHSV(hue, 255, 255), intensity, 0));
	}
}

void Animators::FastLedAnimator::strobo(uint8_t hue, uint8_t fps)
{
	disableFade(0, 127);

	fill_solid(_leds, nrOfLeds, CRGB::HTMLColorCode::Black);

	if (fps == 0)
	{
		_animations.resetAnimations();
	}
	else
	{
		if (hue < 255)
		{
			_animations.insertAnimation(Animation(AnimationType::Strobo, CHSV(hue, 255, 255), 255.0 / fps, 0));
		}
		else
		{
			_animations.insertAnimation(Animation(AnimationType::Strobo, CHSV(0, 0, 255), 255.0 / fps, 0));
		}
	}
}

void Animators::FastLedAnimator::berserk()
{
	disableFade(0, 127);
	_fadeMode = FadeMode::FadeOneByOne;

	_animations.insertAnimation(Animation(AnimationType::Berserk, CHSV(0, 0, 0), 255.0, 0));
}

void Animators::FastLedAnimator::loop()
{
	uint8_t from;
	uint8_t to;

	for (auto &animation : _animations.animations)
	{
		uint8_t chaseFadeSpeed = 63;
		bool chaseReverse = false;

		switch (animation.type)
		{
		case AnimationType::Strobo:

			fill_solid(_leds, nrOfLeds, CHSV(0, 0, 0));

			if ((animation.state++) > animation.data)
			{
				animation.state = 0;

				fill_solid(_leds, nrOfLeds, animation.color);
			}

			// there is nothing else to animate besides flashing of the strobo
			return;

		case AnimationType::Berserk:

			from = random8() / 2;
			to = from + (random8() / 16) + 1;

			if (to > 127)
			{
				break;
			}

			solid(from, to, CHSV(random8() > 127 ? 0 : 158, random8() > 127 ? 0 : 255, 127 + (random8() / 2)));
			fade(0, 127, 5, FadeMode::FadeOneByOne);

			break;

		case AnimationType::ChaseDefault:
		case AnimationType::ChaseDefaultReverse:
		case AnimationType::ChaseLongTail:
		case AnimationType::ChaseLongTailReverse:

			chaseFadeSpeed = ((animation.type & AnimationType::ChaseLongTail) > 0) ? 1 : 63;
			chaseReverse = (animation.type & AnimationType::ChaseDefaultReverse) > 0;

			if (animation.state > 255 - animation.data)
			{
				_animations.removeAnimation(animation);

				// cycle to next animation type without incrementing i, since _animationsActive -= 1
				continue;
			}

			animation.state += animation.data;

			from = animation.state / 2;
			to = (animation.state / 2) + 1;
			if (to > 127)
			{
				to = 127;
			}

			if (chaseReverse)
			{
				solid(127 - to, 127 - from, animation.color);
				fade(127 - to, 127 - from, chaseFadeSpeed, _fadeMode);
			}
			else
			{
				solid(from, to, animation.color);
				fade(from, to, chaseFadeSpeed, _fadeMode);
			}

			break;

		case AnimationType::Bash:

			if (animation.state >= 250)
			{
				_animations.removeAnimation(animation);

				fade(0, 127, 16, FadeMode::FadeToBlack);

				// cycle to next animation type without incrementing i, since _animationsActive -= 1
				continue;
			}

			animation.state += 2;

			if (animation.state % 16 == 0)
			{
				from = 0;
				to = 64 + (animation.state / 4);

				solid(from, to, animation.color);
				solid(to, 127, CHSV(0, 0, 0));
			}
			else if (animation.state % 8 == 0)
			{
				from = 64 - (animation.state / 4);
				to = 127;

				solid(from, to, animation.color);
				solid(0, from, CHSV(0, 0, 0));
			}

			break;

		case AnimationType::ChaseStill:

			from = animation.state;
			to = animation.state + animation.data;

			solid(from, to, animation.color);

			break;
		}
	}

	switch (_fadeMode)
	{
	case FadeMode::FadeToBlack:
		for (int i = 0; i < nrOfLeds; i++)
		{
			if (_ledState[i].fade < 255)
			{
				if (_ledState[i].fade > 255 - 62)
				{
					_ledState[i].fade = 255;
				}
				else
				{
					_ledState[i].fade += ((_ledState[i].fade) / 4) + 1;
				}

				fadeToBlackBy(_leds + i, 1, _ledState[i].fade);
			}
		}
		break;
	case FadeMode::FadeOneByOne:
		for (int i = 0; i < nrOfLeds; i++)
		{
			if (_ledState[i].fade < 255)
			{
				if (_ledState[i].fade / 2 > random8())
				{
					if (_ledState[i].fade / 4 > random8())
					{
						_ledState[i].fade--;
						_leds[i] = CRGB::White;

						FastLED.show();
					}
					else
					{
						_ledState[i].fade = 255;

						fadeToBlackBy(_leds + i, 1, 255);
					}
				}
				else
				{
					fadeToBlackBy(_leds + i, 1, 8);
				}
			}
		}
		break;
	}
}