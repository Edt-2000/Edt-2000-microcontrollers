
/////////COPS_5//////

#ifndef EFFECT_2_H
#define EFFECT_2_H

#include <FastLED.h>

#define NUM_LEDS 640
#define DATA_PIN 5
#define FADE_TIME_MS 20 // Tijd (in milliseconden) tussen elke helderheidsstap
#define FADE_STEPS 50 // Aantal stappen voor de fade-in en fade-out

extern CRGB leds[];
bool effect2Enabled(); // Externe functie om te controleren of het effect is ingeschakeld

int S_LEDs2[] = {
  90, 97, 105, 113, 122, 123, 116, 108, 100, 93, 94, 103, 111, 119, 126,
  153,154, 155, 156, 157, 158, 143, 151, 159, 167, 175,
  185, 186, 187, 188, 189, 190, 191, 199, 207, 215, 222, 221, 212, 204, 196, 203, 210, 217,	  
  234, 235, 236, 237, 238, 247, 255, 263, 270, 269, 268, 267, 266, 257, 249, 241,
  281, 282, 283, 284, 285, 286, 287, 295, 303, 311, 318, 317, 308, 300, 292, 315, 314, 305, 297, 289,
  330, 331, 332, 333, 334, 343, 351, 359, 366, 365, 364, 363, 362, 353, 345, 337,
  410, 401, 393, 385, 378, 379, 380, 381, 382, 391, 399, 407, 414,
  426, 427, 428, 429, 430, 439, 447, 455, 462, 461, 460, 459, 458, 449, 441, 433,
  473, 474, 475, 476, 477, 478, 479, 487, 495, 503, 510, 509, 500, 492, 484,
  522, 529, 537, 545, 554, 555, 548, 540, 532, 525, 526, 535, 543, 551, 558
};

int numS_LEDs2 = sizeof(S_LEDs2) / sizeof(S_LEDs2[0]);

void EffectsCops_2() {
  CRGB colors[] = {CRGB(255, 0, 0), CRGB(0, 0, 255), CRGB(0, 255, 0)}; // Array met kleuren
  int numColors = sizeof(colors) / sizeof(colors[0]);

  for (int colorIndex = 0; colorIndex < numColors; colorIndex++) {
    CRGB color = colors[colorIndex];

    // Fade in
    for (int brightness = 0; brightness <= 255; brightness += (255 / FADE_STEPS)) {
      if (!effect2Enabled()) {
        fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
        FastLED.show();
        return; // Stop de animatie als de vlag is uitgeschakeld
      }
      for (int i = 0; i < numS_LEDs2; i++) {
        leds[S_LEDs2[i]] = color;
        leds[S_LEDs2[i]].fadeLightBy(255 - brightness);
      }
      FastLED.show();
      delay(FADE_TIME_MS);
    }

    // Fade out
    for (int brightness = 255; brightness >= 0; brightness -= (255 / FADE_STEPS)) {
      if (!effect2Enabled()) {
        fill_solid(leds, NUM_LEDS, CRGB::Black); // Zet alle LEDs uit
        FastLED.show();
        return; // Stop de animatie als de vlag is uitgeschakeld
      }
      for (int i = 0; i < numS_LEDs2; i++) {
        leds[S_LEDs2[i]] = color;
        leds[S_LEDs2[i]].fadeLightBy(255 - brightness);
      }
      FastLED.show();
      delay(FADE_TIME_MS);
    }
  }
}

void performEffects_2() {
  if (effect2Enabled()) {
    EffectsCops_2();
  }
}

#endif
