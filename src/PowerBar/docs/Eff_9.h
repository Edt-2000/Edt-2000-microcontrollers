
////STROBE_4///////

#ifndef EFFECT_9_H
#define EFFECT_9_H

#include <FastLED.h>

// Definieer de configuratie van de LED-matrix
const uint8_t kMatrixWidth2 = 80;
const uint8_t kMatrixHeight2 = 8;
#define NUM_LEDS (kMatrixWidth2 * kMatrixHeight2)

// Definieer de pin voor de LED's en het LED-type
#define LED_PIN 5
#define LED_TYPE WS2812B

// Maak een array voor de LED's
//CRGB leds[NUM_LEDS];
extern CRGB leds[];

// Helderheid instelling (0-255)
//uint8_t brightness = 100;

// Functie om een enkele rij in te schakelen en uit te schakelen
void switchRow(int row, CRGB color, int delayTime) {
  // Zet de huidige rij aan
  for (int col = row; col < NUM_LEDS; col += kMatrixHeight2) {
    leds[col] = color;
  }
  FastLED.show(); // Toon de veranderingen op de LED-strip
  delay(delayTime);    // Wacht delayTime milliseconden

  // Zet de huidige rij uit
  for (int col = row; col < NUM_LEDS; col += kMatrixHeight2) {
    leds[col] = CRGB::Black;
  }
  FastLED.show(); // Toon de veranderingen op de LED-strip
  delay(delayTime);    // Wacht delayTime milliseconden
}

// Functie om het effect uit te voeren
void strobe4Effect() {
  // Zet elke rij één voor één aan en vervolgens uit
  for (int row = 0; row < kMatrixHeight2; row++) {
    switchRow(row, CRGB::White, 20); // Schakel de huidige rij in en uit met een delay van 20 milliseconden
  }

  // Zet elke rij één voor één uit en vervolgens aan in omgekeerde volgorde
  for (int row = kMatrixHeight2 - 1; row >= 0; row--) {
    switchRow(row, CRGB::White, 20); // Schakel de huidige rij in en uit met een delay van 20 milliseconden
  }
}

void performEffects_9() {
   strobe4Effect();
}

#endif

/*void setup() {
  // Configureer de LED-strip
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness); // Stel de helderheid in
}

void loop() {
  runEffect(); // Voer het effect uit
}*/
