#include "fastLedApp.h"

#define FASTLED_FORCE_SOFTWARE_SPI

// TODO: deploy to 3 ESP32s

FastLedApp fastLedApp = FastLedApp(
    "LedApp3",
    IPAddress(10, 0, 0, 22),
    IPAddress(255, 0, 0, 0),
    IPAddress(10, 0, 0, 255),
    12345);

void setup()
{
  Serial.begin(115200);
  fastLedApp.setup(33, LOW);
}

void loop()
{
  fastLedApp.loop();
}