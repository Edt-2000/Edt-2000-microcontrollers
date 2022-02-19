#include "dmxApp.h"

DmxApp application = DmxApp(
	"DmxApp",
	IPAddress(10, 0, 0. 30),
	IPAddress(255, 0, 0, 0),
	IPAddress(10, 0, 0, 255),
	12345);

void setup()
{
	application.setup();
}

void loop()
{
	application.loop();
}