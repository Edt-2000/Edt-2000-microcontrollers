#pragma once

#include "core.h"

Messages::MessageQueue<Messages::CommandMessage> tasks[] = {
    Messages::MessageQueue<Messages::CommandMessage>("/R1", &pca9685RgbLedTask<0x40, 8>, 5120, 3)};

class LedApp : public App::CoreApp
{
private:
public:
    const char *ledAppHostname;
    IPAddress localIp;
    IPAddress subnet;
    IPAddress broadcastIp;
    int broadcastPort;

    OSC::Arduino<sizeof(tasks) / sizeof(Messages::MessageQueue<Messages::CommandMessage>), 0> osc;

    LedApp(const char *ledAppHostname, IPAddress localIp, IPAddress subnet, IPAddress broadcastIp, int broadcastPort)
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

        for (auto &task : tasks)
        {
            osc.addConsumer(&task);
        }
    }

    bool setupOsc()
    {
        return true;
    }

    void startApp()
    {
        for (auto &task : tasks)
        {
            task.start();
        }
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
        return !EthernetClient::ethernetIsConnected();
    }

    // check for queue exhaustion in the consumers of the OSC messages
    bool appWarningRequired()
    {
        for (auto &task : tasks)
        {
            if (task.queueExhausted)
            {
                return true;
            }
        }

        return false;
    }
};