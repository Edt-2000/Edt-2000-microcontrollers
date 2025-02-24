
#ifndef EFFECT_16_H
#define EFFECT_16_H

#include <FastLED.h>

#define LED_PIN     5   // Aanpassen naar de gewenste pin
#define NUM_LEDS    640 // Totaal aantal LED's in de matrix

extern CRGB leds[];



void  preformExtra_1Effect() {
   
  
    static bool isRed = true; // Variabele om bij te houden welke kleur ingesteld moet worden
    
    if (isRed) {
        // Eerste helft rood, tweede helft blauw
        fill_solid(leds, NUM_LEDS/2, CRGB(255, 0, 0)); // Eerste helft rood
        fill_solid(&leds[NUM_LEDS/2], NUM_LEDS/2, CRGB(0, 0, 255)); // Tweede helft blauw
    } else {
        // Eerste helft blauw, tweede helft rood
        fill_solid(leds, NUM_LEDS/2, CRGB(0, 0, 255)); // Eerste helft blauw
        fill_solid(&leds[NUM_LEDS/2], NUM_LEDS/2, CRGB(255, 0, 0)); // Tweede helft rood
    }
    
    isRed = !isRed; // Wissel de kleuren voor de volgende keer
    
    FastLED.show(); // Toon de LEDs
    
    delay(300); // Optioneel: wacht 300 milliseconden voordat de volgende actie wordt uitgevoerd
}

void performEffects_16() {
    preformExtra_1Effect();
}

#endif