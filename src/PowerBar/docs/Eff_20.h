

#ifndef EFFECT_20_H
#define EFFECT_20_H

#include <FastLED.h>
#include "font.h"

#define LED_PIN     5   // Aanpassen naar de gewenste pin
#define NUM_LEDS    640 // Totaal aantal LED's in de matrix

extern CRGB leds[];
bool effect20Enabled();

// Kleurinstellingen
enum TextColor20 { RED, GREEN, BLUE };
TextColor20 currentColor20 = RED;

CRGB getCurrentColor20() {
  // Retourneer de huidige kleur
  switch (currentColor20) {
    case RED:
      return CRGB::Red;
    case GREEN:
      return CRGB::Green;
    case BLUE:
      return CRGB::Blue;
    default:
      return CRGB::White; // Default kleur indien iets fout gaat
  }
}

void drawLetter20(const byte *letter, int startX, int startY) {
  for (int i = 0; i < 5; i++) {
    byte column = pgm_read_byte(letter + i); // Lees de kolomgegevens voor de huidige letter
    for (int j = 0; j < 7; j++) {
      if (column & (1 << j)) {
        // Bit is ingesteld, zet de corresponderende LED aan
        int x = startX + i;
        int y = startY + (6 - j);

        if (x >= 0 && x < 80 && y >= 0 && y < 8) {
          int ledIndex = x * 8 + y;
          leds[ledIndex] = getCurrentColor20(); // Gebruik de huidige kleur
        }
      }
    }
  }
}

void displayText20(const char *text, int startX) {
  int startY = 0;
  int letterSpacing = 1; // Ruimte tussen letters

  int currentIndex = 0;

  // Loop door de tekst en weergeef elke letter
  while (text[currentIndex] != '\0') {
    char currentChar = text[currentIndex];
    if (currentChar >= ' ' && currentChar <= '~') {
      int letterIndex = currentChar - ' ';
      drawLetter20(font[letterIndex], startX + currentIndex * 6, startY); // Verschuif de letterpositie
    }
    currentIndex++;
  }
}

void changeColor20() {
  // Verander kleur na het volledig uit het zicht zijn
  switch (currentColor20) {
    case RED:
      currentColor20 = GREEN;
      break;
    case GREEN:
      currentColor20 = BLUE;
      break;
    case BLUE:
      currentColor20 = RED;
      break;
  }
}

void scrollText20(const char *text, int delayMs) {
  int textLength = strlen(text);
  int textWidth = textLength * 6; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters
  int displayWidth = 80; // Breedte van de matrix

  while (effect20Enabled()) {
    // Scroll naar links
    for (int offset = displayWidth; offset > -textWidth; offset--) {
      if (!effect20Enabled()) {
        fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
        FastLED.show();
        return; // Stop de animatie als de vlag is uitgeschakeld
      }
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LED's
      displayText20(text, offset); // Verplaats de tekst naar links
      FastLED.show();
      delay(delayMs);
    }

    // Kleurverandering na het volledig uit het zicht zijn aan de rechterkant
    changeColor20();

    // Scroll naar rechts
    for (int offset = -textWidth; offset < displayWidth; offset++) {
      if (!effect20Enabled()) {
        fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
        FastLED.show();
        return; // Stop de animatie als de vlag is uitgeschakeld
      }
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LED's
      displayText20(text, offset); // Verplaats de tekst naar rechts
      FastLED.show();
      delay(delayMs);
    }

    // Kleurverandering na het volledig uit het zicht zijn aan de linkerzijde
    changeColor20();
  }

  fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
  FastLED.show();
}

void performEffects_20() {
  if (effect20Enabled()) {
    scrollText20("STROBOCOPS", 3); // Scroll "STROBOCOPS" met een vertraging van 5 ms
  }
}


#endif
