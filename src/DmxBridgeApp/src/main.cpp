#include "dmxApp.h"

// TODO: deploy to 2 ESP32s

auto oscAddress = "/R3";

DmxApp dmxApp = DmxApp(
	"DmxApp1",
	oscAddress,
	IPAddress(10, 0, 0, 30),
	IPAddress(255, 0, 0, 0),
	IPAddress(10, 0, 0, 255),
	12345);

void setup()
{
	EEPROM.begin(255);
	Serial.begin(115200);
	Drivers::Dmx::DmxSerial::Initialize(DmxDirection::output);
	dmxApp.setup(33, LOW);
}

void loop()
{
	dmxApp.loop();
}