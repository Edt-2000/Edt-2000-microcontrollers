#pragma once

#include "core.h"

class SmokeApp : public App::CoreApp
{
private:
public:
    const char *ledAppHostname;
    IPAddress localIp;
    IPAddress gateway;
    IPAddress subnet;
    IPAddress broadcastIp;
    int broadcastPort;

    OSC::Arduino<1, 0> osc;
    WiFiUDP UDP;

    SmokeDevice device = SmokeDevice("/SM");

    SmokeApp(const char *ledAppHostname,
             IPAddress localIp,
             IPAddress gateway,
             IPAddress subnet,
             IPAddress broadcastIp,
             int broadcastPort)
        : ledAppHostname(ledAppHostname),
          localIp(localIp),
          gateway(gateway),
          subnet(subnet),
          broadcastIp(broadcastIp),
          broadcastPort(broadcastPort)
    {
    }

    void startSetupNetwork()
    {
        WiFi.config(localIp, gateway, subnet);
        WiFi.begin("nEDTwerk", "ChillenInJeSjon");
    }

    bool setupNetwork()
    {
        return WiFi.status() == WL_CONNECTED;
    }

    void startSetupOsc()
    {
        UDP.begin(broadcastPort);

        osc.bindUDP(&UDP, broadcastIp, broadcastPort);

        osc.addConsumer(&device);
    }

    bool setupOsc()
    {
        return true;
    }

    void startApp()
    {
    }

    void appLoop()
    {
        osc.loop(time.tOSC);

        if (time.t1000ms)
        {
            device.loop();
        }
    }

    // check for failure modes when the ESP must be reset
    bool appRestartRequired()
    {
        return !WiFi.isConnected();
    }

    bool appWarningRequired()
    {
        return false;
    }
};