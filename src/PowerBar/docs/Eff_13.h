
#ifndef EFFECT_13_H
#define EFFECT_13_H

#include <FastLED.h>

#define LED_PIN      5
#define NUM_LEDS     640
//#define BRIGHTNESS   50
#define LED_TYPE     WS2812B
#define COLOR_ORDER  GRB

//CRGB leds[NUM_LEDS];
extern CRGB leds[];

//unsigned long previousMillis = 0;
//const long interval = 100; // Interval in milliseconds

/*void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
 preformDataEffect();
}*/

void data1Effect() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (random(3) == 0) { // Adjust the probability to control the density of lit LEDs
      leds[i] = CRGB::Green; // Adjust the color as desired
    } else if (random(20) == 0) { // Adjust the probability to control the density of raindrops
      for (int j = 0; j < 10; j++) { // Extend the length of the raindrop effect
        if (i + j < NUM_LEDS) {
          leds[i + j] = CRGB(200, 200, 200).fadeToBlackBy(50 * j); // Gradually dim the white LEDs to create comet streak effect
        }
      }
    } else if (random(6) == 0) { // Adjust the probability to control the density of blue LEDs
      leds[i] = CRGB::Blue; // Add blue LEDs
    } else {
      leds[i] = CRGB::Black; // Turn off the LED
    }
  }
  FastLED.show();
}

void preformDataEffect() {
    data1Effect(); // Call the matrixEffect function
    delay(100);
  }

void performEffects_13() {
    preformDataEffect();
}


#endif