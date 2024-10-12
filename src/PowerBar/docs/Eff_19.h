
#ifndef EFFECT_19_H
#define EFFECT_19_H

#include <FastLED.h>

#define LED_PIN     5   // Aanpassen naar de gewenste pin
#define NUM_LEDS    640 // Totaal aantal LED's in de matrix



extern CRGB leds[];


void  preformExtra_4Effect() {
   

     fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0)); // roze
     FastLED.show(); // Toon de LEDs


}

void performEffects_19() {
    preformExtra_4Effect();
}

#endif