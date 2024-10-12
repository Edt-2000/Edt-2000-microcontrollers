

#ifndef EFFECT_15_H
#define EFFECT_15_H

#include <FastLED.h>
#include "font.h"

#define LED_PIN     5   // Aanpassen naar de gewenste pin
#define NUM_LEDS    640 // Totaal aantal LED's in de matrix

extern CRGB leds[];

bool effect15Enabled();

void drawLetter(const byte *letter, int startX, int startY, CRGB color) {
  for (int i = 0; i < 5; i++) {
    byte column = pgm_read_byte(letter + i); // Lees de kolomgegevens voor de huidige letter
    for (int j = 0; j < 7; j++) {
      if (column & (1 << j)) {
        // Bit is ingesteld, zet de corresponderende LED aan
        int x = startX + i;
        int y = startY + (6 - j);

        if (x >= 0 && x < 80 && y >= 0 && y < 8) {
          int ledIndex = x * 8 + y;
          leds[ledIndex] = color;
        }
      }
    }
  }
}

void displayText(const char *text, int startX, CRGB color) {
  int startY = 0;
  int letterSpacing = 1; // Aantal pixels tussen letters

  int currentIndex = 0;

  // Loop door de tekst en weergeef elke letter
  while (text[currentIndex] != '\0') {
    char currentChar = text[currentIndex];
    if (currentChar >= ' ' && currentChar <= '~') {
      int letterIndex = currentChar - ' ';
      drawLetter(font[letterIndex], startX, startY, color);
      startX += 5 + letterSpacing; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters
    }
    currentIndex++;
  }
}

void scrollText(const char *text, CRGB color, int delayMs) {
  int textLength = strlen(text);
  int textWidth = textLength * 6; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters

  for (int offset = -80; offset < textWidth; offset++) {
    if (!effect15Enabled()) {
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
      FastLED.show();
      return; // Stop de animatie als de vlag is uitgeschakeld
    }
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LED's
    displayText(text, -offset, color); // Verplaats de tekst naar links met de opgegeven kleur
    FastLED.show();
    delay(delayMs);
  }
}

void WebsiteEffect() {
  CRGB colors[] = {CRGB::Green, CRGB::Red, CRGB::Blue}; // Array met kleuren
  int numColors = sizeof(colors) / sizeof(colors[0]);

  for (int i = 0; i < numColors; i++) {
    if (!effect15Enabled()) {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      return;
    }
    scrollText("WWW.STROBOCOPS.NL", colors[i], 7);
  }
}

void performEffects_15() {
    WebsiteEffect();
}


#endif
