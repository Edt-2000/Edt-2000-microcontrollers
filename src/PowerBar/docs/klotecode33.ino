#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include <FastLED.h>
#include <EEPROM.h>
#include "Eff_1.h"
#include "Eff_2.h"
#include "Eff_3.h"
#include "Eff_4.h"
#include "Eff_5.h"
#include "Eff_6.h"
#include "Eff_7.h"
#include "Eff_8.h"
#include "Eff_9.h"
#include "Eff_10.h"
#include "Eff_11.h"
#include "Eff_12.h"
#include "Eff_13.h"
#include "Eff_14.h"
#include "Eff_15.h"
#include "Eff_16.h"
#include "Eff_17.h"
#include "Eff_18.h"
#include "Eff_19.h"
#include "Eff_20.h"
#include "Eff_21.h"
#include "Eff_22.h"
#include "Eff_23.h"
#include "Eff_24.h"
#include "Eff_25.h"
#include "Eff_26.h"
#include "Eff_27.h"
#include "Eff_28.h"
#include "Eff_29.h"
#include "Eff_30.h"
#include "Eff_31.h"
#include "Eff_32.h"
#include "Eff_33.h"
#include "Eff_34.h"
//#include "Eff_35.h"
#include "html.h"

#define NUM_LEDS 640
#define MATRIX_SIZE 64   // LEDs per matrix
#define NUM_MATRICES 10  // Aantal matrices



int brightnessLevel = 50;

bool Effect_1Active = false;
bool Effect_2Active = false;
bool Effect_3Active = false;
bool Effect_4Active = false;
bool Effect_5Active = false;
bool Effect_6Active = false;
bool Effect_7Active = false;
bool Effect_8Active = false;
bool Effect_9Active = false;
bool Effect_10Active = false;
bool Effect_11Active = false;
bool Effect_12Active = false;
bool Effect_13Active = false;
bool Effect_14Active = false;
bool Effect_15Active = false;
bool Effect_16Active = false;
bool Effect_17Active = false;
bool Effect_18Active = false;
bool Effect_19Active = false;
bool Effect_20Active = false;
bool Effect_21Active = false;
bool Effect_22Active = false;
bool Effect_23Active = false;
bool Effect_24Active = false;
bool Effect_25Active = false;
bool Effect_26Active = false;
bool Effect_27Active = false;
bool Effect_28Active = false;
bool Effect_29Active = false;
bool Effect_30Active = false;
bool Effect_31Active = false;
bool Effect_32Active = false;
bool Effect_33Active = false;
bool Effect_34Active = false;


const char *ssid = "STROBOOS";
const char *password = "80208044111";

//CRGB leds[640];  // Aanpassen aan het aantal WS2812B-leds dat je hebt
CRGB leds[NUM_LEDS];


AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

enum EffectState {
  EFFECT_1_OFF,
  EFFECT_1_ON,
  EFFECT_2_OFF,
  EFFECT_2_ON,
  EFFECT_3_OFF,
  EFFECT_3_ON,
  EFFECT_4_OFF,
  EFFECT_4_ON,
  EFFECT_5_OFF,
  EFFECT_5_ON,
  EFFECT_6_OFF,
  EFFECT_6_ON,
  EFFECT_7_OFF,
  EFFECT_7_ON,
  EFFECT_8_OFF,
  EFFECT_8_ON,
  EFFECT_9_OFF,
  EFFECT_9_ON,
  EFFECT_10_OFF,
  EFFECT_10_ON,
  EFFECT_11_OFF,
  EFFECT_11_ON,
  EFFECT_12_OFF,
  EFFECT_12_ON,
  EFFECT_13_OFF,
  EFFECT_13_ON,
  EFFECT_14_OFF,
  EFFECT_14_ON,
  EFFECT_15_OFF,
  EFFECT_15_ON,
  EFFECT_16_OFF,
  EFFECT_16_ON,
  EFFECT_17_OFF,
  EFFECT_17_ON,
  EFFECT_18_OFF,
  EFFECT_18_ON,
  EFFECT_19_OFF,
  EFFECT_19_ON,
  EFFECT_20_OFF,
  EFFECT_20_ON,
  EFFECT_21_OFF,
  EFFECT_21_ON,
  EFFECT_22_OFF,
  EFFECT_22_ON,
  EFFECT_23_OFF,
  EFFECT_23_ON,
  EFFECT_24_OFF,
  EFFECT_24_ON,
  EFFECT_25_OFF,
  EFFECT_25_ON,
  EFFECT_26_OFF,
  EFFECT_26_ON,
  EFFECT_27_OFF,
  EFFECT_27_ON,
  EFFECT_28_OFF,
  EFFECT_28_ON,
  EFFECT_29_OFF,
  EFFECT_29_ON,
  EFFECT_30_OFF,
  EFFECT_30_ON,
  EFFECT_31_OFF,
  EFFECT_31_ON,
  EFFECT_32_OFF,
  EFFECT_32_ON,
  EFFECT_33_OFF,
  EFFECT_33_ON,
  EFFECT_34_OFF,
  EFFECT_34_ON


};

