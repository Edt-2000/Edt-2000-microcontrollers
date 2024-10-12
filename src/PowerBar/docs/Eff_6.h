
/////STROBE_1/////

#ifndef EFFECT_6_H
#define EFFECT_6_H


#include "FastLED.h"

#define NUM_LEDS 640
#define DATA_PIN 5

extern CRGB leds[];

//Nodig voor STROBE + STROBE2 + STROBE3 effecten
unsigned long lastStrobe1_Time = 0;
CRGB strobe1_Color = CRGB(220, 220, 220);
int strobe1_OnTime = 1;
int strobe1_OffTime = 100;


//STROBE1 EFFECT//
void strobe1Effect(CRGB color, int delay_ms_on, int delay_ms_off) {
  for (int i = 0; i < NUM_LEDS; i++) {
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

void performStrobe1Effect() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastStrobe1_Time >= strobe1_OnTime) {
    lastStrobe1_Time = currentMillis;
    strobe1Effect(strobe1_Color, strobe1_OnTime, strobe1_OffTime);
  }
}

void performEffects_6() {
    performStrobe1Effect();
}


#endif