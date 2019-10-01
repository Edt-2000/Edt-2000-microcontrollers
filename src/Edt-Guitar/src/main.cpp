#include <GuitarApp.h>

GuitarApp guitarApp = GuitarApp("nEDTwerk", "ChillenInJeSjon", IPAddress(10, 0, 0, 20), (uint32_t)0, IPAddress(10, 0, 0, 200), 12345);

void setup()
{
  Serial.begin(115200);
  guitarApp.setup(5, LOW);
}

void loop()
{
  guitarApp.loop();
}