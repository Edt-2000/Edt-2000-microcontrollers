
/////////COPS_1//////
 
#ifndef EFFECT_3_H
#define EFFECT_3_H

#include "FastLED.h"

#define NUM_LEDS 640
#define DATA_PIN 5

extern CRGB leds[];


// Define an array of LED indices for de eerste set van Rode LEDs //COPS_1 EFFECT//
int LED_S1Indices[] = { 81, 88, 96, 104, 113, 114, 107, 99, 91, 84, 85, 94, 102, 110, 117,
                        144, 145, 146, 147, 148, 149, 134, 142, 150, 158, 166,
                        176, 177, 178, 179, 180, 181, 182, 190, 198, 206, 213, 212, 203, 195, 187, 194, 201, 208,
                        225, 226, 227, 228, 229, 238, 246, 254, 261, 260, 259, 258, 257, 248, 240, 232,
                        272, 273, 274, 275, 276, 277, 278, 286, 294, 302, 309, 308, 299, 291, 283, 306, 305, 296, 288, 280,
                        321, 322, 323, 324, 325, 334, 342, 350, 357, 356, 355, 354, 353, 344, 336, 328 };
int numLEDs_S1 = sizeof(LED_S1Indices) / sizeof(LED_S1Indices[0]);

// Define an array of LED indices for de tweede set van blauwe LEDs //COPS_1 EFFECT//
int LED_S2Indices[] = { 401, 392, 384, 376, 369, 370, 371, 372, 373, 382, 390, 398, 405,
                        417, 418, 419, 420, 421, 430, 438, 446, 453, 452, 451, 450, 449, 440, 432, 424,
                        464, 465, 466, 467, 468, 469, 470, 478, 486, 494, 501, 500, 491, 483, 475,
                        513, 520, 528, 536, 545, 546, 539, 531, 523, 516, 517, 526, 534, 542, 549 };
int numLEDs_S2 = sizeof(LED_S2Indices) / sizeof(LED_S2Indices[0]);

//COPS_1 EFFECT
void combinedStrobeEffect(CRGB color1, int *indices1, int numLEDs1, CRGB color2, int *indices2, int numLEDs2, int delay_ms_on, int delay_ms_off) {
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
  for (int k = 0; k < 3; k++) {
    // Strobe effect for LEDs in the first array
    for (int i = 0; i < numLEDs1; i++) {
      int index = indices1[i];
      leds[index] = k == 1 ? CRGB::Red : color1;
    }
    FastLED.show();
    delay(delay_ms_on);

    for (int i = 0; i < numLEDs1; i++) {
      int index = indices1[i];
      leds[index] = CRGB::Black;
    }
    FastLED.show();
    delay(delay_ms_off);
  }
  for (int k = 0; k < 3; k++) {
    // Strobe effect for LEDs in the second array
    for (int i = 0; i < numLEDs2; i++) {
      int index = indices2[i];
      leds[index] = k == 1 ? CRGB::Blue : color2;
    }
    FastLED.show();
    delay(delay_ms_on);

    for (int i = 0; i < numLEDs2; i++) {
      int index = indices2[i];
      leds[index] = CRGB::Black;
    }
    FastLED.show();
    delay(delay_ms_off);
  }
}

void performEffects_3(){
      combinedStrobeEffect(CRGB::Red, LED_S1Indices, numLEDs_S1, CRGB::Blue, LED_S2Indices, numLEDs_S2, 50, 10);
}

#endif

