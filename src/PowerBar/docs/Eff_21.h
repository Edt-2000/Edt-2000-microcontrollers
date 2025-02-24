
#ifndef EFFECT_21_H
#define EFFECT_21_H

#include <FastLED.h>
#include "font.h"

#define NUM_LEDS 640 // 8x80 LED matrix
#define DATA_PIN 5    // Verander dit naar het juiste datapin-nummer
#define LED_TYPE WS2812B // Verander dit naar het juiste LED-type

extern CRGB leds[NUM_LEDS];
bool effect21Enabled();

// Declaraties van functies
void initializeEffect21();
void drawLetter(const byte *letter, int startX, int startY, CRGB color, int letterIndex);
void displayTextEffect(const char *text);
void clearLetter(int letterIndex);
void displayLetterEffect(const char *text, int index);
void glitchEffect();
void performEffect_21();

// Variabelen
const CRGB colors21[] = {
  CRGB::Red,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Orange,
  CRGB::Cyan,
  CRGB::Magenta,
  CRGB::Orange,
  CRGB::Purple
};
const int numColors = sizeof(colors21) / sizeof(colors21[0]);

// Struct om glitch-timers bij te houden
struct Glitch {
  unsigned long nextGlitchTime;
  int phase;
};

Glitch glitches[11]; // Aantal letters in "CODEMONKEYS"

// Functie-implementaties

void initializeEffect21() {
  // Initializeer glitches
  for (int i = 0; i < 11; i++) {
    glitches[i].nextGlitchTime = millis() + random(1000, 5000); // Begin glitch-tijden willekeurig
    glitches[i].phase = 0;
  }

  // Weergeef de tekst "CODEMONKEYS"
  displayTextEffect("CODEMONKEYS");
}

void drawLetter(const byte *letter, int startX, int startY, CRGB color, int letterIndex) {
  for (int i = 0; i < 5; i++) {
    byte column = pgm_read_byte(letter + i); // Lees de kolomgegevens voor de huidige letter
    for (int j = 0; j < 7; j++) {
      if (column & (1 << j)) {
        // Bit is ingesteld, zet de corresponderende LED aan
        int ledIndex = (startX + i) * 8 + (6 - j) + startY * 80; // Geen wijziging in startY
        leds[ledIndex] = color;
      }
    }
  }
}

void displayTextEffect(const char *text) {
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
      CRGB color = colors21[currentIndex % numColors];
      drawLetter(font[letterIndex], startX, startY, color, currentIndex);
      startX += 6 + letterSpacing; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters
    }
    currentIndex++;
  }
}

void clearLetter(int letterIndex) {
  int textLength = 11; // Lengte van "CODEMONKEYS"
  int letterWidth = 6; // 5 pixels breed plus 1 pixel spatie
  int totalTextWidth = textLength * letterWidth;

  // Bereken startX om de tekst te centreren
  int startX = (80 - totalTextWidth) / 2;
  startX += letterIndex * letterWidth;
  int startY = 0; // Aangezien we slechts één regel hebben

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      int ledIndex = (startX + i) * 8 + (6 - j) + startY * 80; // Geen wijziging in startY
      leds[ledIndex] = CRGB::Black;
    }
  }
}

void displayLetterEffect(const char *text, int index) {
  int letterWidth = 6; // 5 pixels breed plus 1 pixel spatie
  int startX = (80 - (strlen(text) * letterWidth)) / 2 + index * letterWidth;
  int startY = 0; // Aangezien we slechts één regel hebben
  char currentChar = text[index];
  int letterIndex = currentChar - ' ';
  CRGB color = colors21[index % numColors];
  drawLetter(font[letterIndex], startX, startY, color, index);
}

void glitchEffect() {
  unsigned long currentTime = millis();
  for (int i = 0; i < 11; i++) {
    if (currentTime >= glitches[i].nextGlitchTime) {
      switch (glitches[i].phase) {
        case 0:
          // Zet letter uit
          clearLetter(i);
          glitches[i].nextGlitchTime = currentTime + 50; // Kort uit
          glitches[i].phase = 1;
          break;
        case 1:
          // Zet letter aan
          displayLetterEffect("CODEMONKEYS", i);
          glitches[i].nextGlitchTime = currentTime + 50; // Kort aan
          glitches[i].phase = 2;
          break;
        case 2:
          // Zet letter uit
          clearLetter(i);
          glitches[i].nextGlitchTime = currentTime + 50; // Kort uit
          glitches[i].phase = 3;
          break;
        case 3:
          // Zet letter aan
          displayLetterEffect("CODEMONKEYS", i);
          glitches[i].nextGlitchTime = currentTime + 200; // Iets langer aan
          glitches[i].phase = 0;
          // Stel de volgende glitch-tijd willekeurig in
          glitches[i].nextGlitchTime += random(1000, 5000);
          break;
      }
    }
  }
}

void performEffects_21() {
  if (!effect21Enabled()) {
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
    FastLED.show();
    return;
  }

  glitchEffect();
  FastLED.show();
}

#endif
