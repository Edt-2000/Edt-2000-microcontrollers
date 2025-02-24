#pragma once

#include "core.h"
#include "leds.h"

extern volatile bool doFastLed;

class StroboAnimation : public BaseAnimation
{
private:
    uint8_t _intensity;
    uint8_t _progress;
    bool _output;
    CRGB _color;

    BaseLeds *_baseLeds;

public:
    StroboAnimation(StroboCommand command, BaseLeds *baseLeds) : _intensity(command.intensity), _color(command.getColor()), _baseLeds(baseLeds)
    {
        fullControl = true;

        _progress = _intensity > 30 ? random8(_intensity) : 0;
        _output = false;
    }

    bool virtual animate(bool progressAnimation)
    {
        if (_progress == 0 && _output && doFastLed)
        {
            // waiting for output
        }
        else if (_progress == 0 && _output && !doFastLed)
        {
            _output = false;

            fill_solid(_baseLeds->leds, _baseLeds->nrOfLeds, CRGB::Black);

            return true;
        }
        else if (!_output && progressAnimation)
        {
            if ((_progress++ > _intensity))
            {
                _output = true;

                fill_solid(_baseLeds->leds, _baseLeds->nrOfLeds, _color);
                _progress = 0;

                return true;
            }
        }

        return false;
    }
};
