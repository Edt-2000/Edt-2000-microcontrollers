#pragma once

#include <FastLED.h>

struct Settings
{
  String text = "STROBOCOPS";
  CHSV colors[2] = {CHSV(0, 255, 255), CHSV(158, 255, 255)};
  int speed = 5;
  int brightness = 50;
  int size = 1;
} globalSettings;

extern Settings globalSettings;