EffectState currentEffect = EFFECT_1_OFF;


bool effect2Enabled() { return currentEffect == EFFECT_2_ON; }
bool effect5Enabled() { return currentEffect == EFFECT_5_ON; }
bool effect15Enabled() { return currentEffect == EFFECT_15_ON; }
bool effect20Enabled() { return currentEffect == EFFECT_20_ON; }
bool effect21Enabled() { return currentEffect == EFFECT_21_ON; }
bool effect24Enabled() { return currentEffect == EFFECT_24_ON; }
bool effect25Enabled() { return currentEffect == EFFECT_25_ON; }
bool effect26Enabled() { return currentEffect == EFFECT_26_ON; }
bool effect27Enabled() { return currentEffect == EFFECT_27_ON; }
bool effect28Enabled() { return currentEffect == EFFECT_28_ON; }
bool effect29Enabled() { return currentEffect == EFFECT_29_ON; }
bool effect30Enabled() { return currentEffect == EFFECT_30_ON; }
bool effect31Enabled() { return currentEffect == EFFECT_31_ON; }
bool effect32Enabled() { return currentEffect == EFFECT_32_ON; }
bool effect33Enabled() { return currentEffect == EFFECT_33_ON; }
bool effect34Enabled() { return currentEffect == EFFECT_34_ON; }


// EEPROM-adressen voor knopstatussen
const int EFFECT_1_BUTTON_EEPROM_ADDR = 0;
const int EFFECT_2_BUTTON_EEPROM_ADDR = 1;
const int EFFECT_3_BUTTON_EEPROM_ADDR = 2;
const int EFFECT_4_BUTTON_EEPROM_ADDR = 3;
const int EFFECT_5_BUTTON_EEPROM_ADDR = 4;
const int EFFECT_6_BUTTON_EEPROM_ADDR = 5;
const int EFFECT_7_BUTTON_EEPROM_ADDR = 6;
const int EFFECT_8_BUTTON_EEPROM_ADDR = 7;
const int EFFECT_9_BUTTON_EEPROM_ADDR = 8;
const int EFFECT_10_BUTTON_EEPROM_ADDR = 9;
const int EFFECT_11_BUTTON_EEPROM_ADDR = 10;
const int EFFECT_12_BUTTON_EEPROM_ADDR = 11;
const int EFFECT_13_BUTTON_EEPROM_ADDR = 12;
const int EFFECT_14_BUTTON_EEPROM_ADDR = 13;
const int EFFECT_15_BUTTON_EEPROM_ADDR = 14;
const int EFFECT_16_BUTTON_EEPROM_ADDR = 15;
const int EFFECT_17_BUTTON_EEPROM_ADDR = 16;
const int EFFECT_18_BUTTON_EEPROM_ADDR = 17;
const int EFFECT_19_BUTTON_EEPROM_ADDR = 18;
const int EFFECT_20_BUTTON_EEPROM_ADDR = 19;
const int EFFECT_21_BUTTON_EEPROM_ADDR = 20;
const int EFFECT_22_BUTTON_EEPROM_ADDR = 21;
const int EFFECT_23_BUTTON_EEPROM_ADDR = 22;
const int EFFECT_24_BUTTON_EEPROM_ADDR = 23;
const int EFFECT_25_BUTTON_EEPROM_ADDR = 24;
const int EFFECT_26_BUTTON_EEPROM_ADDR = 25;
const int EFFECT_27_BUTTON_EEPROM_ADDR = 26;
const int EFFECT_28_BUTTON_EEPROM_ADDR = 27;
const int EFFECT_29_BUTTON_EEPROM_ADDR = 28;
const int EFFECT_30_BUTTON_EEPROM_ADDR = 29;
const int EFFECT_31_BUTTON_EEPROM_ADDR = 30;
const int EFFECT_32_BUTTON_EEPROM_ADDR = 31;
const int EFFECT_33_BUTTON_EEPROM_ADDR = 32;
const int EFFECT_34_BUTTON_EEPROM_ADDR = 33;


