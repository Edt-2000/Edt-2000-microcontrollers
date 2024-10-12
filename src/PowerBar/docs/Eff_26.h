

#ifndef EFFECT_26_H
#define EFFECT_26_H

#include <FastLED.h>
#include "font.h"

#define NUM_LEDS 640 // 8x80 LED matrix
#define DATA_PIN 5    // Verander dit naar het juiste datapin-nummer
#define LED_TYPE WS2812B // Verander dit naar het juiste LED-type
#define OffTime 100

extern CRGB leds[];

bool effect26Enabled();

void drawLetter26(const byte *letter, int startX, int startY) {
  for (int i = 0; i < 5; i++) {
    byte column = pgm_read_byte(letter + i); // Lees de kolomgegevens voor de huidige letter
    for (int j = 0; j < 7; j++) {
      if (column & (1 << j)) {
        // Bit is ingesteld, zet de corresponderende LED aan
        int ledIndex = (startX + i) * 8 + (6 - j) + startY * 80; // Geen wijziging in startY
        leds[ledIndex] = CRGB::DarkTurquoise ;
      }
    }
  }
}

void displayText26(const char *text) {
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
    char currentChar = text[currentIndex];
    if (currentChar >= ' ' && currentChar <= '~') {
      int letterIndex = currentChar - ' ';
      drawLetter26(font[letterIndex], startX, startY);
      startX += 6 + letterSpacing; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters
    }
    currentIndex++;
  }

  // Toon de LED's
  FastLED.show();
}

void clearLEDs26() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void Cabrio_1Effect() {
  const char* textPart1 = "Ik heb een";
  const char* textPart2 = "CABRIO";
  const char* textPart3 = "CABRIOLETTA";
  char buffer[20] = {0}; // Buffer om de geanimeerde tekst in op te slaan

  for (int repeat = 0; repeat < 3; repeat++) {
    if (!effect26Enabled()) return; // Controleer de voorwaarde en stop indien nodig

    // Weergeef "Ik heb een" met schuifeffect
    for (int i = 1; i <= strlen(textPart1); i++) {
      if (!effect26Enabled()) return; // Controleer de voorwaarde en stop indien nodig
      clearLEDs26();
      strncpy(buffer, textPart1, i); // Voeg de eerste i letters van "Ik heb een" toe aan de buffer
      buffer[i] = '\0'; // Zorg ervoor dat buffer een geldige string is
      displayText26(buffer);
      delay(OffTime);
    }

    if (!effect26Enabled()) return; // Controleer de voorwaarde en stop indien nodig

    // Weergeef "CABRIO" of "CABRIOLETTA" in één keer afhankelijk van de iteratie
    clearLEDs26();
    if (repeat < 2) {
      displayText26(textPart2);
    } else {
      displayText26(textPart3);
    }
    delay(OffTime * 3); // Verlengde tijd om "CABRIO" of "CABRIOLETTA" te laten zien
    clearLEDs26();
  }

  // Herhaal de animatie indien de voorwaarde nog steeds waar is
  if (effect26Enabled()) {
    delay(OffTime);
  }
}

void performEffects_26() {
  if (effect26Enabled()) {
    Cabrio_1Effect();
  }
}

#endif
