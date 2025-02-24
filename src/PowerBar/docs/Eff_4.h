
/////////COPS_2//////
 
#ifndef EFFECT_4_H
#define EFFECT_4_H


#include "FastLED.h"

#define NUM_LEDS 640
#define DATA_PIN 5

extern CRGB leds[];

int delayTime_Cops_2 = 100;

// templates
CRGB C2_LEDs_S1[NUM_LEDS];
CRGB C2_LEDs_S2[NUM_LEDS];
CRGB C2_LEDs_S3[NUM_LEDS];

// Define an array of LED indices for red LEDs //COPS 2 EFFECT//
int C2_LED_S1Indices[] = { 81, 88, 96, 104, 113, 114, 107, 99, 91, 84, 85, 94, 102, 110, 117,
                           144, 145, 146, 147, 148, 149, 134, 142, 150, 158, 166,
                           176, 177, 178, 179, 180, 181, 182, 190, 198, 206, 213, 212, 203, 195, 187, 194, 201, 208,
                           225, 226, 227, 228, 229, 238, 246, 254, 261, 260, 259, 258, 257, 248, 240, 232,
                           272, 273, 274, 275, 276, 277, 278, 286, 294, 302, 309, 308, 299, 291, 283, 306, 305, 296, 288, 280,
                           321, 322, 323, 324, 325, 334, 342, 350, 357, 356, 355, 354, 353, 344, 336, 328,
                           401, 392, 384, 376, 369, 370, 371, 372, 373, 382, 390, 398, 405,
                           417, 418, 419, 420, 421, 430, 438, 446, 453, 452, 451, 450, 449, 440, 432, 424,
                           464, 465, 466, 467, 468, 469, 470, 478, 486, 494, 501, 500, 491, 483, 475,
                           513, 520, 528, 536, 545, 546, 539, 531, 523, 516, 517, 526, 534, 542, 549 };
int C2_numLEDs_S1 = sizeof(C2_LED_S1Indices) / sizeof(C2_LED_S1Indices[0]);

// Define an array of LED indices for the 2e set of blue LEDs //COPS 2 EFFECT//
int C2_LED_S2Indices[] = { 90, 97, 105, 113, 122, 123, 116, 108, 100, 93, 94, 103, 111, 119, 126,
                           153, 154, 155, 156, 157, 158, 143, 151, 159, 167, 175,
                           185, 186, 187, 188, 189, 190, 191, 199, 207, 215, 222, 221, 212, 204, 196, 203, 210, 217,
                           234, 235, 236, 237, 238, 247, 255, 263, 270, 269, 268, 267, 266, 257, 249, 241,
                           281, 282, 283, 284, 285, 286, 287, 295, 303, 311, 318, 317, 308, 300, 292, 315, 314, 305, 297, 289,
                           330, 331, 332, 333, 334, 343, 351, 359, 366, 365, 364, 363, 362, 353, 345, 337,
                           410, 401, 393, 385, 378, 379, 380, 381, 382, 391, 399, 407, 414,
                           426, 427, 428, 429, 430, 439, 447, 455, 462, 461, 460, 459, 458, 449, 441, 433,
                           473, 474, 475, 476, 477, 478, 479, 487, 495, 503, 510, 509, 500, 492, 484,
                           522, 529, 537, 545, 554, 555, 548, 540, 532, 525, 526, 535, 543, 551, 558 };
int C2_numLEDs_S2 = sizeof(C2_LED_S2Indices) / sizeof(C2_LED_S2Indices[0]);

// Define an array of LED indices for the 3e set of green LEDs //COPS 2 EFFECT//
int C2_LED_S3Indices[] = { 82, 89, 97, 105, 114, 115, 108, 100, 92, 85, 86, 95, 103, 111, 118,
                           145, 146, 147, 148, 149, 150, 135, 143, 151, 159, 167,
                           177, 178, 179, 180, 181, 182, 183, 191, 199, 207, 214, 213, 204, 196, 188, 195, 202, 209,
                           226, 227, 228, 229, 230, 239, 247, 255, 262, 261, 260, 259, 258, 249, 241, 233,
                           273, 274, 275, 276, 277, 278, 279, 287, 295, 303, 310, 309, 300, 292, 284, 307, 306, 297, 289, 281,
                           322, 323, 324, 325, 326, 335, 343, 351, 358, 357, 356, 355, 354, 345, 337, 329,
                           402, 393, 385, 377, 370, 371, 372, 373, 374, 383, 391, 399, 406,
                           418, 419, 420, 421, 422, 431, 439, 447, 454, 453, 452, 451, 450, 441, 433, 425,
                           465, 466, 467, 468, 469, 470, 471, 479, 487, 495, 502, 501, 492, 484, 476,
                           514, 521, 529, 537, 546, 547, 540, 532, 524, 517, 518, 527, 535, 543, 550 };
int C2_numLEDs_S3 = sizeof(C2_LED_S3Indices) / sizeof(C2_LED_S3Indices[0]);

//COPS2 EFFECT//
void Cops4_Effect(CRGB *LEDs, int *indices, int numLEDs, CRGB color) {
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  for (int i = 0; i < numLEDs; i++) {
    LEDs[indices[i]] = color;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = LEDs[i];
  }

  FastLED.show();
  delay(delayTime_Cops_2);

  for (int i = 0; i < NUM_LEDS; i++) {
    LEDs[i] = CRGB::Black;
  }
}
//COPS2 EFFECT//
void performEffectsCops_4() {
  Cops4_Effect(C2_LEDs_S1, C2_LED_S1Indices, C2_numLEDs_S1, CRGB(255, 0, 0));  // Red color
  Cops4_Effect(C2_LEDs_S2, C2_LED_S2Indices, C2_numLEDs_S2, CRGB(0, 0, 255));  // Blue color
  Cops4_Effect(C2_LEDs_S1, C2_LED_S1Indices, C2_numLEDs_S1, CRGB(255, 0, 0));  // Red color
  Cops4_Effect(C2_LEDs_S3, C2_LED_S3Indices, C2_numLEDs_S3, CRGB(0, 255, 0));  // Green color
}

void performEffects_4(){
    performEffectsCops_4();
}


#endif