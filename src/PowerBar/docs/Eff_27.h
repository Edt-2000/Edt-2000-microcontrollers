

#ifndef EFFECT_27_H
#define EFFECT_27_H

#include <FastLED.h>
#include "font.h"

#define NUM_LEDS 640 // 8x80 LED matrix
#define DATA_PIN 5    // Verander dit naar het juiste datapin-nummer
#define LED_TYPE WS2812B // Verander dit naar het juiste LED-type
#define OffTime27 300

extern CRGB leds[];

bool effect27Enabled();

void drawLetter27(const byte *letter, int startX, int startY) {
  for (int i = 0; i < 5; i++) {
    byte column = pgm_read_byte(letter + i); // Lees de kolomgegevens voor de huidige letter
    for (int j = 0; j < 7; j++) {
      if (column & (1 << j)) {
        // Bit is ingesteld, zet de corresponderende LED aan
        int ledIndex = (startX + i) * 8 + (6 - j) + startY * 80; // Geen wijziging in startY
        leds[ledIndex] = CRGB::DarkOrange ;
      }
    }
  }
}

void displayText27(const char *text) {
  int textLength = strlen(text);
  int letterWidth = 6; // 5 pixels breed plus 1 pixel spatie
  int totalTextWidth = textLength * letterWidth;

  // Bereken startX om de tekst te centreren
  int startX = (80 - totalTextWidth) / 2;
  int startY = 0; // Aangezien we slechts één regel hebben

  int letterSpacing = 0;
  int currentIndex = 0;

  // Loop door de tekst en weergeef elke letter
  while (text[currentIndex] != '\0') {
    if (!effect27Enabled()) return; // Controleer de voorwaarde en stop indien nodig
    char currentChar = text[currentIndex];
    if (currentChar >= ' ' && currentChar <= '~') {
      int letterIndex = currentChar - ' ';
      drawLetter27(font[letterIndex], startX, startY);
      startX += 6 + letterSpacing; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters
    }
    currentIndex++;
  }

  // Toon de LED's
  FastLED.show();
}

void clearLEDs27() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void Cabrio_2Effect() {
  const char* text = "CABRIOLETTA";
  char buffer[12] = {0}; // Buffer om de geanimeerde tekst in op te slaan

  for (int i = 1; i <= 6; i++) {
    if (!effect27Enabled()) return; // Controleer de voorwaarde en stop indien nodig
    clearLEDs27();
    strncpy(buffer, text, i); // Voeg de eerste i letters van "CABRIO" toe aan de buffer
    displayText27(buffer);
    delay(OffTime27);
  }

  if (!effect27Enabled()) return; // Controleer de voorwaarde en stop indien nodig

  // Voeg "LETTA" in één keer toe
  strcat(buffer, "LETTA");
  clearLEDs27();
  displayText27(buffer);
  delay(OffTime27);

  // Herhaal de animatie indien de voorwaarde nog steeds waar is
  if (effect27Enabled()) {
    delay(OffTime27);
  }
}

void performEffects_27() {
  if (effect27Enabled()) {
    Cabrio_2Effect();
  }
}

#endif

