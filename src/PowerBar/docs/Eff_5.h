
/////////COPS_4//////

#ifndef EFFECT_5_H
#define EFFECT_5_H

#include "FastLED.h"

#define NUM_LEDS 640
#define DATA_PIN 5

extern CRGB leds[];
bool effect5Enabled();

int writeTime = 1;

// LED-posities voor de letters
int S_LEDsW[] = {117, 110, 102, 94, 85, 84, 91, 99, 107, 114, 113, 104, 96, 88, 81};
int T_LEDsW[] = {134, 142, 150, 158, 166, 149,148, 147, 146, 145, 144};
int R_LEDsW[] = {176, 177, 178, 179, 180, 181, 182, 190, 198, 206, 213, 212, 203, 195, 187, 194, 201, 208};
int O_LEDsW[] = {246, 238, 229, 228, 227, 226, 225, 232, 240, 248, 257, 258, 259, 260, 261, 254};
int B_LEDsW[] = {272, 273, 274, 275, 276, 277, 278, 286, 294, 302, 309, 308, 299, 291, 283, 306, 305, 296, 288, 280};
int O_2_LEDsW[] = {342, 334, 325, 324, 323, 322, 321, 328, 336, 344, 353, 354, 355, 356, 357, 350};
int C_LEDsW[] = {405, 398, 390, 382, 373, 372, 371, 370, 369, 376, 384, 392, 401};
int O_3_LEDsW[] = {438, 430, 421, 420, 419, 418, 417, 424, 432, 440, 449, 450, 451, 452, 453, 446};
int P_LEDsW[] = {464, 465, 466, 467, 468, 469, 470, 478, 486, 494, 501, 500, 491, 483, 475};
int S_2_LEDsW[] = {549, 542, 534, 526, 517, 516, 523, 531, 539, 546, 545, 536, 528, 520, 513};


bool displayLetter(int letter_LEDsW[], int num_LEDsW, CRGB color) {
  for (int i = 0; i < num_LEDsW; i++) {
    if (!effect5Enabled()) {
      return false;
    }

    leds[letter_LEDsW[i]] = color;
    FastLED.show();
    delay(writeTime);
  }
  return true;
}

bool veryDodgyUglyBitje = true;

void performEffect(CRGB color) {

  // Controleer of het effect is uitgeschakeld voordat de volgende reeks LEDs wordt aangepast
  if (veryDodgyUglyBitje) {
    // Zet alle LEDs naar zwart
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0)); 
    FastLED.show();
    veryDodgyUglyBitje = false;
    //return;
  }

  if (
    displayLetter(S_LEDsW, sizeof(S_LEDsW) / sizeof(S_LEDsW[0]), color) &&
    displayLetter(T_LEDsW, sizeof(T_LEDsW) / sizeof(T_LEDsW[0]), color) &&
    displayLetter(R_LEDsW, sizeof(R_LEDsW) / sizeof(R_LEDsW[0]), color) &&
    displayLetter(O_LEDsW, sizeof(O_LEDsW) / sizeof(O_LEDsW[0]), color) &&
    displayLetter(B_LEDsW, sizeof(B_LEDsW) / sizeof(B_LEDsW[0]), color) &&
    displayLetter(O_2_LEDsW, sizeof(O_2_LEDsW) / sizeof(O_2_LEDsW[0]), color) &&
    displayLetter(C_LEDsW, sizeof(C_LEDsW) / sizeof(C_LEDsW[0]), color) &&
    displayLetter(O_3_LEDsW, sizeof(O_3_LEDsW) / sizeof(O_3_LEDsW[0]), color) &&
    displayLetter(P_LEDsW, sizeof(P_LEDsW) / sizeof(P_LEDsW[0]), color) &&
    displayLetter(S_2_LEDsW, sizeof(S_2_LEDsW) / sizeof(S_2_LEDsW[0]), color))
  {
    delay(100); // Wacht voordat de volgende kleur wordt weergegeven
    FastLED.show();
  }
  else {
    veryDodgyUglyBitje = true;
  }
}

void performEffectsCops_5() {
  performEffect(CRGB(255, 0, 0)); // Rood
  if (!effect5Enabled()) {
    // Zet alle LEDs naar zwart
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0)); 
    FastLED.show();
  }
  performEffect(CRGB(0, 0, 255)); // Blauw
  if (!effect5Enabled()) {
    // Zet alle LEDs naar zwart
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0)); 
    FastLED.show();
  }
   performEffect(CRGB(0, 255, 0)); // Groen
  if (!effect5Enabled()) {
    // Zet alle LEDs naar zwart
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0)); 
    FastLED.show();
  }
  // Voeg hier meer effecten toe indien gewenst
}

void performEffects_5(){
    performEffectsCops_5();
}



#endif
