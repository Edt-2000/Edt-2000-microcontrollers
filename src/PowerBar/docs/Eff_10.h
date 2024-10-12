
#ifndef EFFECT_10_H
#define EFFECT_10_H

#include <FastLED.h>

#define NUM_LEDS 640
#define DATA_PIN 5

extern CRGB leds[];


void sparkle() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (random(50) < 2) { // Pas de kans aan om de dichtheid van de sparkles te regelen
      leds[i] = CRGB::Gold;
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
  delay(100); // Voeg een vertraging van 100 milliseconden toe
}

void performEffects_10() {
   sparkle();
}


#endif