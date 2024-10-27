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
    ltr = false;

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

    // TODO: fix timing
    if (every(1000.0 / globalSettings.speed))
    {
      fill_solid(leds, NUM_LEDS, CRGB::Black);

      if (variant == ScrollTextAnimationVariants::scrollRtl)
      {
        auto hasRendered = FontRenderer.displayText(&globalSettings.text, progress, 0, colorIndex);

        if (--progress < 0 && !hasRendered)
        {
          progress = MAX_WIDTH;
          colorIndex++;
        }
      }
      else if (variant == ScrollTextAnimationVariants::scrollBounce)
      {
        auto limit = FontRenderer.getOffset(&globalSettings.text, TextAlign::right);

        progress += ltr ? 1 : -1;

        if (progress <= 0)
        {
          ltr = true;
          colorIndex++;
        }
        else if (progress >= limit)
        {
          ltr = false;
          colorIndex++;
        }

        FontRenderer.displayText(&globalSettings.text, progress, 0, colorIndex);
      }
      else if (variant == ScrollTextAnimationVariants::scrollMerge)
      {
        globalSettings.font = 0;

        if (progress-- >= 0)
        {
          int8_t centerPos = FontRenderer.getOffset(&globalSettings.text, TextAlign::center);

          int8_t posLeft = centerPos - progress;
          int8_t posRight = centerPos + progress + 1 + (globalSettings.textSplitPosition * DEFAULT_FONT_GLYPH_SIZE_WITH_KERNING);

          FontRenderer.displayText(&globalSettings.text, 0, globalSettings.textSplitPosition, posLeft, 0, colorIndex);
          FontRenderer.displayText(&globalSettings.text, globalSettings.textSplitPosition, globalSettings.text.length() - globalSettings.textSplitPosition, posRight, 0, colorIndex);
        }
        else
        {
          if (progress > -64)
          {
            fill_solid(leds, NUM_LEDS, CRGB::Gray);
            fadeToBlackBy(leds, NUM_LEDS, 192 - progress);
          }

          FontRenderer.displayText(&globalSettings.text, TextAlign::center, colorIndex);

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