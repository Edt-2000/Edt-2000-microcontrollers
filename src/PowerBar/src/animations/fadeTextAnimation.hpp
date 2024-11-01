#pragma once

#include "../animation.hpp"
#include "../font.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"
#include "../fader.hpp"

enum struct FadeTextAnimationVariants
{
  fadeOnOff,
  fadeInOut,
  fadeSawIn,
  fadeSawOut
};

class FadeTextAnimation : public Animation
{
private:
  uint8_t fade;
  int8_t progress;
  uint colorIndex;

public:
  FadeTextAnimation()
  {
  }

  const char *name()
  {
    return "fadeText";
  }

  void start()
  {
    _isActive = true;

    colorIndex = 0;

    progress = 0;
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    auto variant = (FadeTextAnimationVariants)globalSettings.variant;

    fill_solid(leds, NUM_LEDS, CRGB::Black);

    FontRenderer.displayText(&globalSettings.text, TextAlign::center, colorIndex);

    auto isBelowZero = progress < 0;

    progress += max(1, globalSettings.speed / 10);

    if (isBelowZero && progress >= 0)
    {
      colorIndex++;
    }

    if (variant == FadeTextAnimationVariants::fadeOnOff)
    {
      Fader.fadeOnOff(progress);
    }
    else if (variant == FadeTextAnimationVariants::fadeInOut)
    {
      Fader.fadeInOut(progress);
    }
    else if (variant == FadeTextAnimationVariants::fadeSawIn)
    {
      Fader.fadeSawIn(progress);
    }
    else if (variant == FadeTextAnimationVariants::fadeSawOut)
    {
      Fader.fadeSawOut(progress);
    }

    show();
  }
};