#pragma once

#include <FastLED.h>

struct Settings
{
  const char *text = "";
  CHSV colors[5] = {CHSV(0, 0, 0), CHSV(0, 0, 0), CHSV(0, 0, 0), CHSV(0, 0, 0), CHSV(0, 0, 0)};
  int speed = 1;
  int brightness = 255;
  int size = 1;
} globalSettings;

extern Settings globalSettings;
