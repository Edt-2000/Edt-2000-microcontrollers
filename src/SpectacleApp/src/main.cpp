#include "leds.h"
#include "spectacleApp.h"

Leds SpectacleLeds;

SpectacleApp spectacleApp = SpectacleApp(
    "SpectacleApp1",
    IPAddress(10, 0, 0, 99),
    IPAddress(10, 0, 0, 1),
    IPAddress(255, 0, 0, 0),
    IPAddress(10, 0, 0, 255),
    12345);

void setup()
{
  pinMode(13, OUTPUT);

  digitalWrite(13, LOW);

  delay(1000);

  Serial.begin(9600);
  spectacleApp.setup(13, HIGH);
}

void loop()
{
  spectacleApp.loop();
}
