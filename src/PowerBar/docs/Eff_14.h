
#ifndef EFFECT_14_H
#define EFFECT_14_H

#include <FastLED.h>

// Mark's xy coordinate mapping code.
const uint8_t kMatrixWidth = 8;
const uint8_t kMatrixHeight = 80;

#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight)
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
//#define COLOR_ORDER   RBG


const bool kMatrixSerpentineLayout = true;

//CRGB leds[NUM_LEDS];
extern CRGB leds[];


static uint16_t x;
static uint16_t y;
static uint16_t z;


uint16_t speed = 20;
uint16_t scale = 311;
uint16_t noise[MAX_DIMENSION][MAX_DIMENSION];



uint16_t XY(uint8_t x, uint8_t y) {
  uint16_t i;
 
  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }
 
  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
 
  return i;
}

void fillnoise8() {
  for (int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = scale * i;
    for (int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = scale * j;
      noise[i][j] = inoise8(x + ioffset, y + joffset, z);
    }
  }
  z += speed;
}

void preformCarnavalEffect() {
  fillnoise8();
  for (int i = 0; i < kMatrixWidth; i++) {
    for (int j = 0; j < kMatrixHeight; j++) {
      leds[XY(i, j)] = CHSV(noise[j][i], 255, noise[i][j]);
    }
  }
  FastLED.show();
}

void performEffects_14() {
    preformCarnavalEffect();
}


#endif

/*void setup() {
  FastLED.addLeds<WS2812B, 5, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);

  x = random16();
  y = random16();
  z = random16();
}*/

//void loop() {
  //preformCarnavalEffect();
//}


