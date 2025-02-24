#pragma once

#include "../animation.hpp"
#include "../font.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"
#include "../fader.hpp"

class LoadingAnimation : public Animation
{
private:
  uint8_t colorIndex;
  String part1 = String("LOADING");
  String part2 = String("............");
  String part3 = String("STROBOCOPS");

public:
  LoadingAnimation()
  {
  }

  const char *name()
  {
    return "loading";
  }

  void start()
  {
    colorIndex = 0;

    _isActive = true;
  }

  void stop()
  {
    _isActive = false;
  }

  void loop()
  {
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    loadText(&part1, 20);

    blinkText(&part1, 15);
    delay(200);
    blinkText(&part1, 15);

    loadText(&part2, 10);

    fadeText(&part3, 15);

    colorIndex++;
  }

  void loadText(String *text, uint8_t timeout)
  {
    for (uint16_t i = 0; i < NUM_LEDS; i += 8)
    {
      fill_solid(leds, NUM_LEDS, CRGB::Black);

      FontRenderer.displayText(text, TextAlign::center, colorIndex);

      fill_solid(leds + i, NUM_LEDS - i, CRGB::Black);

      show();

      delay(timeout);
    }
  }

  void blinkText(String *text, uint8_t timeout)
  {
    for (uint8_t i = 0; i < 2; i++)
    {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      show();

      delay(timeout);

      FontRenderer.displayText(text, TextAlign::center, colorIndex);
      show();

      delay(timeout);
    }
  }

  void fadeText(String *text, uint8_t timeout)
  {
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    for (uint8_t i = 0; i < 255; i++)
    {
      FontRenderer.displayText(text, TextAlign::center, colorIndex);
      Fader.fadeInOut(i);

      show();

      delay(timeout);
    }
  }
};