#pragma once

#include "../animation.hpp"
#include "../font.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"
#include "../fader.hpp"

class HarderAnimation : public Animation
{
private:
  uint8_t colorIndex;
  String part1 = String("HARDER dan jij...");

public:
  HarderAnimation()
  {
  }

  const char *name()
  {
    return "harder";
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
    do
    {
      fill_solid(leds, NUM_LEDS, CRGB::Black);

      

      show();
    } while (true);
  }
};