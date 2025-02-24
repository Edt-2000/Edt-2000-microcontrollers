#pragma once

#include "../animation.hpp"
#include "../settings.hpp"

#include "../leds.hpp"

enum struct StroboAnimationVariants
{
  stroboFull,
  stroboHalf,
  stroboScanBlock,
  stroboScanLine,
  stroboText
};

class StroboAnimation : public Animation
{
private:
  uint8_t flashCount;
  uint colorIndex;

public:
  StroboAnimation()
  {
  }

  const char *name()
  {
    return "strobo";
  }

  void start()
  {
    flashCount = 0;
    colorIndex = 0;
    _isActive = true;
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    do
    {
      auto variant = (StroboAnimationVariants)globalSettings.variant;

      auto color = globalSettings.colorAt(colorIndex);

      if (variant == StroboAnimationVariants::stroboFull)
      {
        output(color, 0, NUM_LEDS);
      }
      else if (variant == StroboAnimationVariants::stroboHalf)
      {
        output(color, (colorIndex % 2) * (NUM_LEDS / 2), NUM_LEDS / 2);
      }
      else if (variant == StroboAnimationVariants::stroboScanBlock)
      {
        uint8_t pos = colorIndex % 18;
        if (pos > 9) {
          pos = 18 - pos;
        }
        output(color, (pos) * (NUM_LEDS / 10), NUM_LEDS / 10);
      }
      else if (variant == StroboAnimationVariants::stroboScanLine)
      {
        uint8_t height = colorIndex % 14;
        if (height > 7) {
          height = 14 - height;
        }
        if (isRainbow(color))
        {
          for (uint8_t i = 0; i < MAX_WIDTH; i++)
          {
            leds[(i * 8) + height] = CHSV(i * 3.2, 255, 255);
          }
        }
        else
        {
          for (uint8_t i = 0; i < MAX_WIDTH; i++)
          {
            leds[(i * 8) + height] = color;
          }
        }
      }
      else if (variant == StroboAnimationVariants::stroboText)
      {
        FontRenderer.displayText(globalSettings.textAt(colorIndex), TextAlign::center, colorIndex);
      }

      show();

      delay(10);

      fill_solid(leds, NUM_LEDS, CRGB::Black);

      show();

      if (++flashCount >= globalSettings.flashCount)
      {
        flashCount = 0;
        colorIndex++;
      }

      delay(255 - globalSettings.speed);
      delay(255 - globalSettings.speed);
      delay(255 - globalSettings.speed);

    } while (_isActive);
  }

  void output(CHSV &color, int offset, int numLeds)
  {
    if (isRainbow(color))
    {
      for (uint16_t i = offset; i < offset + numLeds; i++)
      {
        leds[i] = CHSV((255 * i) / NUM_LEDS, 255, 255);
      }
    }
    else
    {
      fill_solid(leds + offset, numLeds, color);
    }
  }
};
