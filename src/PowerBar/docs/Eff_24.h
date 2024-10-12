#ifndef EFFECT_24_H
#define EFFECT_24_H

#include <FastLED.h>
#include "font.h"

#define NUM_LEDS 640 // 8x80 LED matrix
#define DATA_PIN 5   // Verander dit naar het juiste datapin-nummer
#define LED_TYPE WS2812B // Verander dit naar het juiste LED-type

extern CRGB leds[NUM_LEDS];
bool effect24Enabled();

// Kleurinstellingen
enum TextColor { RED2, GREEN2, BLUE2 };
TextColor currentColor = RED2;

// Strobe effect timings
unsigned long onTime = 50;  // Aantal milliseconden dat de tekst zichtbaar is
unsigned long offTime = 50; // Aantal milliseconden dat de tekst onzichtbaar is
unsigned long lastToggleTime = 0;
bool isTextVisible24 = true;

void changeColor() {
  // Verander kleur na het volledig uit het zicht zijn
  switch (currentColor) {
    case RED2:
      currentColor = GREEN2;
      break;
    case GREEN2:
      currentColor = BLUE2;
      break;
    case BLUE2:
      currentColor = RED2;
      break;
  }
}

CRGB getCurrentColor() {
  // Retourneer de huidige kleur
  switch (currentColor) {
    case RED2:
      return CRGB::Red;
    case GREEN2:
      return CRGB::Green;
    case BLUE2:
      return CRGB::Blue;
    default:
      return CRGB::White; // Default kleur indien iets fout gaat
  }
}

void drawLetter(const byte *letter, int startX, int startY) {
  for (int i = 0; i < 5; i++) {
    byte column = pgm_read_byte(letter + i); // Lees de kolomgegevens voor de huidige letter
    for (int j = 0; j < 7; j++) {
      if (column & (1 << j)) {
        // Bit is ingesteld, zet de corresponderende LED aan
        int x = startX + i;
        int y = startY + (6 - j);

        if (x >= 0 && x < 80 && y >= 0 && y < 8) {
          int ledIndex = x * 8 + y;
          leds[ledIndex] = getCurrentColor(); // Gebruik de huidige kleur
        }
      }
    }
  }
}

void drawWord(const char *word, int startX, int startY) {
  int wordLength = strlen(word);
  for (int i = 0; i < wordLength; i++) {
    char currentChar = word[i];
    if (currentChar >= ' ' && currentChar <= '~') {
      int letterIndex = currentChar - ' ';
      drawLetter(font[letterIndex], startX + i * 6, startY);
    }
  }
}

void displayText(const char *text, int startX) {
  int startY = 0;
  int letterSpacing = 1; // Ruimte tussen letters

  int currentIndex = 0;
  int textOffset = startX; // Huidige horizontale positie voor de tekstweergave

  while (text[currentIndex] != '\0') {
    char currentChar = text[currentIndex];

    if (strncmp(&text[currentIndex], "HARDER", 6) == 0) {
      // Tekst bevat "HARDER", pas strobe effect toe
      if (isTextVisible24) {
        drawWord("HARDER", textOffset, startY);
      }
      textOffset += 6 * 6; // Verplaats startX met de breedte van "HARDER"
      currentIndex += 6;   // Sla "HARDER" over
    } else {
      if (currentChar >= ' ' && currentChar <= '~') {
        int letterIndex = currentChar - ' ';
        drawLetter(font[letterIndex], textOffset, startY);
        textOffset += 6; // Ga naar de volgende letterpositie
      }
      currentIndex++;
    }
  }
}

bool shouldToggleStrobe() {
  unsigned long currentTime = millis();
  if (isTextVisible24 && currentTime - lastToggleTime >= onTime) {
    return true;
  } else if (!isTextVisible24 && currentTime - lastToggleTime >= offTime) {
    return true;
  }
  return false;
}

void scrollText(const char *text, int delayMs) {
  int textLength = strlen(text);
  int textWidth = textLength * 6; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters
  int displayWidth = 80; // Breedte van de matrix

  while (effect24Enabled()) {
    // Scroll naar links
    for (int offset = displayWidth; offset > -textWidth; offset--) {
      if (!effect24Enabled()) {
        fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
        FastLED.show();
        return; // Stop de animatie als de vlag is uitgeschakeld
      }
      if (shouldToggleStrobe()) {
        isTextVisible24 = !isTextVisible24;
        lastToggleTime = millis();
      }
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LED's
      displayText(text, offset); // Verplaats de tekst naar links
      FastLED.show();
      delay(delayMs);
    }

    // Verander de kleur na elke volledige scroll
    changeColor();
  }

  // Zet alle LEDs uit als de loop eindigt
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void performEffects_24() {
  if (effect24Enabled()) {
    scrollText("HARDER dan jij...", 1); // Start scrolling "HARDER DAN JIJ" met een vertraging van 10 ms
  }
}

#endif