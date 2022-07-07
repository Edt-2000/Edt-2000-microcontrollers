#include "smokeApp.h"

SmokeApp smokeApp = SmokeApp(
    "SmokeApp1",
    IPAddress(10, 0, 0, 165),
    IPAddress(10, 0, 0, 1),
    IPAddress(255, 0, 0, 0),
    IPAddress(10, 0, 0, 255),
    12345);

void setup()
{
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(5, LOW);
  digitalWrite(12, LOW);

  Serial.begin(115200);
  smokeApp.setup(5, HIGH);
}

void loop()
{
  smokeApp.loop();
}