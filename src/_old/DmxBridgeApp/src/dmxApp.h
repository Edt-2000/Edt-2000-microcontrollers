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
	DmxDevice dmx;

	DmxApp(const char *dmxAppHostname,
		   const char *oscAddress,
		   IPAddress localIp,
		   IPAddress subnet,
		   IPAddress broadcastIp,
		   int broadcastPort)
		: dmxAppHostname(dmxAppHostname),
		  localIp(localIp),
		  subnet(subnet),
		  broadcastIp(broadcastIp),
		  broadcastPort(broadcastPort),
		  dmx(DmxDevice(oscAddress))
	{
	}

	void startSetupNetwork()
	{
		EthernetClient::setupEthernet(dmxAppHostname, localIp, subnet);
	}

	bool setupNetwork()
	{
		return EthernetClient::ethernetIsConnected();
	}

	void startSetupOsc()
	{
		EthernetClient::setupUdp(broadcastPort);

		osc.bindUDP(&EthernetClient::udp, broadcastIp, broadcastPort);

		osc.addConsumer(&dmx);
	}

	bool setupOsc()
	{
		return true;
	}

	void startApp()
	{
		dmx.start();
	}

	void appLoop()
	{
		osc.loop(time.tOSC);

		if (time.tVISUAL)
		{
			dmx.show();
		}
	}

	// check for failure modes when the ESP must be reset
	bool appRestartRequired()
	{
		return !EthernetClient::ethernetIsConnected();
	}

	// there is nothing to complain about
	bool appWarningRequired()
	{
		return false;
	}
};