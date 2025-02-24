

#ifndef EFFECT_25_H
#define EFFECT_25_H

#include <FastLED.h>
#include "font.h"

#define NUM_LEDS 640 // 8x80 LED matrix
#define DATA_PIN 5    // Verander dit naar het juiste datapin-nummer
#define LED_TYPE WS2812B // Verander dit naar het juiste LED-type
//#define BRIGHTNESS 40

extern CRGB leds[NUM_LEDS];

bool effect25Enabled();


void flag(){
// Definieer de kleuren
CRGB blauw = CRGB(0, 0, 255);
CRGB geel = CRGB(255, 255, 0);

// Stel de kleuren in voor de linker 2 en rechter 2 matricen
for (int i = 0; i < 16; i++) { // Links (2 matrices van 8x8)
  leds[i] = blauw;
}
for (int i = 624; i < 640; i++) { // Rechts (2 matrices van 8x8) 
  leds[i] = geel;
}


// Bovenste helft blauw, onderste helft geel
for (int i = 0; i < 21; i++) { // Links (2 matrices van 8x8)
  for (int j = 0; j < 4; j++) {
    leds[i * 8 + j] = geel;
    leds[i * 8 + j + 4] = blauw;
  }
}

for (int i = 58; i < 80; i++) { // Rechts (2 matrices van 8x8)
  for (int j = 0; j < 4; j++) {
    leds[i * 8 + j] = geel;
    leds[i * 8 + j + 4] = blauw;
   }
  }
}


void drawLetter25(const byte *letter, int startX, int startY) {
  for (int i = 0; i < 5; i++) {
    byte column = pgm_read_byte(letter + i); // Lees de kolomgegevens voor de huidige letter
    for (int j = 0; j < 7; j++) {
      if (column & (1 << j)) {
        // Bit is ingesteld, zet de corresponderende LED aan
        int ledIndex = (startX + i) * 8 + (6 - j) + startY * 80; // Geen wijziging in startY
        leds[ledIndex] = CRGB::DeepPink;
      }
    }
  }
}

void displayText25(const char *text) {
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
      drawLetter25(font[letterIndex], startX, startY);
      startX += 6 + letterSpacing; // Breedte van elke letter is 5, plus 1 voor ruimte tussen letters
    }
    currentIndex++;
  }
}

void clearLEDs25() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
 
}


void showPoetin(){
  
  clearLEDs25(); // Wis de LED's voordat je de volgende tekst weergeeft
  flag();  
  displayText25("POETIN");
  FastLED.show();
  delay(400); // Wacht .. ms seconde

  clearLEDs25(); // Wis de LED's voordat je de volgende tekst weergeeft
  flag();  
  displayText25("is een");
  FastLED.show();
  delay(250); // Wacht .. ms seconde

  clearLEDs25(); // Wis de LED's voordat je de volgende tekst weergeeft
  flag();  
  displayText25("LUL");
  FastLED.show();
  delay(400); // Wacht .. ms seconde
 
}

void performEffects_25() {
  if (effect25Enabled()){
   showPoetin();  
  }
}

#endif

