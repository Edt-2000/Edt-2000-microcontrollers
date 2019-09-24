#include <GuitarApp.h>

GuitarApp guitarApp = GuitarApp("WeAreTriple-Guest", "tripleinternet", (uint32_t)0, (uint32_t)0, IPAddress(10, 52, 1, 129), 12345);

void setup()
{
  Serial.begin(115200);
  guitarApp.setup(5, LOW);
}

void loop()
{
  guitarApp.loop();
}