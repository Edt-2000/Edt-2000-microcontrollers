#pragma once

#include <FastLED.h>

struct Settings
{
  // TODO: should this be a pointer?
  String texts[10] = {"STROBOCOPS", "", "", "", ""};
  int textCount = 1;
  bool displayAllTexts = false;

  CHSV colors[3] = {CHSV(0, 255, 255), CHSV(0, 0, 0)};
  int colorCount = 1;
  int speed = 5;
  uint8_t brightness = 255;
  uint8_t font = 0;
  uint8_t variant = 0;
  int flashCount = 1;

  inline String *textAt(uint textIndex) { return &texts[textIndex % textCount]; }

  inline CHSV colorAt(uint colorIndex) { return colors[colorIndex % colorCount]; }

  inline CHSV foregroundColor() { return colors[0]; }
  inline CHSV backgroundColor() { return colors[1]; }

  inline CHSV primaryColor() { return colors[0]; }
  inline CHSV secondaryColor() { return colors[1]; }

} globalSettings;

extern Settings globalSettings;
