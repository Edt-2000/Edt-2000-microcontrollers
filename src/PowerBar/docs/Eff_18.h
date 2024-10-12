
#ifndef EFFECT_18_H
#define EFFECT_18_H

#include <FastLED.h>

#define LED_PIN     5   // Aanpassen naar de gewenste pin
#define NUM_LEDS    640 // Totaal aantal LED's in de matrix



extern CRGB leds[];




void  preformExtra_3Effect() {
     fill_solid(leds, NUM_LEDS, CRGB(255, 0, 229)); // roze
     FastLED.show(); // Toon de LEDs
}

void performEffects_18() {
    preformExtra_3Effect();
}

#endif


