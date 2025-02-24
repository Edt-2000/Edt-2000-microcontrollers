

#ifndef EFFECT_28_H
#define EFFECT_28_H

#include <FastLED.h>
#include "font.h"

#define NUM_LEDS 640 // 8x80 LED matrix
#define DATA_PIN 5   // Verander dit naar het juiste datapin-nummer
#define LED_TYPE WS2812B // Verander dit naar het juiste LED-type
#define STROBE_DELAY 40 // Strobe delay in milliseconds
#define COLOR_CHANGE_DELAY 1000 // Delay before changing to the next color in milliseconds

extern CRGB leds[];
bool effect28Enabled();

// Kleurinstellingen
CRGB colors28[] = { CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Cyan, CRGB::Magenta, CRGB::White };
int colorIndex28 = 0;

// Strobe effect timings
unsigned long lastStrobeTime = 0;
unsigned long lastColorChangeTime = 0;
bool isTextVisible28 = true;

void changeColor28() {
  // Verander naar de volgende kleur in de array
  colorIndex28 = (colorIndex28 + 1) % (sizeof(colors28) / sizeof(colors28[0]));
}

CRGB getCurrentColor28() {
  // Retourneer de huidige kleur
  return colors28[colorIndex28];
}

void drawLetter28(const byte *letter, int startX, int startY, CRGB color) {
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

void drawWord28(const char *word, int startX, int startY, CRGB color) {
  int wordLength = strlen(word);
  for (int i = 0; i < wordLength; i++) {
    char currentChar = word[i];
    if (currentChar >= ' ' && currentChar <= '~') {
      int letterIndex = currentChar - ' ';
      drawLetter28(font[letterIndex], startX + i * 6, startY, color);
    }
  }
}

bool shouldToggleStrobe28() {
  unsigned long currentTime = millis();
  if (isTextVisible28 && currentTime - lastStrobeTime >= STROBE_DELAY) {
    return true;
  } else if (!isTextVisible28 && currentTime - lastStrobeTime >= STROBE_DELAY) {
    return true;
  }
  return false;
}

void strobeText28(const char *text, int delayMs) {
  int textLength = strlen(text);
  int textWidth = textLength * 6; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters
  int startX = (80 - textWidth) / 2; // Bereken startX om de tekst te centreren

  while (effect28Enabled()) {
    unsigned long currentTime = millis();

    // Check if we should toggle the strobe effect
    if (shouldToggleStrobe28()) {
      isTextVisible28 = !isTextVisible28;
      lastStrobeTime = currentTime;
    }

    // Check if we should change the color
    if (currentTime - lastColorChangeTime >= COLOR_CHANGE_DELAY) {
      changeColor28();
      lastColorChangeTime = currentTime;
    }

    fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LEDs

    if (isTextVisible28) {
      drawWord28(text, startX, 0, getCurrentColor28()); // Show the text at the top-left corner
    }

    FastLED.show();
    delay(delayMs);
  }

  // Clear LEDs when effect is disabled
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void performEffects_28() {
  if (effect28Enabled()) {
    strobeText28("MEER POWER", 1); // Start strobe effect with "MEER POWER"
  } else {
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
    FastLED.show();
  }
}

#endif
