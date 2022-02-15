#include "ledApp.h"

LedApp ledApp = LedApp("LedApp1", 
  IPAddress(10, 0, 0, 20), 
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