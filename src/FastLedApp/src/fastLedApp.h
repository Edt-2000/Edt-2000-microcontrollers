#pragma once

#include "core.h"
#include "fastLedDevice.h"

// Messages::MessageQueue<FastLedCommand> tasks[] = {
//     Messages::MessageQueue<FastLedCommand>("/F1", &fastLedTask<16, true>, 5120, 3),
//     Messages::MessageQueue<FastLedCommand>("/F2", &fastLedTask<13, false>, 5120, 3),
//     Messages::MessageQueue<FastLedCommand>("/F3", &fastLedTask<14, false>, 5120, 3), 
//     Messages::MessageQueue<FastLedCommand>("/F4", &fastLedTask<15, false>, 5120, 3),
//     Messages::MessageQueue<FastLedCommand>("/F5", &fastLedTask<5, false>, 5120, 3), 
//     Messages::MessageQueue<FastLedCommand>("/F6", &fastLedTask<4, false>, 5120, 3),
//     Messages::MessageQueue<FastLedCommand>("/F7", &fastLedTask<3, false>, 5120, 3),
//     Messages::MessageQueue<FastLedCommand>("/F8", &fastLedTask<2, false>, 5120, 3)};

FastLedBaseDevice* devices[] = {
    new FastLedDevice<16>("/F1"),
    new FastLedDevice<13>("/F2"),
    new FastLedDevice<14>("/F3"),
    new FastLedDevice<15>("/F4"),
    new FastLedDevice<5>("/F5"),
    new FastLedDevice<4>("/F6"),
    new FastLedDevice<3>("/F7"),
    new FastLedDevice<2>("/F8")
};

class FastLedApp : public App::CoreApp
{
private:
public:
    const char *ledAppHostname;
    IPAddress localIp;
    IPAddress subnet;
    IPAddress broadcastIp;
    int broadcastPort;

    OSC::Arduino<8, 0> osc;

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

        for (auto &device : devices)
        {
            osc.addConsumer(device);
        }
    }

    bool setupOsc()
    {
        return true;
    }

    void startApp()
    {
        for (auto &device : devices)
        {
            device->init();
        }
    }

    void appLoop()
    {
        osc.loop(time.tOSC);

        for (auto &device : devices)
        {
            device->animate();
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
        // for (auto &task : tasks)
        // {
        //     if (task.queueExhausted)
        //     {
        //         return true;
        //     }
        // }

        return false;
    }
};