#pragma once

#include "../animation.hpp"
#include "../font.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"
#include "../fader.hpp"

enum struct GlitchTextAnimationVariants
{
  glitchRotate,
  glitchPerLetter,
  glitchArtifacts
};

class GlitchTextAnimation : public Animation
{
private:
  uint8_t fade;
  int8_t progress;
  uint colorIndex;
  uint8_t letterIndex;
  bool ltr;

public:
  GlitchTextAnimation()
  {
  }

  const char *name()
  {
    return "glitchText";
  }

  void start()
  {
    auto variant = (GlitchTextAnimationVariants)globalSettings.variant;

    _isActive = true;

    colorIndex = 0;
    letterIndex = 0;
    ltr = false;

    progress = 0;
  }

  void stop()
  {
    _isActive = false;

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    show();
  }

  void loop()
  {
    auto variant = (GlitchTextAnimationVariants)globalSettings.variant;

    if (every(1000 / globalSettings.speed))
    {
      fill_solid(leds, NUM_LEDS, CRGB::Black);

      if (variant == GlitchTextAnimationVariants::glitchRotate)
      {
        int8_t x = progress == 0   ? 0
                   : progress == 1 ? -1
                                   : 0;
        int8_t y = progress < 2 ? -1 : 0;

        FontRenderer.displayText(&globalSettings.text, TextAlign::center, x, y, progress);

        progress = (progress + 1) % 3;
      }
      else if (variant == GlitchTextAnimationVariants::glitchPerLetter)
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
      else if (variant == GlitchTextAnimationVariants::glitchArtifacts)
      {
        FontRenderer.displayText(&globalSettings.text, TextAlign::center, 0);

        for (uint8_t i = 0; i < 32; i++)
        {
          leds[random16(NUM_LEDS)] = globalSettings.colorAt(1 + (i % 2));
        }
      }

      show();
    }
  }
};