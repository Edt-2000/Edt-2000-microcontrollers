
#ifndef EFFECT_23_H
#define EFFECT_23_H

#include <FastLED.h>

#define LED_PIN     5   // Aanpassen naar de gewenste pin
#define NUM_LEDS    640 // Totaal aantal LED's in de matrix



extern CRGB leds[];




void  performEffects_23() {
     fill_solid(leds, NUM_LEDS, CRGB(0, 0, 255)); // 
     FastLED.show(); // Toon de LEDs
}


#endif