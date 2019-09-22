#pragma once

#include "core.h"

const int fastLedCount = 6;
const int rgbLedCount = 0;

const int messageConsumerCount = fastLedCount + rgbLedCount;

Tasks::CommandMessageTask tasks[] = {
    Tasks::CommandMessageTask("/R1", &pca9685RgbLedTask<0x40, 1>, 5120, 3),
    Tasks::CommandMessageTask("/F1", &fastLedTask<APA102, 3, 32, BGR, 59>, 5120, 3),
    Tasks::CommandMessageTask("/F2", &fastLedTask<APA102, 2, 32, BGR, 59>, 5120, 3),
    Tasks::CommandMessageTask("/F3", &fastLedTask<APA102, 4, 32, BGR, 59>, 5120, 3),
    Tasks::CommandMessageTask("/F4", &fastLedTask<APA102, 15, 32, BGR, 59>, 5120, 3),
    Tasks::CommandMessageTask("/F5", &fastLedTask<APA102, 14, 32, BGR, 59>, 5120, 3),
    Tasks::CommandMessageTask("/F6", &fastLedTask<APA102, 5, 32, BGR, 59>, 5120, 3)};

class LedApp : public App::CoreApp
{
private:
public:
    const char *ledAppHostname;
    IPAddress localIp;
    IPAddress subnet;
    IPAddress broadcastIp;
    int broadcastPort;

    OSC::Arduino<OSC::StructMessage<Messages::CommandMessage, uint32_t>> osc;

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

        osc = OSC::Arduino<OSC::StructMessage<Messages::CommandMessage, uint32_t>>(sizeof(tasks) / sizeof(Tasks::CommandMessageTask), 0);
        osc.bindUDP(&EthernetClient::udp, broadcastIp, broadcastPort);

        for (auto &task : tasks)
        {
            osc.addConsumer(&task.messageConsumer);
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
            if (task.messageConsumer.queueExhausted)
            {
                return true;
            }
        }

        return false;
    }
};