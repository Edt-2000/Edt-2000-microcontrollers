

#ifndef EFF_30_H
#define EFF_30_H

#include <FastLED.h>
#include "font.h"

#define NUM_LEDS 640 // 8x80 LED matrix
#define DATA_PIN 5   // Verander dit naar het juiste datapin-nummer
#define LED_TYPE WS2812B // Verander dit naar het juiste LED-type
#define STROBE_DELAY30 400 // Strobe delay in milliseconds
#define COLOR_CHANGE_DELAY30 500 // Delay before changing to the next color in milliseconds

extern CRGB leds[];
bool effect30Enabled();

// Kleurinstellingen
CRGB colors30[] = { CRGB::Magenta, CRGB::Magenta, CRGB::Magenta, CRGB::Magenta, CRGB::Magenta, CRGB::Magenta, CRGB::Magenta };
int colorIndex30 = 0;

// Strobe effect timings
unsigned long lastStrobeTime30 = 0;
unsigned long lastColorChangeTime30 = 0;
bool isTextVisible30 = true;

void changeColor30() {
  // Verander naar de volgende kleur in de array
  colorIndex30 = (colorIndex30 + 1) % (sizeof(colors30) / sizeof(colors30[0]));
}

CRGB getCurrentColor30() {
  // Retourneer de huidige kleur
  return colors30[colorIndex30];
}

void drawLetter30(const byte *letter, int startX, int startY, CRGB color) {
  for (int i = 0; i < 5; i++) {
    byte column = pgm_read_byte(letter + i); // Lees de kolomgegevens voor de huidige letter
    for (int j = 0; j < 7; j++) {
      if (column & (1 << j)) {
        // Bit is ingesteld, zet de corresponderende LED aan
        int x = startX + i;
        int y = startY + (6 - j);

        if (x >= 0 && x < 80 && y >= 0 && y < 8) {
          int ledIndex = x * 8 + y;
          leds[ledIndex] = color; // Gebruik de huidige kleur
        }
      }
    }
  }
}

void drawWord30(const char *word, int startX, int startY, CRGB color) {
  int wordLength = strlen(word);
  for (int i = 0; i < wordLength; i++) {
    char currentChar = word[i];
    if (currentChar >= ' ' && currentChar <= '~') {
      int letterIndex = currentChar - ' ';
      drawLetter30(font[letterIndex], startX + i * 6, startY, color);
    }
  }
}

bool shouldToggleStrobe30() {
  unsigned long currentTime = millis();
  if (isTextVisible30 && currentTime - lastStrobeTime30 >= STROBE_DELAY30) {
    return true;
  } else if (!isTextVisible30 && currentTime - lastStrobeTime30 >= STROBE_DELAY30) {
    return true;
  }
  return false;
}

void strobeText30(const char *text, int delayMs) {
  int textLength = strlen(text);
  int textWidth = textLength * 6; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters
  int startX = (80 - textWidth) / 2; // Bereken startX om de tekst te centreren

  while (effect30Enabled()) {
    unsigned long currentTime = millis();

    // Check if we should toggle the strobe effect
    if (shouldToggleStrobe30()) {
      isTextVisible30 = !isTextVisible30;
      lastStrobeTime30 = currentTime;
    }

    // Check if we should change the color
    if (currentTime - lastColorChangeTime30 >= COLOR_CHANGE_DELAY30) {
      changeColor30();
      lastColorChangeTime30 = currentTime;
    }

    fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LEDs

    if (isTextVisible30) {
      drawWord30(text, startX, 0, getCurrentColor30()); // Show the text at the top-left corner
    }

    FastLED.show();
    delay(delayMs);
  }

  // Clear LEDs when effect is disabled
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void performEffects_30() {
  if (effect30Enabled()) {
    strobeText30("NEUKEN", 1); // Start strobe effect with "MEER POWER"
  } else {
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
    FastLED.show();
  }
}

#endif

