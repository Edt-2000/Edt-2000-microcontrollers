#pragma once

#include <FastLED.h>

struct Settings
{
  String text = "STROBOCOPS";
  CHSV colors[5] = {CHSV(0, 255, 255), CHSV(158, 255, 255), CHSV(0, 0, 0), CHSV(0, 0, 0), CHSV(0, 0, 0)};
  int speed = 5;
  int brightness = 50;
  int size = 1;
} globalSettings;

extern Settings globalSettings;
