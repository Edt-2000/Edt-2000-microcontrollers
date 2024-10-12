

#ifndef EFFECT_34_H
#define EFFECT_34_H

#include <FastLED.h>
#include "font.h"

#define NUM_LEDS 640 // 8x80 LED matrix
#define DATA_PIN 5   // Verander dit naar het juiste datapin-nummer
#define LED_TYPE WS2812B // Verander dit naar het juiste LED-type
#define STROBE_DELAY34 40 // Strobe delay in milliseconds
#define COLOR_CHANGE_DELAY34 1000 // Delay before changing to the next color in milliseconds

extern CRGB leds[];
bool effect34Enabled();

// Kleurinstellingen
CRGB colors34[] = { CRGB::Orange, CRGB::White, CRGB::Yellow, CRGB::White, CRGB::Gold, CRGB::Magenta, CRGB::White };
int colorIndex34 = 0;

// Strobe effect timings
unsigned long lastStrobeTime34 = 0;
unsigned long lastColorChangeTime34 = 0;
bool isTextVisible34 = true;

void changeColor34() {
  // Verander naar de volgende kleur in de array
  colorIndex34 = (colorIndex34 + 1) % (sizeof(colors34) / sizeof(colors28[0]));
}

CRGB getCurrentColor34() {
  // Retourneer de huidige kleur
  return colors34[colorIndex34];
}

void drawLetter34(const byte *letter, int startX, int startY, CRGB color) {
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

void drawWord34(const char *word, int startX, int startY, CRGB color) {
  int wordLength = strlen(word);
  for (int i = 0; i < wordLength; i++) {
    char currentChar = word[i];
    if (currentChar >= ' ' && currentChar <= '~') {
      int letterIndex = currentChar - ' ';
      drawLetter34(font[letterIndex], startX + i * 6, startY, color);
    }
  }
}

bool shouldToggleStrobe34() {
  unsigned long currentTime = millis();
  if (isTextVisible34 && currentTime - lastStrobeTime34 >= STROBE_DELAY34) {
    return true;
  } else if (!isTextVisible34 && currentTime - lastStrobeTime34 >= STROBE_DELAY34) {
    return true;
  }
  return false;
}

void strobeText34(const char *text, int delayMs) {
  int textLength = strlen(text);
  int textWidth = textLength * 6; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters
  int startX = (80 - textWidth) / 2; // Bereken startX om de tekst te centreren

  while (effect34Enabled()) {
    unsigned long currentTime = millis();

    // Check if we should toggle the strobe effect
    if (shouldToggleStrobe34()) {
      isTextVisible34 = !isTextVisible34;
      lastStrobeTime34 = currentTime;
    }

    // Check if we should change the color
    if (currentTime - lastColorChangeTime34 >= COLOR_CHANGE_DELAY34) {
      changeColor34();
      lastColorChangeTime34 = currentTime;
    }

    fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear de LEDs

    if (isTextVisible34) {
      drawWord34(text, startX, 0, getCurrentColor34()); // Show the text at the top-left corner
    }

    FastLED.show();
    delay(delayMs);
  }

  // Clear LEDs when effect is disabled
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void performEffects_34() {
  if (effect34Enabled()) {
    strobeText34("VOEL NIKS", 1); // Start strobe effect with "MEER POWER"
  } else {
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
    FastLED.show();
  }
}

#endif
