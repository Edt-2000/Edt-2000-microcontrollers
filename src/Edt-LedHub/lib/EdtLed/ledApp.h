#pragma once

#include "core.h"

QueueHandle_t queues[2] = {
    xQueueCreate(3, sizeof(Messages::CommandMessage)),
    xQueueCreate(3, sizeof(Messages::CommandMessage))};

Messages::CommandMessageConsumer consumers[2] = {
    {"/F1", queues[0]},
    {"/F2", queues[1]}};

class LedApp : public App::CoreApp
{
private:
public:
    int setupCount = 0;
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

        osc = OSC::Arduino<OSC::StructMessage<Messages::CommandMessage, uint32_t>>(1, 0);
        osc.bindUDP(&EthernetClient::udp, broadcastIp, broadcastPort);

        osc.addConsumer(&consumers[0]);
        osc.addConsumer(&consumers[1]);
    }

    bool setupOsc()
    {
        return true;
    }

    void startApp()
    {
        xTaskCreate(&fastLedTask<APA102, 13, 16, BGR, 1>, "fastLedTask1", 10240, (void *)queues[0], 10, NULL);
        xTaskCreate(&fastLedTask<APA102, 2, 16, BGR, 1>, "fastLedTask2", 10240, (void *)queues[1], 10, NULL);
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
};