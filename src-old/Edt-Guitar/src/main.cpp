#include <GuitarApp.h>

GuitarApp guitarApp = GuitarApp("nEDTwerk", "ChillenInJeSjon", (uint32_t)0, (uint32_t)0, IPAddress(10, 0, 0, 255), 12345);

void setup()
{
  Serial.begin(115200);
  guitarApp.setup(5, LOW);
}

void loop()
{
  guitarApp.loop();
}