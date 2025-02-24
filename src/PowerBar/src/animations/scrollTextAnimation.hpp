#pragma once

#include "../animation.hpp"
#include "../font.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"
#include "../fader.hpp"

enum struct ScrollTextAnimationVariants
{
  scrollRtl,
  scrollBounce,
  scrollMerge
};

class ScrollTextAnimation : public Animation
{
private:
  int8_t progress;
  uint colorIndex;
  bool ltr;

public:
  ScrollTextAnimation()
  {
  }

  const char *name()
  {
    return "scrollText";
  }

  void start()
  {
    auto variant = (ScrollTextAnimationVariants)globalSettings.variant;

    _isActive = true;

    colorIndex = 0;
    ltr = true;

    progress = 0;

    if (variant == ScrollTextAnimationVariants::scrollRtl)
    {
      progress = MAX_WIDTH;
    }
    else if (variant == ScrollTextAnimationVariants::scrollMerge)
    {
      progress = MAX_WIDTH;
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
    auto variant = (ScrollTextAnimationVariants)globalSettings.variant;

    if (every(100 / globalSettings.speed))
    {
      fill_solid(leds, NUM_LEDS, CRGB::Black);

      if (variant == ScrollTextAnimationVariants::scrollRtl)
      {
        auto hasRendered = FontRenderer.displayText(progress, 0, colorIndex);

        if (--progress < 0 && !hasRendered)
        {
          progress = MAX_WIDTH;
          colorIndex++;
        }
      }
      else if (variant == ScrollTextAnimationVariants::scrollBounce)
      {
        auto limit = FontRenderer.getOffset(TextAlign::right, colorIndex);

        progress += ltr ? 1 : -1;

        if (!ltr && progress <= 0)
        {
          ltr = true;
          colorIndex++;
        }
        else if (ltr && progress >= limit)
        {
          ltr = false;
          colorIndex++;
        }

        FontRenderer.displayText(progress, 0, colorIndex);
      }
      else if (variant == ScrollTextAnimationVariants::scrollMerge)
      {
        globalSettings.font = 0;

        if (progress-- >= 0)
        {
          auto leftText = globalSettings.textAt(0);
          auto rightText = globalSettings.textAt(1);

          auto leftTextLength = leftText->length();
          auto rightTextLength = rightText->length();

          auto totalLength = leftTextLength + rightTextLength;

          auto centerPos = FontRenderer.getOffset(totalLength, TextAlign::center) + (leftTextLength * DEFAULT_FONT_GLYPH_SIZE_WITH_KERNING);

          int8_t posLeft = centerPos - progress - (leftTextLength * DEFAULT_FONT_GLYPH_SIZE_WITH_KERNING);
          int8_t posRight = centerPos + progress;

          FontRenderer.displayText(leftText, posLeft, 0, 0);
          FontRenderer.displayText(rightText, posRight, 0, 1);
        }
        else
        {
          if (progress > -64 && globalSettings.colorAt(2).v > 0)
          {
            fill_solid(leds, NUM_LEDS, CHSV(globalSettings.colorAt(2).h, globalSettings.colorAt(2).s, 4 * (128 - (progress * -1))));
          }

          FontRenderer.displayText(globalSettings.textAt(2), TextAlign::center, colorIndex);

          if (--progress == -128)
          {
            progress = MAX_WIDTH;
          }
        }
      }
      
      show();
    }
  }
};