void toggleEffect_1() {
  if (currentEffect == EFFECT_1_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_1_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_1Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_1_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_1Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_1_ON;
    Effect_1Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_1_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_2() {
  if (currentEffect == EFFECT_2_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_2_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_2Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_2_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_2Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_2_ON;
    Effect_2Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_2_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_3() {
  if (currentEffect == EFFECT_3_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_3_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_3Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_3_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_3Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_3_ON;
    Effect_3Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_3_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_4() {
  if (currentEffect == EFFECT_4_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_4_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_4Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_4_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_4Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_4_ON;
    Effect_4Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_4_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_5() {
  if (currentEffect == EFFECT_5_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_5_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_5Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_5_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_5Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_5_ON;
    Effect_5Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_5_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_6() {
  if (currentEffect == EFFECT_6_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_6_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_6Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_6_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_6Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_6_ON;
    Effect_6Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_6_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_7() {
  if (currentEffect == EFFECT_7_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_7_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_7Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_7_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_7Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_7_ON;
    Effect_7Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_7_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_8() {
  if (currentEffect == EFFECT_8_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_8_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_8Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_8_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_8Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_8_ON;
    Effect_8Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_8_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_9() {
  if (currentEffect == EFFECT_9_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_9_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_9Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_9_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_9Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_9_ON;
    Effect_9Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_9_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_10() {
  if (currentEffect == EFFECT_10_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_10_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_10Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_10_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_10Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_10_ON;
    Effect_10Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_10_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_11() {
  if (currentEffect == EFFECT_11_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_11_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_11Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_11_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_11Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_11_ON;
    Effect_11Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_11_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_12() {
  if (currentEffect == EFFECT_12_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_12_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_12Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_12_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_12Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_12_ON;
    Effect_12Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_12_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_13() {
  if (currentEffect == EFFECT_13_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_13_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_13Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_13_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_13Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_13_ON;
    Effect_13Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_13_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_14() {
  if (currentEffect == EFFECT_14_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_14_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_14Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_14_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_14Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_14_ON;
    Effect_14Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_14_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_15() {
  if (currentEffect == EFFECT_15_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_15_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_15Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_15_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_15Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_15_ON;
    Effect_15Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_15_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_16() {
  if (currentEffect == EFFECT_16_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_16_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_16Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_16_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_16Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_16_ON;
    Effect_16Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_16_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_17() {
  if (currentEffect == EFFECT_17_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_17_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_17Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_17_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_17Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_17_ON;
    Effect_17Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_17_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_18() {
  if (currentEffect == EFFECT_18_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_18_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_18Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_18_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_18Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_18_ON;
    Effect_18Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_18_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_19() {
  if (currentEffect == EFFECT_19_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_19_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_19Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_19_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_19Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_19_ON;
    Effect_19Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_19_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_20() {
  if (currentEffect == EFFECT_20_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_20_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_20Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_20_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_20Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_20_ON;
    Effect_20Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_20_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_21() {
  if (currentEffect == EFFECT_21_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_21_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_21Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_21_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_21Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_21_ON;
    Effect_21Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_21_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_22() {
  if (currentEffect == EFFECT_22_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_22_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_22Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_22_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_22Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_22_ON;
    Effect_22Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_22_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_23() {
  if (currentEffect == EFFECT_23_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_23_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_23Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_23_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_23Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_23_ON;
    Effect_23Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_23_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_24() {
  if (currentEffect == EFFECT_24_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_24_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_24Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_24_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_24Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_24_ON;
    Effect_24Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_24_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_25() {
  if (currentEffect == EFFECT_25_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_25_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_25Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_25_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_25Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_25_ON;
    Effect_25Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_25_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_26() {
  if (currentEffect == EFFECT_26_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_26_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_26Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_26_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_26Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_26_ON;
    Effect_26Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_26_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_27() {
  if (currentEffect == EFFECT_27_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_27_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_27Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_27_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_27Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_27_ON;
    Effect_27Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_27_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_28() {
  if (currentEffect == EFFECT_28_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_28_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_28Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_28_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_28Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_28_ON;
    Effect_28Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_28_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_29() {
  if (currentEffect == EFFECT_29_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_29_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_29Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_29_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_29Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_29_ON;
    Effect_29Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_29_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_30() {
  if (currentEffect == EFFECT_30_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_30_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_30Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_30_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_30Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_30_ON;
    Effect_30Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_30_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_31() {
  if (currentEffect == EFFECT_31_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_31_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_31Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_31_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_31Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_31_ON;
    Effect_31Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_31_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_32() {
  if (currentEffect == EFFECT_32_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_32_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_32Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_32_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_32Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_32_ON;
    Effect_32Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_32_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_33() {
  if (currentEffect == EFFECT_33_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_33_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_33Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_33_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_33Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_33_ON;
    Effect_33Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_33_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}

void toggleEffect_34() {
  if (currentEffect == EFFECT_34_ON) {
    // Als het huidige effect effect is, schakel het uit
    currentEffect = EFFECT_34_OFF;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
    Effect_34Active = false;                       // Stop het effect
  } else {
    // Als het huidige effect niet effect is, schakel het uit
    if (currentEffect != EFFECT_34_ON) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Schakel alle LEDs uit
      Effect_34Active = false;                       // Stop het effect
      notifyClients();                            // Stuur de status naar de clients
    }

    // Schakel Magenta in
    currentEffect = EFFECT_34_ON;
    Effect_34Active = true;  // Start het effect
  }

  EEPROM.write(EFFECT_34_BUTTON_EEPROM_ADDR, currentEffect);
  FastLED.show();
  notifyClients();
}



void notifyClients() {
  ws.textAll(String(currentEffect == EFFECT_1_ON)
   + "," + String(currentEffect == EFFECT_2_ON)
   + "," + String(currentEffect == EFFECT_3_ON)
   + "," + String(currentEffect == EFFECT_4_ON)
   + "," + String(currentEffect == EFFECT_5_ON)
   + "," + String(currentEffect == EFFECT_6_ON)
   + "," + String(currentEffect == EFFECT_7_ON)
   + "," + String(currentEffect == EFFECT_8_ON)
   + "," + String(currentEffect == EFFECT_9_ON)
   + "," + String(currentEffect == EFFECT_10_ON)
   + "," + String(currentEffect == EFFECT_11_ON)
   + "," + String(currentEffect == EFFECT_12_ON)
   + "," + String(currentEffect == EFFECT_13_ON)
   + "," + String(currentEffect == EFFECT_14_ON)
   + "," + String(currentEffect == EFFECT_15_ON)
   + "," + String(currentEffect == EFFECT_16_ON)
   + "," + String(currentEffect == EFFECT_17_ON)
   + "," + String(currentEffect == EFFECT_18_ON)
   + "," + String(currentEffect == EFFECT_19_ON)
   + "," + String(currentEffect == EFFECT_20_ON)
   + "," + String(currentEffect == EFFECT_21_ON)
   + "," + String(currentEffect == EFFECT_22_ON)
   + "," + String(currentEffect == EFFECT_23_ON)
   + "," + String(currentEffect == EFFECT_24_ON)
   + "," + String(currentEffect == EFFECT_25_ON)
   + "," + String(currentEffect == EFFECT_26_ON)
   + "," + String(currentEffect == EFFECT_27_ON)
   + "," + String(currentEffect == EFFECT_28_ON)
   + "," + String(currentEffect == EFFECT_29_ON)
   + "," + String(currentEffect == EFFECT_30_ON)
   + "," + String(currentEffect == EFFECT_31_ON)
   + "," + String(currentEffect == EFFECT_32_ON)
   + "," + String(currentEffect == EFFECT_33_ON)
   + "," + String(currentEffect == EFFECT_34_ON)
   + "," + String(brightnessLevel));
}

void adjustBrightness(String direction) {
  if (direction == "+") {
    brightnessLevel = min(100, brightnessLevel + 10);  // Verhoog de helderheid met 10, max 100
  } else if (direction == "-") {
    brightnessLevel = max(0, brightnessLevel - 10);  // Verlaag de helderheid met 10, min 0
  }

  // Pas hier de helderheid aan op basis van de 'brightnessLevel'-waarde
  FastLED.setBrightness(map(brightnessLevel, 0, 100, 0, 255));

  notifyClients();

  FastLED.show();
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char *)data, "toggleEffect_1") == 0) {
      toggleEffect_1();
    } else if (strcmp((char *)data, "toggleEffect_2") == 0) {
      toggleEffect_2();
    } else if (strcmp((char *)data, "toggleEffect_3") == 0) {
      toggleEffect_3();
    } else if (strcmp((char *)data, "toggleEffect_4") == 0) {
      toggleEffect_4();
    } else if (strcmp((char *)data, "toggleEffect_5") == 0) {
      toggleEffect_5();  
     } else if (strcmp((char *)data, "toggleEffect_6") == 0) {
      toggleEffect_6(); 
    } else if (strcmp((char *)data, "toggleEffect_7") == 0) {
      toggleEffect_7(); 
    } else if (strcmp((char *)data, "toggleEffect_8") == 0) {
      toggleEffect_8(); 
    } else if (strcmp((char *)data, "toggleEffect_9") == 0) {
      toggleEffect_9(); 
    } else if (strcmp((char *)data, "toggleEffect_10") == 0) {
      toggleEffect_10(); 
    } else if (strcmp((char *)data, "toggleEffect_11") == 0) {
      toggleEffect_11(); 
    } else if (strcmp((char *)data, "toggleEffect_12") == 0) {
      toggleEffect_12(); 
    } else if (strcmp((char *)data, "toggleEffect_13") == 0) {
      toggleEffect_13(); 
    } else if (strcmp((char *)data, "toggleEffect_14") == 0) {
      toggleEffect_14(); 
    } else if (strcmp((char *)data, "toggleEffect_15") == 0) {
      toggleEffect_15(); 
    } else if (strcmp((char *)data, "toggleEffect_16") == 0) {
      toggleEffect_16(); 
    } else if (strcmp((char *)data, "toggleEffect_17") == 0) {
      toggleEffect_17();
    } else if (strcmp((char *)data, "toggleEffect_18") == 0) {
      toggleEffect_18();
    } else if (strcmp((char *)data, "toggleEffect_19") == 0) {
      toggleEffect_19(); 
    } else if (strcmp((char *)data, "toggleEffect_20") == 0) {
      toggleEffect_20(); 
    } else if (strcmp((char *)data, "toggleEffect_21") == 0) {
      toggleEffect_21(); 
    } else if (strcmp((char *)data, "toggleEffect_22") == 0) {
      toggleEffect_22(); 
    } else if (strcmp((char *)data, "toggleEffect_23") == 0) {
      toggleEffect_23(); 
    } else if (strcmp((char *)data, "toggleEffect_24") == 0) {
      toggleEffect_24(); 
    } else if (strcmp((char *)data, "toggleEffect_25") == 0) {
      toggleEffect_25();
    } else if (strcmp((char *)data, "toggleEffect_26") == 0) {
      toggleEffect_26();  
    } else if (strcmp((char *)data, "toggleEffect_27") == 0) {
      toggleEffect_27();
    } else if (strcmp((char *)data, "toggleEffect_28") == 0) {
      toggleEffect_28(); 
    } else if (strcmp((char *)data, "toggleEffect_29") == 0) {
      toggleEffect_29(); 
    } else if (strcmp((char *)data, "toggleEffect_30") == 0) {
      toggleEffect_30();
    } else if (strcmp((char *)data, "toggleEffect_31") == 0) {
      toggleEffect_31();
    } else if (strcmp((char *)data, "toggleEffect_32") == 0) {
      toggleEffect_32();
    } else if (strcmp((char *)data, "toggleEffect_33") == 0) {
      toggleEffect_33();
    } else if (strcmp((char *)data, "toggleEffect_34") == 0) {
      toggleEffect_34();                                                                                                                                
    } else if (strcmp((char *)data, "adjustBrightness+") == 0) {
      adjustBrightness("+");
    } else if (strcmp((char *)data, "adjustBrightness-") == 0) {
      adjustBrightness("-");
    }
  }
}


void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String &var) {
  Serial.println(var);
  if (var == "EFFECT_1_STATE") {
    return currentEffect == EFFECT_1_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_2_STATE") {
    return currentEffect == EFFECT_2_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_3_STATE") {
    return currentEffect == EFFECT_3_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_4_STATE") {
    return currentEffect == EFFECT_4_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_5_STATE") {
    return currentEffect == EFFECT_5_ON ? "ON" : "OFF";  
  } else if (var == "EFFECT_6_STATE") {
    return currentEffect == EFFECT_6_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_7_STATE") {
    return currentEffect == EFFECT_7_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_8_STATE") {
    return currentEffect == EFFECT_8_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_9_STATE") {
    return currentEffect == EFFECT_9_ON ? "ON" : "OFF";  
  } else if (var == "EFFECT_10_STATE") {
    return currentEffect == EFFECT_10_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_11_STATE") {
    return currentEffect == EFFECT_11_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_12_STATE") {
    return currentEffect == EFFECT_12_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_13_STATE") {
    return currentEffect == EFFECT_13_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_14_STATE") {
    return currentEffect == EFFECT_14_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_15_STATE") {
    return currentEffect == EFFECT_15_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_16_STATE") {
    return currentEffect == EFFECT_16_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_17_STATE") {
    return currentEffect == EFFECT_17_ON ? "ON" : "OFF"; 
  } else if (var == "EFFECT_18_STATE") {
    return currentEffect == EFFECT_18_ON ? "ON" : "OFF"; 
  } else if (var == "EFFECT_19_STATE") {
    return currentEffect == EFFECT_19_ON ? "ON" : "OFF"; 
  } else if (var == "EFFECT_20_STATE") {
    return currentEffect == EFFECT_20_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_21_STATE") {
    return currentEffect == EFFECT_21_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_22_STATE") {
    return currentEffect == EFFECT_22_ON ? "ON" : "OFF";  
  } else if (var == "EFFECT_23_STATE") {
    return currentEffect == EFFECT_23_ON ? "ON" : "OFF";  
  } else if (var == "EFFECT_24_STATE") {
    return currentEffect == EFFECT_24_ON ? "ON" : "OFF";  
  } else if (var == "EFFECT_25_STATE") {
    return currentEffect == EFFECT_25_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_26_STATE") {
    return currentEffect == EFFECT_26_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_27_STATE") {
    return currentEffect == EFFECT_27_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_28_STATE") {
    return currentEffect == EFFECT_28_ON ? "ON" : "OFF";  
  } else if (var == "EFFECT_29_STATE") {
    return currentEffect == EFFECT_29_ON ? "ON" : "OFF";  
  } else if (var == "EFFECT_30_STATE") {
    return currentEffect == EFFECT_30_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_31_STATE") {
    return currentEffect == EFFECT_31_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_32_STATE") {
    return currentEffect == EFFECT_32_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_33_STATE") {
    return currentEffect == EFFECT_33_ON ? "ON" : "OFF";
  } else if (var == "EFFECT_34_STATE") {
    return currentEffect == EFFECT_34_ON ? "ON" : "OFF";             
  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Init LED strip
  FastLED.addLeds<WS2812B, 5, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  //Nodig voor effect_17(fire)/////
  setupMatrix();

  //Nodig voor Carnaval Effect
  x = random16();
  y = random16();
  z = random16();  


  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Vast IP-adres instellen
  IPAddress staticIP(192, 168, 142, 101);  // Je gewenste IP-adres
  IPAddress gateway(192, 168, 142, 1);     // Het gateway-adres van je netwerk
  IPAddress subnet(255, 255, 255, 0);      // Het subnetmasker van je netwerk

  WiFi.config(staticIP, gateway, subnet);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();

  // Herstel de laatst bekende status van de knoppen
  currentEffect = (EffectState)EEPROM.read(EFFECT_1_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_1_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_1_ON:
      performEffects_1();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_2_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_2_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_2_ON:
      performEffects_2();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_3_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_3_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_3_ON:
      performEffects_3();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_4_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_4_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_4_ON:
      performEffects_4();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_5_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_5_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_5_ON:
      performEffects_5();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_6_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_6_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_6_ON:
      //performEffects_6();
      strobe1Effect(strobe1_Color, strobe1_OnTime, strobe1_OffTime);
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_7_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_7_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_7_ON:
      performEffects_7();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_8_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_8_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_8_ON:
      performEffects_8();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_9_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_9_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_9_ON:
      performEffects_9();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_10_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_10_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_10_ON:
      performEffects_10();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_11_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_11_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_11_ON:
      performEffects_11();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_12_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_12_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_12_ON:
      performEffects_12();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_13_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_13_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_13_ON:
      performEffects_13();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_14_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_14_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_14_ON:
      performEffects_14();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_15_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_15_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_15_ON:
      performEffects_15();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_16_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_16_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_16_ON:
      performEffects_16();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_17_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_17_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_17_ON:
      performEffects_17();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_18_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_18_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_18_ON:
      performEffects_18();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_19_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_19_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_19_ON:
      performEffects_19();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_20_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_20_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_20_ON:
      performEffects_20();
      break;
  }
  currentEffect = (EffectState)EEPROM.read(EFFECT_21_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_21_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_21_ON:
      performEffects_21();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_22_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_22_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_22_ON:
      performEffects_22();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_23_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_23_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_23_ON:
      performEffects_23();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_24_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_24_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_24_ON:
      performEffects_24();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_25_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_25_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_25_ON:
      performEffects_25();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_26_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_26_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_26_ON:
      performEffects_26();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_27_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_27_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_27_ON:
      performEffects_27();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_28_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_28_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_28_ON:
      performEffects_28();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_29_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_29_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_29_ON:
      performEffects_29();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_30_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_30_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_30_ON:
      performEffects_30();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_31_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_31_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_31_ON:
      performEffects_31();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_32_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_32_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_32_ON:
      performEffects_32();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_33_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_33_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_33_ON:
      performEffects_33();
      break;
  }

  currentEffect = (EffectState)EEPROM.read(EFFECT_34_BUTTON_EEPROM_ADDR);
  switch (currentEffect) {
    case EFFECT_34_OFF:
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case EFFECT_34_ON:
      performEffects_34();
      break;
  }


  FastLED.show();
}



void loop() {
  ws.cleanupClients();

  // Zet alle LED's uit als geen van de effecten actief is
  if (!Effect_1Active
   && !Effect_2Active
   && !Effect_3Active
   && !Effect_4Active
   && !Effect_5Active
   && !Effect_6Active
   && !Effect_7Active
   && !Effect_8Active
   && !Effect_9Active
   && !Effect_10Active
   && !Effect_11Active
   && !Effect_12Active
   && !Effect_13Active
   && !Effect_14Active
   && !Effect_15Active
   && !Effect_16Active
   && !Effect_17Active
   && !Effect_18Active
   && !Effect_19Active
   && !Effect_20Active
   && !Effect_21Active
   && !Effect_22Active
   && !Effect_23Active
   && !Effect_24Active
   && !Effect_25Active
   && !Effect_26Active
   && !Effect_27Active
   && !Effect_28Active
   && !Effect_29Active
   && !Effect_30Active
   && !Effect_31Active
   && !Effect_32Active
   && !Effect_33Active
   && !Effect_34Active) {
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
    FastLED.show();  // Voeg deze regel toe om de LED's uit te schakelen
  }

  switch (currentEffect) {
    case EFFECT_1_ON:
      Effect_1Active = true;
      notifyClients();
      performEffects_1();
      break;

    case EFFECT_2_ON:
      Effect_2Active = true;
      notifyClients();
      performEffects_2();
      break;

    case EFFECT_3_ON:
      Effect_3Active = true;
      notifyClients();
      performEffects_3();
      break;

    case EFFECT_4_ON:
      Effect_4Active = true;
      notifyClients();
      performEffects_4();
      break;

    case EFFECT_5_ON:
      Effect_5Active = true;
      notifyClients();
      performEffects_5();
      break;  

    case EFFECT_6_ON:
      Effect_6Active = true;
      notifyClients();
      performEffects_6();
      break;

    case EFFECT_7_ON:
      Effect_7Active = true;
      notifyClients();
      performEffects_7();
      break;

    case EFFECT_8_ON:
      Effect_8Active = true;
      notifyClients();
      performEffects_8();
      break;

    case EFFECT_9_ON:
      Effect_9Active = true;
      notifyClients();
      performEffects_9();
      break;

    case EFFECT_10_ON:
      Effect_10Active = true;
      notifyClients();
      performEffects_10();
      break;

    case EFFECT_11_ON:
      Effect_11Active = true;
      notifyClients();
      performEffects_11();
      break;

    case EFFECT_12_ON:
      Effect_12Active = true;
      notifyClients();
      performEffects_12();
      break;

    case EFFECT_13_ON:
      Effect_13Active = true;
      notifyClients();
      performEffects_13();
      break;

    case EFFECT_14_ON:
      Effect_14Active = true;
      notifyClients();
      performEffects_14();
      break;

    case EFFECT_15_ON:
      Effect_15Active = true;
      notifyClients();
      performEffects_15();
      break;

    case EFFECT_16_ON:
      Effect_16Active = true;
      notifyClients();
      performEffects_16();
      break;

    case EFFECT_17_ON:
      Effect_17Active = true;
      notifyClients();
      performEffects_17();
      break;

    case EFFECT_18_ON:
      Effect_18Active = true;
      notifyClients();
      performEffects_18();
      break;

    case EFFECT_19_ON:
      Effect_19Active = true;
      notifyClients();
      performEffects_19();
      break;

    case EFFECT_20_ON:
      Effect_20Active = true;
      notifyClients();
      performEffects_20();
      break;

    case EFFECT_21_ON:
      Effect_21Active = true;
      notifyClients();
      performEffects_21();
      break;

    case EFFECT_22_ON:
      Effect_22Active = true;
      notifyClients();
      performEffects_22();
      break; 

    case EFFECT_23_ON:
      Effect_23Active = true;
      notifyClients();
      performEffects_23();
      break; 

    case EFFECT_24_ON:
      Effect_24Active = true;
      notifyClients();
      performEffects_24();
      break; 

    case EFFECT_25_ON:
      Effect_25Active = true;
      notifyClients();
      performEffects_25();
      break;

    case EFFECT_26_ON:
      Effect_26Active = true;
      notifyClients();
      performEffects_26();
      break;  

    case EFFECT_27_ON:
      Effect_27Active = true;
      notifyClients();
      performEffects_27();
      break;

    case EFFECT_28_ON:
      Effect_28Active = true;
      notifyClients();
      performEffects_28();
      break;  

    case EFFECT_29_ON:
      Effect_29Active = true;
      notifyClients();
      performEffects_29();
      break;  

    case EFFECT_30_ON:
      Effect_30Active = true;
      notifyClients();
      performEffects_30();
      break;

    case EFFECT_31_ON:
      Effect_31Active = true;
      notifyClients();
      performEffects_31();
      break; 

    case EFFECT_32_ON:
      Effect_32Active = true;
      notifyClients();
      performEffects_32();
      break; 

    case EFFECT_33_ON:
      Effect_33Active = true;
      notifyClients();
      performEffects_33();
      break;

    case EFFECT_34_ON:
      Effect_34Active = true;
      notifyClients();
      performEffects_34();
      break;                


    default:
      // Als de huidige effectwaarde niet overeenkomt met een van de bovenstaande gevallen,
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      FastLED.show();

      break;
  }

  // Controleer of een ander effect actief is en zet het effect uit
  switch (currentEffect) {
    case EFFECT_1_ON:
      if (!Effect_1Active) {
        Effect_1Active = false;
        notifyClients();
      }
      break;

    case EFFECT_2_ON:
      if (!Effect_2Active) {
        Effect_2Active = false;
        notifyClients();
      }
      break;

    case EFFECT_3_ON:
      if (!Effect_3Active) {
        Effect_3Active = false;
        notifyClients();
      }
      break;

    case EFFECT_4_ON:
      if (!Effect_4Active) {
        Effect_4Active = false;
        notifyClients();
      }
      break;

    case EFFECT_5_ON:
      if (!Effect_5Active) {
        Effect_5Active = false;
        notifyClients();
      }
      break;

    case EFFECT_6_ON:
      if (!Effect_6Active) {
        Effect_6Active = false;
        notifyClients();
      }
      break;

    case EFFECT_7_ON:
      if (!Effect_7Active) {
        Effect_7Active = false;
        notifyClients();
      }
      break;

    case EFFECT_8_ON:
      if (!Effect_8Active) {
        Effect_8Active = false;
        notifyClients();
      }
      break;

    case EFFECT_9_ON:
      if (!Effect_9Active) {
        Effect_9Active = false;
        notifyClients();
      }
      break;

    case EFFECT_10_ON:
      if (!Effect_10Active) {
        Effect_10Active = false;
        notifyClients();
      }
      break;

    case EFFECT_11_ON:
      if (!Effect_11Active) {
        Effect_11Active = false;
        notifyClients();
      }
      break;

    case EFFECT_12_ON:
      if (!Effect_12Active) {
        Effect_12Active = false;
        notifyClients();
      }
      break;

    case EFFECT_13_ON:
      if (!Effect_13Active) {
        Effect_13Active = false;
        notifyClients();
      }
      break;

    case EFFECT_14_ON:
      if (!Effect_14Active) {
        Effect_14Active = false;
        notifyClients();
      }
      break;

    case EFFECT_15_ON:
      if (!Effect_15Active) {
        Effect_15Active = false;
        notifyClients();
      }
      break;

    case EFFECT_16_ON:
      if (!Effect_16Active) {
        Effect_16Active = false;
        notifyClients();
      }
      break;

    case EFFECT_17_ON:
      if (!Effect_17Active) {
        Effect_17Active = false;
        notifyClients();
      }
      break;

    case EFFECT_18_ON:
      if (!Effect_18Active) {
        Effect_18Active = false;
        notifyClients();
      }
      break;

    case EFFECT_19_ON:
      if (!Effect_19Active) {
        Effect_19Active = false;
        notifyClients();
      }
      break;

    case EFFECT_20_ON:
      if (!Effect_20Active) {
        Effect_20Active = false;
        notifyClients();
      }
      break;

    case EFFECT_21_ON:
      if (!Effect_21Active) {
        Effect_21Active = false;
        notifyClients();
      }
      break;

    case EFFECT_22_ON:
      if (!Effect_22Active) {
        Effect_22Active = false;
        notifyClients();
      }
      break;

            case EFFECT_23_ON:
      if (!Effect_23Active) {
        Effect_23Active = false;
        notifyClients();
      }
      break;         

    case EFFECT_24_ON:
      if (!Effect_24Active) {
        Effect_24Active = false;
        notifyClients();
      }
      break; 

    case EFFECT_25_ON:
      if (!Effect_25Active) {
        Effect_25Active = false;
        notifyClients();
      }
      break;

    case EFFECT_26_ON:
      if (!Effect_26Active) {
        Effect_26Active = false;
        notifyClients();
      }
      break;  

    case EFFECT_27_ON:
      if (!Effect_27Active) {
        Effect_27Active = false;
        notifyClients();
      }
      break;

    case EFFECT_28_ON:
      if (!Effect_28Active) {
        Effect_28Active = false;
        notifyClients();
      }
      break;   

    case EFFECT_29_ON:
      if (!Effect_29Active) {
        Effect_29Active = false;
        notifyClients();
      }
      break;   

    case EFFECT_30_ON:
      if (!Effect_30Active) {
        Effect_30Active = false;
        notifyClients();
      }
      break;

    case EFFECT_31_ON:
      if (!Effect_31Active) {
        Effect_31Active = false;
        notifyClients();
      }
      break;

    case EFFECT_32_ON:
      if (!Effect_32Active) {
        Effect_32Active = false;
        notifyClients();
      }
      break;

    case EFFECT_33_ON:
      if (!Effect_33Active) {
        Effect_33Active = false;
        notifyClients();
      }
      break;

    case EFFECT_34_ON:
      if (!Effect_34Active) {
        Effect_34Active = false;
        notifyClients();
      }
      break;                              

           
    default:
      // Voer hier iets uit als geen van de bovenstaande gevallen overeenkomt.
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      FastLED.show();
      break;
  }
}





