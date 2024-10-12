
#ifndef EFF_33_H
#define EFF_33_H

#include <FastLED.h>
#include "font.h"

#define NUM_LEDS 640 // 8x80 LED matrix
#define DATA_PIN 5   // Verander dit naar het juiste datapin-nummer
#define LED_TYPE WS2812B // Verander dit naar het juiste LED-type

#define FADE_DURATION 1000  // Duur van de fade in en fade out in milliseconden
#define HOLD_DURATION 500  // Tijd dat de tekst zichtbaar blijft na de fade in

#define COLOR_CHANGE_DELAY33 350 // Delay before changing to the next color in milliseconds

extern CRGB leds[];
bool effect33Enabled();

// Kleurinstellingen
CRGB colorAdem = CRGB::Orange;
CRGB colorInUit = CRGB::Magenta;

// Tijd variabelen
unsigned long fadeStartTime = 0;
unsigned long lastChangeTimeInUit = 0;
bool showingIn = true;

void drawLetter33(const byte *letter, int startX, int startY, CRGB color) {
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

void drawWord33(const char *word, int startX, int startY, CRGB color) {
    int wordLength = strlen(word);
    for (int i = 0; i < wordLength; i++) {
        char currentChar = word[i];
        if (currentChar >= ' ' && currentChar <= '~') {
            int letterIndex = currentChar - ' ';
            drawLetter33(font[letterIndex], startX + i * 6, startY, color);
        }
    }
}

void fadeText(const char *text, CRGB color) {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - fadeStartTime;

    // Bereken helderheid gebaseerd op de fade-in/out tijd
    int brightness;
    if (elapsedTime < FADE_DURATION) {
        brightness = map(elapsedTime, 0, FADE_DURATION, 0, 255);
    } else if (elapsedTime < FADE_DURATION + HOLD_DURATION) {
        brightness = 255;
    } else if (elapsedTime < 2 * FADE_DURATION + HOLD_DURATION) {
        brightness = map(elapsedTime, FADE_DURATION + HOLD_DURATION, 2 * FADE_DURATION + HOLD_DURATION, 255, 0);
    } else {
        fadeStartTime = currentTime;  // Reset fade
        return;
    }

    // Pas helderheid toe op kleur
    CRGB fadedColor = color;
    fadedColor.nscale8_video(brightness);

    // Wis de LEDs en teken de tekst
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    drawWord33(text, 10, 0, fadedColor);  // Positie aangepast voor 'ADEM'
    FastLED.show();
}

void drawInUit() {
    unsigned long currentTime = millis();

    if (currentTime - lastChangeTimeInUit >= COLOR_CHANGE_DELAY33) {
        showingIn = !showingIn;
        lastChangeTimeInUit = currentTime;

        // Wis de LEDs in het gebied waar "IN" of "UIT" wordt weergegeven
        fill_solid(leds + (80 * 4), 80 * 4, CRGB::Black);  // Maak de helft van de matrix schoon

        // Teken de tekst "IN" of "UIT"
        const char *text = showingIn ? "IN" : "UIT";
        drawWord30(text, 50, 0, colorInUit);  // Positie aangepast voor 'IN' en 'UIT'

        // Update de LEDs alleen als de tekst verandert
        FastLED.show();
    }
}

void performEffects_33() {
    if (effect33Enabled()) {
        fadeText("ADEM", colorAdem); // Roze (PINK) voor 'ADEM'
        drawInUit(); // Geel (YELLOW) voor 'IN' en 'UIT'
    } else {
        fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
        FastLED.show();
    }
}

#endif
