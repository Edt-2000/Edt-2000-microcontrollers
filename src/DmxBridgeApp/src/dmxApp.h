#pragma once

#include "core.h"

class DmxApp : public App::CoreApp
{
private:
public:
	const char *dmxAppHostname;
	IPAddress localIp;
	IPAddress subnet;
	IPAddress broadcastIp;
	int broadcastPort;

	OSC::Arduino<1, 0> osc;
	OSC::Device::EdtDMX dmx = Devices::EdtDmx("/R1"));

	DmxApp(const char *dmxAppHostname, IPAddress localIp, IPAddress subnet, IPAddress broadcastIp, int broadcastPort)
		: dmxAppHostname(dmxAppHostname),
		  localIp(localIp),
		  subnet(subnet),
		  broadcastIp(broadcastIp),
		  broadcastPort(broadcastPort) {}

	void startSetupNetwork()
	{
		Ethernet.begin();
		EthernetClient::setupEthernet(dmxAppHostname, localIp, subnet);
	}

	bool setupNetwork()
	{
#ifndef ETHERNET

		Serial.begin(57600);

#else
		Ethernet.begin(MAC_DOSMCX, localIp);

		udp.begin(broadcastPort);

#endif
		// return EthernetClient::ethernetIsConnected();
	}

	void startSetupOsc()
	{
		DMXSerial.init(DMXController);

		osc = OSC::Arduino<OSC::StructMessage<OSC::EdtMessage, uint8_t>>(0, 0);
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
			FastLED.show();
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