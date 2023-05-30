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

volatile bool doFastLed = false;

FastLedBaseDevice* devices[] = {
    new FastLedDevice<16, 1>("/F1"),
    new FastLedDevice<13, 2>("/F2"),
    new FastLedDevice<14, 3>("/F3"),
    new FastLedDevice<15, 4>("/F4"),
    new FastLedDevice<5, 5>("/F5"),
    new FastLedDevice<4, 6>("/F6"),
    new FastLedDevice<3, 7>("/F7"),
    new FastLedDevice<2, 8>("/F8")
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

        xTaskCreate(&fastLedTask, "OSC", 5120, NULL, 1, NULL);
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

        bool shouldOutput = time.tOSC;

        for (auto &device : devices)
        {
            bool output = device->animate(time.tVISUAL);
            shouldOutput = shouldOutput || output;
        }
        
        if (shouldOutput) {
            doFastLed = true;
        }

        // if (time.tVISUAL)
        // {
        //     doFastLed = true;
        //     // FastLED.show();
        // }
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