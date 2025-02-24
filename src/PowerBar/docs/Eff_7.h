
#ifndef EFFECT_7_H
#define EFFECT_7_H

#include "FastLED.h"

#define NUM_LEDS 640
#define DATA_PIN 5

extern CRGB leds[];

//Nodig voor STROBE2 effect
unsigned long lastStrobe2_Time = 0;
CRGB strobe2_Color = CRGB(220, 220, 220);
int strobe2_OnTime = 1;
int strobe2_OffTime = 100;


//STROBE2 EFFECT//
void strobe2Effect(CRGB color, int delay_ms_on, int delay_ms_off, bool firstHalf) {
  int half = NUM_LEDS / 2;

  for (int i = firstHalf * half; i < half + (firstHalf * half); i++) {
    //for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;  // Zet alle LEDs aan met de opgegeven kleur
  }
  FastLED.show();
  delay(delay_ms_on);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;  // Zet alle LEDs uit
  }
  FastLED.show();
  delay(delay_ms_off);
}

bool firstHalf = false;
void performEffects_7() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastStrobe2_Time >= strobe2_OnTime + strobe2_OffTime) {
    lastStrobe2_Time = currentMillis;
    strobe2Effect(strobe2_Color, strobe2_OnTime, strobe2_OffTime, firstHalf);
    firstHalf = !firstHalf;
  }
}

/*
void performEffects_7() {
    strobe2Effect(strobe2_Color, strobe2_OnTime, strobe2_OffTime, false);
}
*/
#endif