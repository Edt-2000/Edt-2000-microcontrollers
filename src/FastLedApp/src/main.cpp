#include "ledApp.h"

// TODO: deploy to 3 ESP32s

LedApp ledApp = LedApp(
    "LedApp3",
    IPAddress(10, 0, 0, 22),
    IPAddress(255, 0, 0, 0),
    IPAddress(10, 0, 0, 255),
    12345);

void setup()
{
  Serial.begin(115200);
  ledApp.setup(33, LOW);
}

void loop()
{
  ledApp.loop();
}