#include <ledApp.hpp>

LedApp ledApp = LedApp("LedApp1");

void setup()
{
  ledApp.setup(0, 0);
}

void loop()
{
  ledApp.loop();
}