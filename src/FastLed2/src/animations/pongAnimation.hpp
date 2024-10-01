#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

class PongAnimation : public Animation
{
private:
    const uint8_t rightUp = 1;
    const uint8_t rightDown = 2;
    const uint8_t leftUp = 3;
    const uint8_t leftDown = 4;
    const uint8_t batLength = 5;

    uint8_t _step;

    // 0-7
    uint8_t _position;

    uint8_t _direction;

    // 0-59
    uint8_t _verticalPosition;
    uint8_t _verticalSpeed;

    uint8_t _leftBatVerticalPosition;
    uint8_t _rightBatVerticalPosition;

public:
    PongAnimation()
    {
    }

    const char *name()
    {
        return "pong";
    }

    bool mustRunSolo()
    {
        return true;
    }

    void start()
    {
        _isActive = true;

        _step = 0;
        _position = 0;
        _direction = 0;
        _verticalPosition = 20;
        _verticalSpeed = 5;
        _leftBatVerticalPosition = 18;
        _rightBatVerticalPosition = 40;
    }

    void stop()
    {
        _isActive = false;
    }

    void loop()
    {
        if (Time.t1ms)
        {
            // 3 - 45
            auto speed = 3 + globalSettings.speed / 6;

            _step = qadd8(_step, speed);
            if (_step != 255)
            {
                return;
            }
            _step = 0;

            auto isUp = _direction == rightUp || _direction == leftUp;
            auto isDown = !isUp;
            auto isLeft = _direction >= leftUp;
            auto isRight = !isLeft;

            if (_position == 0 && isLeft)
            {
                if (globalSettings.speed == 255) {
                    fill_solid(leds0 + _leftBatVerticalPosition, batLength, CRGB::Red);
                    Fader.scheduleFade(0, _leftBatVerticalPosition, batLength, 4, FadeMode::sparkle);
        
                    fill_solid(leds7 + _rightBatVerticalPosition, batLength, CRGB::Lime);
                    Fader.scheduleFade(7, _rightBatVerticalPosition, batLength, 1, FadeMode::fadeAll);

                    _isActive = false;

                    return;
                }

                _verticalSpeed = random8(4, 6);
                if (isUp)
                {
                    _direction = rightUp;
                }
                else
                {
                    _direction = rightDown;
                }
                isLeft = false;
                isRight = true;
            }
            else if (_position == 7 && isRight)
            {
                if (globalSettings.speed == 255) {
                    fill_solid(leds0 + _leftBatVerticalPosition, batLength, CRGB::Lime);
                    Fader.scheduleFade(0, _leftBatVerticalPosition, batLength, 1, FadeMode::fadeAll);
        
                    fill_solid(leds7 + _rightBatVerticalPosition, batLength, CRGB::Red);
                    Fader.scheduleFade(7, _rightBatVerticalPosition, batLength, 4, FadeMode::sparkle);

                    _isActive = false;

                    return;
                }

                _verticalSpeed = random8(4, 6);
                if (isUp)
                {
                    _direction = leftUp;
                }
                else
                {
                    _direction = leftDown;
                }
                isLeft = true;
                isRight = false;
            }

            if (isLeft)
            {
                _position--;
            }
            else
            {
                _position++;
            }

            if (isUp)
            {
                if (_verticalPosition < _verticalSpeed)
                {
                    _verticalPosition = _verticalSpeed - _verticalPosition;
                    _direction = isLeft ? leftDown : rightDown;

                    isUp = false;
                    isDown = true;
                }
                else
                {
                    _verticalPosition -= _verticalSpeed;
                }
            }
            else
            {
                if (_verticalPosition + _verticalSpeed > 58)
                {
                    _verticalPosition = _verticalPosition - ((_verticalPosition + _verticalSpeed) - 58);
                    _direction = isLeft ? leftUp : rightUp;

                    isUp = true;
                    isDown = false;
                }
                else
                {
                    _verticalPosition += _verticalSpeed;
                }
            }

            if (isLeft)
            {
                uint8_t easing = 1 + _position;

                auto batBelow = _verticalPosition < _leftBatVerticalPosition;

                uint8_t diff = (batBelow
                    ? _leftBatVerticalPosition - _verticalPosition
                    : _verticalPosition - _leftBatVerticalPosition) / easing;

                if (batBelow)
                {
                    _leftBatVerticalPosition = qsub8(_leftBatVerticalPosition, diff);
                }
                else
                {
                    _leftBatVerticalPosition += diff;
                }

                _leftBatVerticalPosition = qsub8(_leftBatVerticalPosition, batLength / 2);
                if (_leftBatVerticalPosition + batLength > 58)
                {
                    _leftBatVerticalPosition = 58 - batLength;
                }
            }

            if (isRight)
            {
                uint8_t easing = 8 - _position;

                auto batBelow = _verticalPosition < _rightBatVerticalPosition;

                uint8_t diff = (batBelow
                    ? _rightBatVerticalPosition - _verticalPosition
                    : _verticalPosition - _rightBatVerticalPosition) / easing;

                if (batBelow)
                {
                    _rightBatVerticalPosition = qsub8(_rightBatVerticalPosition, diff);
                }
                else
                {
                    _rightBatVerticalPosition += diff;
                }

                _rightBatVerticalPosition = qsub8(_rightBatVerticalPosition, batLength / 2);
                if (_rightBatVerticalPosition + batLength > 58)
                {
                    _rightBatVerticalPosition = 58 - batLength;
                }
            }

            fill_solid(leds0 + _leftBatVerticalPosition, batLength, CRGB::White);
            Fader.scheduleFade(0, _leftBatVerticalPosition, batLength, 30, FadeMode::fadeAll);

            auto color = HeatColor(130 + speed);

            applyToLeds(
                1 << _position, 
                [=, &color](CRGB *leds, uint8_t index)
                {
                    leds[_verticalPosition] = color;
                    Fader.scheduleFade(index, _verticalPosition, 1, 20, FadeMode::fadeAll); 
                });

            fill_solid(leds7 + _rightBatVerticalPosition, batLength, CRGB::White);
            Fader.scheduleFade(7, _rightBatVerticalPosition, batLength, 30, FadeMode::fadeAll);
        }
    }
};
