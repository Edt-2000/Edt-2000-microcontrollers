
/////////COPS_3//////
 
#ifndef EFFECT_1_H
#define EFFECT_1_H

#include "FastLED.h"

#define NUM_LEDS 640
//#define BRIGHTNESS 10
#define DATA_PIN 5
#define ON_TIME_MS 500 // Tijd (in milliseconden) dat de LED's aan blijven
#define OFF_TIME_MS 500 // Tijd (in milliseconden) dat de LED's uit blijven

extern CRGB leds[];
//CRGB leds[NUM_LEDS];

int S_LEDs[] = {90, 97, 105, 113, 122, 123, 116, 108, 100, 93, 94, 103, 111, 119, 126,
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

int numS_LEDs = sizeof(S_LEDs) / sizeof(S_LEDs[0]);

bool ledsOn = false; // Controlevariabele voor de LED-status
int colorIndex = 0; // Variabele om de huidige kleurstatus bij te houden


void performEffectsCops_1 () {
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0)); 
  if (ledsOn) {
    // Schakel de LED's in de S_LEDs array uit
    for (int i = 0; i < numS_LEDs; i++) {
      leds[S_LEDs[i]] = CRGB(0, 0, 0);
    }
    ledsOn = false;
    FastLED.show();
    delay(OFF_TIME_MS);
  } else {
    CRGB color;
    // Kies de kleur op basis van de huidige kleurstatus
    if (colorIndex == 0) {
      color = CRGB(255, 0, 0); // Rood
    } else if (colorIndex == 1) {
      color = CRGB(0, 0, 255); // Blauw
    } else if (colorIndex == 2) {
      color = CRGB(0, 255, 0); // Groen
    }

    // Schakel de LED's in de S_LEDs array aan met de gekozen kleur
    for (int i = 0; i < numS_LEDs; i++) {
      leds[S_LEDs[i]] = color;
    }
    ledsOn = true;
    FastLED.show();
    delay(ON_TIME_MS);
    
    // Verhoog de kleurindex en reset als deze 3 bereikt
    colorIndex = (colorIndex + 1) % 3;
  }
}

void performEffects_1(){
    performEffectsCops_1();
}


#endif