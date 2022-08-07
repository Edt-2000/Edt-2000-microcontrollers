#pragma once

#include "core.h"

class SpectacleApp : public App::CoreApp
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

    SpectacleDevice device = SpectacleDevice("/SP");

    SpectacleApp(const char * ledAppHostname,
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
      Serial.println("START NETWORK 1");
      delay(1000);
        WiFi.begin("nEDTwerk", "ChillenInJeSjon");
      delay(1000);
      Serial.println("START NETWORK 2");
      delay(1000);
        WiFi.config(localIp, INADDR_NONE, gateway, subnet);
      delay(1000);
      Serial.println("START NETWORK 3");
      delay(1000);
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

        device.loop();
    }

    // check for failure modes when the ESP must be reset
    bool appRestartRequired()
    {
        return WiFi.status() == WL_CONNECTION_LOST;
    }

    bool appWarningRequired()
    {
        return false;
    }
};