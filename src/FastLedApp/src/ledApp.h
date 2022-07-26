#pragma once

#include "core.h"

Messages::MessageQueue consumers[] = {
    Messages::MessageQueue("/F1", new Devices::EdtFastLed<APA102, 3, 32, BGR, 59>()),
    Messages::MessageQueue("/F2", new Devices::EdtFastLed<APA102, 2, 32, BGR, 59>()),
    Messages::MessageQueue("/F3", new Devices::EdtFastLed<APA102, 4, 32, BGR, 59>()),
    Messages::MessageQueue("/F4", new Devices::EdtFastLed<APA102, 15, 32, BGR, 59>()),
    Messages::MessageQueue("/F5", new Devices::EdtFastLed<APA102, 14, 32, BGR, 59>()),
    Messages::MessageQueue("/F6", new Devices::EdtFastLed<APA102, 5, 32, BGR, 59>()),
    Messages::MessageQueue("/F7", new Devices::EdtFastLed<APA102, 13, 32, BGR, 59>()),
    Messages::MessageQueue("/F8", new Devices::EdtFastLed<APA102, 16, 32, BGR, 59>())};

class LedApp : public App::CoreApp
{
private:
public:
    const char *ledAppHostname;
    IPAddress localIp;
    IPAddress subnet;
    IPAddress broadcastIp;
    int broadcastPort;

    OSC::Arduino<8, 0, OSC::StructMessage<Messages::CommandMessage, uint32_t>> osc;

    LedApp(const char *ledAppHostname,
           IPAddress localIp,
           IPAddress subnet,
           IPAddress broadcastIp,
           int broadcastPort)
        : ledAppHostname(ledAppHostname),
          localIp(localIp),
          subnet(subnet),
          broadcastIp(broadcastIp),
          broadcastPort(broadcastPort) {}

    void startSetupNetwork()
    {
        EthernetClient::setupEthernet(ledAppHostname, localIp, subnet);
    }

    bool setupNetwork()
    {
        return EthernetClient::ethernetIsConnected();
    }

    void startSetupOsc()
    {
        EthernetClient::setupUdp(broadcastPort);

        osc.bindUDP(&EthernetClient::udp, broadcastIp, broadcastPort);

        for (auto &consumer : consumers)
        {
            osc.addConsumer(&consumer);
        }
    }

    bool setupOsc()
    {
        return true;
    }

    void startApp()
    {
        for (auto &consumer : consumers)
        {
            consumer.start();
        }

        FastLED.show();
    }

    void appLoop()
    {
        osc.loop(time.tOSC);

        for (auto &consumer : consumers)
        {
            consumer.loop();
        }

        if (time.tVISUAL)
        {
            FastLED.show();
        }
    }

    // check for failure modes when the ESP must be reset
    bool appRestartRequired()
    {
        return !EthernetClient::ethernetIsConnected();
    }

    // check for queue exhaustion in the consumers of the OSC messages
    bool appWarningRequired()
    {
        return false;
    }
};