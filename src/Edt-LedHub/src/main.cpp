#include <Arduino.h>

bool on = true;

void setup() {
  pinMode(1, OUTPUT);
}

void loop() {
  digitalWrite(1, on);

  on = !on;

  delay(1000);
}