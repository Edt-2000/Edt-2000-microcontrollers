#pragma once

#include "../animation.hpp"
#include "../font.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"

class TextAnimation : public Animation
{
private:
  uint8_t offset = 0;
  bool isAnimating = false;

public:
  TextAnimation()
  {
  }

  const char *name()
  {
    return "text";
  }

  void start()
  {
    _isActive = true;

    isAnimating = globalSettings.speed > 1;
    if (isAnimating)
    {
      offset = MAX_WIDTH;
    }
    else
    {
      offset = 0;
    }
  }

  void stop()
  {
    _isActive = false;
    
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    show();
  }

  void loop()
  {
    if (!isAnimating || every(1000.0 / globalSettings.speed))
    {
      fill_solid(leds, NUM_LEDS, globalSettings.backgroundColor());

      FontRenderer.displayText(&globalSettings.text, offset, globalSettings.foregroundColor());

      show();

      if (isAnimating)
      {
        offset--;

        // check offset and stop / restart
      }
      else
      {
        _isActive = false;
      }
    }
  }
};