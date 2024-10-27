#pragma once

#include "../animation.hpp"
#include "../font.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"
#include "../fader.hpp"

enum struct TextAnimationVariants
{
  // fixed text
  left,
  center,
  right,

  // animating text
  scrollRtl,
  scrollBounce,
  scrollMerge,

  fadeOnOff,
  fadeInOut,
  fadeSawIn,
  fadeSawOut,

  glitchRotate,
  glitchPerLetter,
  glitchArtifacts
};

class TextAnimation : public Animation
{
private:
  uint8_t fade;
  int8_t progress;
  uint colorIndex;
  uint8_t letterIndex;
  bool ltr;
  bool isAnimating;

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
    auto variant = (TextAnimationVariants)globalSettings.variant;

    _isActive = true;

    colorIndex = 0;
    letterIndex = 0;
    ltr = false;
    isAnimating = variant >= TextAnimationVariants::scrollRtl;

    progress = 0;

    if (variant == TextAnimationVariants::scrollRtl)
    {
      progress = MAX_WIDTH;
    }
    else if (variant == TextAnimationVariants::scrollMerge)
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
  void stopped() override
  {
    // only clear the screen when we were animating, as we might have stopped in a weird place
    // if we're just displaying text, its must be kept
    if (isAnimating)
    {
      Animation::stopped();
    }
  }

  void loop()
  {
    auto variant = (TextAnimationVariants)globalSettings.variant;

    if (!isAnimating)
    {
      fill_solid(leds, NUM_LEDS, CRGB::Black);

      if (variant == TextAnimationVariants::left)
      {
        FontRenderer.displayText(&globalSettings.text, TextAlign::left, 0);
      }
      else if (variant == TextAnimationVariants::center)
      {
        FontRenderer.displayText(&globalSettings.text, TextAlign::center, 0);
      }
      else if (variant == TextAnimationVariants::right)
      {
        FontRenderer.displayText(&globalSettings.text, TextAlign::right, 0);
      }

      show();
      _isActive = false;
    }
    // TODO: timing is a bit off
    else if (every(1000.0 / globalSettings.speed))
    {
      fill_solid(leds, NUM_LEDS, CRGB::Black);

      // TODO: perhaps these variants should become separate animations

      if (variant == TextAnimationVariants::scrollRtl)
      {
        auto hasRendered = FontRenderer.displayText(&globalSettings.text, progress, 0, colorIndex);

        if (--progress < 0 && !hasRendered)
        {
          progress = MAX_WIDTH;
          colorIndex++;
        }
      }
      else if (variant == TextAnimationVariants::scrollBounce)
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
      else if (variant == TextAnimationVariants::scrollMerge)
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
      else if (variant >= TextAnimationVariants::fadeOnOff && variant <= TextAnimationVariants::fadeSawOut)
      {
        FontRenderer.displayText(&globalSettings.text, TextAlign::center, colorIndex);

        if (++progress == 0)
        {
          colorIndex++;
        }

        if (variant == TextAnimationVariants::fadeOnOff)
        {
          Fader.fadeOnOff(progress);
        }
        else if (variant == TextAnimationVariants::fadeInOut)
        {
          Fader.fadeInOut(progress);
        }
        else if (variant == TextAnimationVariants::fadeSawIn)
        {
          Fader.fadeSawIn(progress);
        }
        else if (variant == TextAnimationVariants::fadeSawOut)
        {
          Fader.fadeSawOut(progress);
        }
      }
      else if (variant == TextAnimationVariants::glitchRotate)
      {
        int8_t x = progress == 0   ? 0
                   : progress == 1 ? -1
                                   : 0;
        int8_t y = progress < 2 ? -1 : 0;

        FontRenderer.displayText(&globalSettings.text, TextAlign::center, x, y, progress);

        progress = (progress + 1) % 3;
      }
      else if (variant == TextAnimationVariants::glitchPerLetter)
      {
        if (progress == 0)
        {
          globalSettings.font = 0;
          letterIndex = random8(globalSettings.text.length());
        }

        FontRenderer.displayText(&globalSettings.text, TextAlign::center, 0);

        ++progress;

        uint16_t offset = (letterIndex * DEFAULT_FONT_CHAR_SIZE) + (FontRenderer.getOffset(&globalSettings.text, TextAlign::center) * 8);

        if (progress > 64)
        {
          fadeToBlackBy(leds + offset, DEFAULT_FONT_CHAR_SIZE, 191 + (random8(0, 2) * 64));
        }
        else if (progress > -90 && progress < 0)
        {
          fadeToBlackBy(leds + offset, DEFAULT_FONT_CHAR_SIZE, 127 + (random8(0, 5) * 32));
        }
      }
      else if (variant == TextAnimationVariants::glitchArtifacts)
      {
        FontRenderer.displayText(&globalSettings.text, TextAlign::center, 0);

        for (uint8_t i = 0; i < 32; i++)
        {
          leds[random16(NUM_LEDS)] = globalSettings.colorAt(1);
        }
      }

      show();
    }
  }
};