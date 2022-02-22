#pragma once

#include "core.h"

class DmxApp : public App::CoreApp
{
private:
public:
	const char *dmxAppHostname;
	uint8_t *macAddress;
	IPAddress localIp;
	IPAddress subnet;
	IPAddress broadcastIp;
	int broadcastPort;

	OSC::Arduino<1, 0> osc;
	Devices::EdtDmx dmx;
	EthernetUDP udp;

	DmxApp(const char *dmxAppHostname, 
		const char *oscAddress,
		uint8_t* macAddress, 
		IPAddress localIp, 
		IPAddress subnet, 
		IPAddress broadcastIp, 
		int broadcastPort)
		: dmxAppHostname(dmxAppHostname),
		  macAddress(macAddress),
		  localIp(localIp),
		  subnet(subnet),
		  broadcastIp(broadcastIp),
		  broadcastPort(broadcastPort),
		  dmx(Devices::EdtDmx(oscAddress)) {
		  }

	void startSetupNetwork()
	{
		
	}

	bool setupNetwork()
	{
#ifndef ETHERNET

		Serial.begin(57600);

#else
		Ethernet.begin(macAddress, localIp);

		udp.begin(broadcastPort);

#endif

		return true;
	}

	void startSetupOsc()
	{
		DMXSerial.init(DMXController);

#ifndef ETHERNET
		osc.bindStream(&Serial);
#else
		osc.bindUDP(&udp, broadcastIp, broadcastPort);
#endif
		// EthernetClient::setupUdp(broadcastPort);
		osc.addConsumer(&dmx);
	}

	bool setupOsc()
	{
		return true;
	}

	void startApp()
	{
		dmx.initialize();
	}

	void appLoop()
	{
		osc.loop(time.tOSC);

		if (time.tVISUAL)
		{
			dmx.animationLoop();
		}
	}

	// check for failure modes when the ESP must be reset
	bool appRestartRequired()
	{
		return false;
		//return !EthernetClient::ethernetIsConnected();
	}

	// check for queue exhaustion in the consumers of the OSC messages
	bool appWarningRequired()
	{
		return false;
	}
};