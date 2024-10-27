#pragma once

#include "../animation.hpp"
#include "../font.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"
#include "../fader.hpp"

enum struct StaticTextAnimationVariants
{
  left,
  center,
  right
};

class StaticTextAnimation : public Animation
{
public:
  StaticTextAnimation()
  {
  }

  const char *name()
  {
    return "staticText";
  }

  void start()
  {
    _isActive = true;
  }

  void stop()
  {
    _isActive = false;
  }

  void stopped() override
  {
    // do not set leds to black after being done
  }

  void loop()
  {
    auto variant = (StaticTextAnimationVariants)globalSettings.variant;

    fill_solid(leds, NUM_LEDS, CRGB::Black);

    if (variant == StaticTextAnimationVariants::left)
    {
      FontRenderer.displayText(&globalSettings.text, TextAlign::left, 0);
    }
    else if (variant == StaticTextAnimationVariants::center)
    {
      FontRenderer.displayText(&globalSettings.text, TextAlign::center, 0);
    }
    else if (variant == StaticTextAnimationVariants::right)
    {
      FontRenderer.displayText(&globalSettings.text, TextAlign::right, 0);
    }

    show();
    _isActive = false;
  }
};