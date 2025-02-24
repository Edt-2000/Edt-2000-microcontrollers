
#ifndef EFFECT_31_H
#define EFFECT_31_H

#include <FastLED.h>
#include "font.h"

#define LED_PIN     5   // Aanpassen naar de gewenste pin
#define NUM_LEDS    640 // Totaal aantal LED's in de matrix

extern CRGB leds[];
bool effect31Enabled();

// Kleurinstellingen
enum TextColor31 { RED_31, GREEN_31, BLUE_31 };
TextColor31 currentColor31 = RED_31;

CRGB getCurrentColor31() {
  // Retourneer de huidige kleur
  switch (currentColor31) {
    case RED_31:
      return CRGB::Red;
    case GREEN_31:
      return CRGB::Green;
    case BLUE_31:
      return CRGB::Blue;
    default:
      return CRGB::White; // Default kleur indien iets fout gaat
  }
}

void drawLetter31(const byte *letter, int startX, int startY, CRGB color) {
  for (int i = 0; i < 5; i++) {
    byte column = pgm_read_byte(letter + i); // Lees de kolomgegevens voor de huidige letter
    for (int j = 0; j < 7; j++) {
      if (column & (1 << j)) {
        // Bit is ingesteld, zet de corresponderende LED aan
        int x = startX + i;
        int y = startY + (6 - j);

        if (x >= 0 && x < 80 && y >= 0 && y < 8) {
          int ledIndex = x * 8 + y;
          leds[ledIndex] = color; // Gebruik de doorgegeven kleur
        }
      }
    }
  }
}

void displayText31(const char *text, int length, int startX, int startY, int line, CRGB color) {
  int letterSpacing = 1; // Ruimte tussen letters

  // Loop door de tekst en weergeef elke letter
  for (int i = 0; i < length; i++) {
    char currentChar = text[i];
    if (currentChar >= ' ' && currentChar <= '~') {
      int letterIndex = currentChar - ' ';
      for (int col = 0; col < 5; col++) {
        byte column = pgm_read_byte(&font[letterIndex][col]);
        for (int row = 0; row < 7; row++) {
          int x = startX + i * 6 + col;
          int y = startY + (6 - row);

          if (x >= 0 && x < 80 && y >= 0 && y < 8) {
            int ledIndex = x * 8 + y;
            if (line >= x) {
              if (column & (1 << row)) {
                leds[ledIndex] = color; // Gebruik de doorgegeven kleur
              } else {
                leds[ledIndex] = CRGB::Black; // Achtergrondkleur
              }
            } else {
              leds[ledIndex] = CRGB::Black; // Achtergrondkleur
            }
          }
        }
      }
    }
  }
}

void changeColor31() {
  // Verander kleur na het volledig uit het zicht zijn
  switch (currentColor31) {
    case RED_31:
      currentColor31 = GREEN_31;
      break;
    case GREEN_31:
      currentColor31 = BLUE_31;
      break;
    case BLUE_31:
      currentColor31 = RED_31;
      break;
  }
}

void loadText31(const char *text, int delayMs) {
  int textLength = strlen(text);
  int textWidth = textLength * 6; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters

  int startX = (80 - textWidth) / 2; // Bereken de startpositie X zodat de tekst in het midden staat
  int startY = 0; // Y-positie voor de tekst

  // Laat de tekst rij per rij verschijnen
  for (int line = 0; line <= 80; line++) {
    if (!effect31Enabled()) {
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
      FastLED.show();
      return; // Stop de animatie als de vlag is uitgeschakeld
    }
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LED's
    displayText31(text, textLength, startX, startY, line, getCurrentColor31()); // Toon de eerste i letters van de tekst
    FastLED.show();
    delay(delayMs);
  }
}

void blinkText31(const char *text, int delayMs) {
  int textLength = strlen(text);
  int textWidth = textLength * 6; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters

  int startX = (80 - textWidth) / 2; // Bereken de startpositie X zodat de tekst in het midden staat
  int startY = 0; // Y-positie voor de tekst

  // Knipper de volledige tekst 2 keer
  for (int j = 0; j < 2; j++) {
    if (!effect31Enabled()) {
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
      FastLED.show();
      return; // Stop de animatie als de vlag is uitgeschakeld
    }
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LED's
    FastLED.show();
    delay(delayMs);

    displayText31(text, textLength, startX, startY, 80, getCurrentColor31()); // Toon de volledige tekst
    FastLED.show();
    delay(delayMs);
  }
}

void fadeText31(const char *text, int fadeSteps, int delayMs) {
  int textLength = strlen(text);
  int textWidth = textLength * 6; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters

  int startX = (80 - textWidth) / 2; // Bereken de startpositie X zodat de tekst in het midden staat
  int startY = 0; // Y-positie voor de tekst

  // Fade in
  for (int step = 0; step <= fadeSteps; step++) {
    if (!effect31Enabled()) {
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
      FastLED.show();
      return; // Stop de animatie als de vlag is uitgeschakeld
    }
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LED's
    CRGB color = getCurrentColor31();
    color.fadeLightBy(255 - (255 * step / fadeSteps)); // Bereken de kleur voor de huidige fade stap
    displayText31(text, textLength, startX, startY, 80, color); // Toon de volledige tekst met de huidige kleur
    FastLED.show();
    delay(delayMs);
  }

  // Fade out
  for (int step = fadeSteps; step >= 0; step--) {
    if (!effect31Enabled()) {
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
      FastLED.show();
      return; // Stop de animatie als de vlag is uitgeschakeld
    }
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LED's
    CRGB color = getCurrentColor31();
    color.fadeLightBy(255 - (255 * step / fadeSteps)); // Bereken de kleur voor de huidige fade stap
    displayText31(text, textLength, startX, startY, 80, color); // Toon de volledige tekst met de huidige kleur
    FastLED.show();
    delay(delayMs);
  }
}

void performEffects_31() {
  if (effect31Enabled()) {
    // Toon "LOADING" met een delay van 15 ms
    loadText31("LOADING", 20);

    // Knipper "LOADING" 2 keer met een delay van 500 ms
    blinkText31("LOADING", 15);
    delay(200);
    blinkText31("LOADING", 15);

    loadText31(".............", 10);
    // Toon "STROBOCOPS" met fade in en fade out effect
    fadeText31("STROBOCOPS", 50, 15);

    // Verander de kleur na elke cyclus
    changeColor31();
  }
}

#endif
