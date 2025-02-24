
#ifndef EFFECT_22_H
#define EFFECT_22_H

#include <FastLED.h>

#define LED_PIN     5   // Aanpassen naar de gewenste pin
#define NUM_LEDS    640 // Totaal aantal LED's in de matrix



extern CRGB leds[];




void  performEffects_22() {
     fill_solid(leds, NUM_LEDS, CRGB(0, 255, 0)); // 
     FastLED.show(); // Toon de LEDs
}


#endif