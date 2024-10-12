#ifndef EFFECT_32_H
#define EFFECT_32_H

#include <FastLED.h>
#include "font.h"

#define LED_PIN     5   // Aanpassen naar de gewenste pin
#define NUM_LEDS    640 // Totaal aantal LED's in de matrix

extern CRGB leds[];
bool effect32Enabled();

// Kleurinstellingen
enum TextColor32 { RED_32, GREEN_32, BLUE_32 };
TextColor32 currentColor32 = RED_32;

CRGB getCurrentColor32() {
  // Retourneer de huidige kleur
  switch (currentColor32) {
    case RED_32:
      return CRGB::Red;
    case GREEN_32:
      return CRGB::Green;
    case BLUE_32:
      return CRGB::Blue;
    default:
      return CRGB::White; // Default kleur indien iets fout gaat
  }
}

// Functiedefinities
void drawLetter32(const byte *letter, int startX, int startY, CRGB color);
void displayText32(const char *text, int startX, int startY, CRGB color);
void changeColor32();
void strobeEffect(const char *text, int textX, int textY, CRGB color, int strobeDuration, int strobeDelay);
void scrollText32(const char *text1, const char *text2, int delayMs);

void drawLetter32(const byte *letter, int startX, int startY, CRGB color) {
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

void displayText32(const char *text, int startX, int startY, CRGB color) {
  int letterSpacing = 1; // Ruimte tussen letters

  int currentIndex = 0;

  // Loop door de tekst en weergeef elke letter
  while (text[currentIndex] != '\0') {
    char currentChar = text[currentIndex];
    if (currentChar >= ' ' && currentChar <= '~') {
      int letterIndex = currentChar - ' ';
      drawLetter32(font[letterIndex], startX + currentIndex * 6, startY, color); // Verschuif de letterpositie
    }
    currentIndex++;
  }
}

void changeColor32() {
  // Verander kleur na het volledig uit het zicht zijn
  switch (currentColor32) {
    case RED_32:
      currentColor32 = GREEN_32;
      break;
    case GREEN_32:
      currentColor32 = BLUE_32;
      break;
    case BLUE_32:
      currentColor32 = RED_32;
      break;
  }
}

void strobeEffect(const char *text, int textX, int textY, CRGB textColor, CRGB strobeColor, int strobeDuration, int strobeDelay, int text2StartX) {
  int endTime = millis() + strobeDuration;

  while (millis() < endTime) {
    if (!effect32Enabled()) {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      return;
    }

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    displayText32("COPS", text2StartX, 0, getCurrentColor32());
    displayText32(text, textX, textY, textColor);
    FastLED.show();
    delay(strobeDelay);

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    displayText32("COPS", text2StartX, 0, getCurrentColor32());
    displayText32(text, textX, textY, strobeColor);
    FastLED.show();
    delay(strobeDelay);
  }
}



void scrollText32(const char *text1, const char *text2, int delayMs) {
  int text1Length = strlen(text1);
  int text2Length = strlen(text2);
  int text1Width = text1Length * 6;
  int text2Width = text2Length * 6;
  int displayWidth = 80;

  int text1StartX = displayWidth;
  int text2StartX = -text2Width;

  while (effect32Enabled()) {
    while (text1StartX + text1Width > text2StartX) {
      if (!effect32Enabled()) {
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        return;
      }
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      displayText32(text1, text1StartX, 0, getCurrentColor32());
      displayText32(text2, text2StartX, 0, getCurrentColor32());
      FastLED.show();
      delay(delayMs);

      text1StartX--;
      text2StartX++;
    }

    for (int pause = 0; pause < 20; pause += delayMs) {
      if (!effect32Enabled()) {
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        return;
      }
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      displayText32(text1, text1StartX, 0, getCurrentColor32());
      displayText32(text2, text2StartX, 0, getCurrentColor32());
      FastLED.show();
      delay(delayMs);
    }

    // Voeg de kleur voor het strobe-effect toe, bijvoorbeeld CRGB::White voor wit
    strobeEffect(text1, text1StartX, 0, getCurrentColor32(), CRGB::White, 2000, 50, text2StartX);

    changeColor32();

    text1StartX = displayWidth;
    text2StartX = -text2Width;
  }

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}




void performEffects_32() {
  if (effect32Enabled()) {
    // Scroll "STROBO" van links naar rechts en "COPS" van rechts naar links
    scrollText32("STROBO", "COPS", 3); // Scroll met een vertraging van 3 ms
  }
}

#endif
