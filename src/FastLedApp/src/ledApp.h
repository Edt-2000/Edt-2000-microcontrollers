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

// Messages::MessageQueue<Messages::CommandMessage> tasks[] = {
//     Messages::MessageQueue<Messages::CommandMessage>("/F1", &fastLedTask<APA102, 3, 32, BGR, 59>, 5120, 3),
//     Messages::MessageQueue<Messages::CommandMessage>("/F2", &fastLedTask<APA102, 2, 32, BGR, 59>, 5120, 3),
//     Messages::MessageQueue<Messages::CommandMessage>("/F3", &fastLedTask<APA102, 4, 32, BGR, 59>, 5120, 3),
//     Messages::MessageQueue<Messages::CommandMessage>("/F4", &fastLedTask<APA102, 15, 32, BGR, 59>, 5120, 3),
//     Messages::MessageQueue<Messages::CommandMessage>("/F5", &fastLedTask<APA102, 14, 32, BGR, 59>, 5120, 3),
//     Messages::MessageQueue<Messages::CommandMessage>("/F6", &fastLedTask<APA102, 5, 32, BGR, 59>, 5120, 3),
//     Messages::MessageQueue<Messages::CommandMessage>("/F7", &fastLedTask<APA102, 13, 32, BGR, 59>, 5120, 3),
//     Messages::MessageQueue<Messages::CommandMessage>("/F8", &fastLedTask<APA102, 16, 32, BGR, 59>, 5120, 3)};

class LedApp : public App::CoreApp
{
private:
public:
    const char *ledAppHostname;
    IPAddress localIp;
    IPAddress subnet;
    IPAddress broadcastIp;
    int broadcastPort;

    OSC::Arduino<8, 0> osc;

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
        // consumers[0].start();
        // consumers[1].start();
        // consumers[2].start();
        // consumers[3].start();
        // consumers[4].start();
        // consumers[5].start();
        // consumers[6].start();
        // consumers[7].start();
        
        for (auto &consumer : consumers)
        {
            consumer.start();
        }
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