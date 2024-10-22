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
  scroll,
  bounce,      // TODO
  mergeScroll, // TODO

  fadeOnOff,
  fadeInOut,
  fadeSawIn,
  fadeSawOut,

  glitchRotate,
  glitchPerLetter,
  glitchArtifacts,

  strobo
};

class TextAnimation : public Animation
{
private:
  uint8_t fade;
  int8_t progress;
  uint colorIndex;
  uint8_t letterIndex;
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
    isAnimating = variant >= TextAnimationVariants::scroll;

    progress = 0;

    if (variant == TextAnimationVariants::scroll)
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

      if (variant == TextAnimationVariants::scroll)
      {
        auto hasRendered = FontRenderer.displayText(&globalSettings.text, progress, 0, colorIndex);

        if (--progress < 0 && !hasRendered)
        {
          progress = MAX_WIDTH;
          colorIndex++;
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
          letterIndex = random8(globalSettings.text.length());
        }

        FontRenderer.displayText(&globalSettings.text, TextAlign::center, 0);

        ++progress;

        uint8_t offset = (letterIndex * CHAR_SIZE) + (FontRenderer.getOffset(&globalSettings.text, TextAlign::center) * 8);

        if (progress > 90)
        {
          fadeToBlackBy(leds + offset, CHAR_SIZE, random8(127, 255));
        }
        else if (progress > -90 && progress < 0)
        {
          fadeToBlackBy(leds + offset, CHAR_SIZE, random8(127, 255));
        }
      }

      show();
    }
  }
};