#pragma once

#include <FastLED.h>

struct Settings
{
  String text = "STROBOCOPS";
  CHSV colors[3] = {CHSV(0, 255, 255), CHSV(0, 0, 0)};
  int speed = 5;
  int brightness = 50;
  int size = 1;
  int variant = 0;
  int colorCount = 1;
  int textSplitPosition = 0;

  inline CHSV colorAt(uint colorIndex) { return colors[colorIndex % colorCount]; }

  inline CHSV foregroundColor() { return colors[0]; }
  inline CHSV backgroundColor() { return colors[1]; }

  inline CHSV primaryColor() { return colors[0]; }
  inline CHSV secondaryColor() { return colors[1]; }

} globalSettings;

extern Settings globalSettings;
