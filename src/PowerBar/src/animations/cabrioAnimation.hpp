#pragma once

#include "../animation.hpp"
#include "../font.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"
#include "../fader.hpp"

enum struct CabrioAnimationVariants
{
  variant0,
  variant1
};

class CabrioAnimation : public Animation
{
private:
  String part1 = String("Ik heb een");
  String part2 = String("CABRIO");
  String part3 = String("CABRIOLETTA");

public:
  CabrioAnimation()
  {
  }

  const char *name()
  {
    return "cabrio";
  }

  void start()
  {
    _isActive = true;
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    auto variant = (CabrioAnimationVariants)globalSettings.variant;

    if (variant == CabrioAnimationVariants::variant0)
    {
      variant0loop();
    }
    else
    {
      variant1loop();
    }
  }

  void variant0loop()
  {
    uint offTime = globalSettings.speed;

    for (uint8_t r = 0; r < 3; r++)
    {
      for (uint8_t i = 1; i <= part1.length(); i++)
      {
        auto partial = part1.substring(0, i);

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FontRenderer.displayText(&partial, TextAlign::center, 0);

        show();
        delay(offTime);
      }

      fill_solid(leds, NUM_LEDS, CRGB::Black);

      if (r < 2)
      {
        FontRenderer.displayText(&part2, TextAlign::center, 1);
      }
      else
      {
        FontRenderer.displayText(&part3, TextAlign::center, 2);
      }

      show();
      delay(offTime * 3);
    }

    delay(offTime);
  }

  void variant1loop()
  {
    uint offTime = globalSettings.speed;

    for (uint8_t i = 1; i <= part2.length(); i++)
    {
      auto partial = part2.substring(0, i);

      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FontRenderer.displayText(&partial, TextAlign::center, 0);

      show();
      delay(offTime);
    }

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FontRenderer.displayText(&part3, TextAlign::center, 1);

    show();
    delay(offTime);
  }
};