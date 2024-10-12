
#ifndef EFFECT_8_H
#define EFFECT_8_H


#include "FastLED.h"

#define NUM_LEDS 640
#define DATA_PIN 5
#define MATRIX_SIZE 64   // LEDs per matrix
#define NUM_MATRICES 10  // Aantal matrices

extern CRGB leds[];


//Nodig voor STROBE3 effect
int direction = 1;      // 1 voor links naar rechts, -1 voor rechts naar links
int currentMatrix = 0;  // Houd de huidige matrix bij



//STROBE3 EFFECT//
void strobe3Effect(CRGB color, int delay_ms_on, int delay_ms_off, int startLED, int endLED) {
  for (int i = startLED; i < endLED; i++) {
    leds[i] = color;
  }
  FastLED.show();
  delay(delay_ms_on);

  for (int i = startLED; i < endLED; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(delay_ms_off);

  // Update de huidige matrix op basis van de richting
  currentMatrix += direction;

  // Als we de uitersten bereiken, verander de richting
  if (currentMatrix == 0 || currentMatrix == NUM_MATRICES - 1) {
    direction *= -1;
  }

  // Voorkom dat currentMatrix buiten bereik raakt
  currentMatrix = constrain(currentMatrix, 0, NUM_MATRICES - 1);
}

void performEffects_8() {
    strobe3Effect(CRGB::White, 1, 100, currentMatrix * MATRIX_SIZE, (currentMatrix + 1) * MATRIX_SIZE);
}


#endif