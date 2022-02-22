#include "dmxApp.h"

uint8_t macAddress[6] =  { 0x00, 0x00, 0x12, 0x34, 0x56, 0xA2 };
auto oscAddress = "/R3";

DmxApp application = DmxApp(
	"DmxApp",
	oscAddress,
	macAddress,
	IPAddress(10, 0, 0, 30),
	IPAddress(255, 0, 0, 0),
	IPAddress(10, 0, 0, 255),
	12345);

void setup()
{
	application.setup(13, 0);
}

void loop()
{
	application.loop();
}