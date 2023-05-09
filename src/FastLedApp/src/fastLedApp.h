#pragma once

#include "core.h"
#include "fastLedDevice.h"

// TODO: check how to schedule stuff for better predictability

Messages::MessageQueue<FastLedCommand> tasks[] = {
    Messages::MessageQueue<FastLedCommand>("/F1", &fastLedTask<16, true, 0>, 5120, 3, 0),
    Messages::MessageQueue<FastLedCommand>("/F2", &fastLedTask<13, false, 1>, 5120, 3, 1),
    Messages::MessageQueue<FastLedCommand>("/F3", &fastLedTask<14, false, 2>, 5120, 3, 0),
    Messages::MessageQueue<FastLedCommand>("/F4", &fastLedTask<15, false, 3>, 5120, 3, 1),
    Messages::MessageQueue<FastLedCommand>("/F5", &fastLedTask<5, false, 4>, 5120, 3, 0),
    Messages::MessageQueue<FastLedCommand>("/F6", &fastLedTask<4, false, 5>, 5120, 3, 1),
    Messages::MessageQueue<FastLedCommand>("/F7", &fastLedTask<3, false, 6>, 5120, 3, 0),
    Messages::MessageQueue<FastLedCommand>("/F8", &fastLedTask<2, false, 7>, 5120, 3, 1)};

volatile bool doFastLed = false;

class FastLedApp : public App::CoreApp
{
private:
public:
    const char *ledAppHostname;
    IPAddress localIp;
    IPAddress subnet;
    IPAddress broadcastIp;
    int broadcastPort;

    OSC::Arduino<sizeof(tasks) / sizeof(Messages::MessageQueue<FastLedCommand>), 0> osc;

    FastLedApp(const char *ledAppHostname,
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

        if (doFastLed || time.tVISUAL)
        {
            doFastLed = false;
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