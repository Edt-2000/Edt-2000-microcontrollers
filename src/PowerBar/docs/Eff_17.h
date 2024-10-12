
#ifndef EFFECT_17_H
#define EFFECT_17_H

#include "FastLED.h"

#define NUM_LEDS 640
#define DATA_PIN 5
#define FADE_TIME_MS 10 // Tijd (in milliseconden) tussen elke helderheidsstap
#define FADE_STEPS 50 // Aantal stappen voor de fade-in en fade-out

//CRGB leds[NUM_LEDS];
extern CRGB leds[];

int S_LEDs3[] = {
44, 45, 51, 52, 53, 54, 58, 59, 60, 61, 62, 63, 65, 66, 67, 68, 69, 70, 72, 73, 74, 75, 76, 77, 81, 82, 83, 84, 85, 86, 90, 91, 92, 93, 94, 95, 99, 100, 101, 102, 108, 109,
204, 205, 211, 212, 213, 214, 218, 219, 220, 221, 222, 223, 225, 226, 227, 228, 229, 230, 232, 233, 234, 235, 236, 237, 241, 242, 243, 244, 245, 246, 250, 251, 252, 253, 254, 255, 259, 260, 261, 262, 268, 269,
364, 365, 371, 372, 373, 374, 378, 379, 380, 381, 382, 383, 385, 386, 387, 388, 389, 390, 392, 393, 394, 395, 396, 397, 401, 402, 403, 404, 405, 406, 410, 411, 412, 413, 414, 415, 419, 420, 421, 422, 428, 429,
524, 525, 531, 532, 533, 534, 538, 539, 540, 541, 542, 543, 545, 546, 547, 548, 549, 550, 552, 553, 554, 555, 556, 557, 561, 562, 563, 564, 565, 566, 570, 571, 572, 573, 574, 575, 579, 580, 581, 582, 588, 589
};

int numS_LEDs3 = sizeof(S_LEDs3) / sizeof(S_LEDs3[0]);

int colorIndex3 = 0; // Variabele om de huidige kleurstatus bij te houden



void preformExtra_2Effect() {
   fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0)); // 
     FastLED.show(); // Toon de LEDs
  CRGB color;
  // Kies de kleur op basis van de huidige kleurstatus
  if (colorIndex3 == 0) {
    color = CRGB(205, 0, 105); // 
  } else if (colorIndex3 == 1) {
    color = CRGB(235, 0, 50); // 
  } else if (colorIndex3 == 2) {
    color = CRGB(255, 0, 0); // 
  }

  // Fade in
  for (int brightness = 0; brightness <= 255; brightness += (255 / FADE_STEPS)) {
    for (int i = 0; i < numS_LEDs3; i++) {
      leds[S_LEDs3[i]] = color;
      leds[S_LEDs3[i]].fadeLightBy(255 - brightness);
    }
    FastLED.show();
    delay(FADE_TIME_MS);
  }

  // Fade out
  for (int brightness = 255; brightness >= 0; brightness -= (255 / FADE_STEPS)) {
    for (int i = 0; i < numS_LEDs3; i++) {
      leds[S_LEDs3[i]] = color;
      leds[S_LEDs3[i]].fadeLightBy(255 - brightness);
    }
    FastLED.show();
    delay(FADE_TIME_MS);

  }

  // Verhoog de kleurindex en reset als deze 3 bereikt
  colorIndex3 = (colorIndex3 + 1) % 3;
}  

void performEffects_17() {
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0)); // 
    FastLED.show(); // Toon de LEDs
    preformExtra_2Effect();
}


#endif
