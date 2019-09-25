#include <DrumApp.h>

uint8_t macAddress[6] = {0x00, 0x12, 0x34, 0x56, 0x78, 0xAA};

DrumApp drumApp = DrumApp(
    macAddress,
    IPAddress(10, 0, 0, 20),
    IPAddress(255, 0, 0, 0),
    IPAddress(10, 0, 0, 255),
    12345);

void setup()
{
  Serial.begin(115200);
  drumApp.setup(13, LOW);
}

void loop()
{
  drumApp.loop();
}