#pragma once

#include "core.h"

const int fastLedCount = 6;

QueueHandle_t queues[fastLedCount] = {
    xQueueCreate(3, sizeof(Messages::CommandMessage)),
    xQueueCreate(3, sizeof(Messages::CommandMessage)),
    xQueueCreate(3, sizeof(Messages::CommandMessage)),
    xQueueCreate(3, sizeof(Messages::CommandMessage)),
    xQueueCreate(3, sizeof(Messages::CommandMessage)),
    xQueueCreate(3, sizeof(Messages::CommandMessage))};

Messages::CommandMessageConsumer consumers[fastLedCount] = {
    {"/F1", queues[0]},
    {"/F2", queues[1]},
    {"/F3", queues[2]},
    {"/F4", queues[3]},
    {"/F5", queues[4]},
    {"/F6", queues[5]}};

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

        osc = OSC::Arduino<OSC::StructMessage<Messages::CommandMessage, uint32_t>>(fastLedCount, 0);
        osc.bindUDP(&EthernetClient::udp, broadcastIp, broadcastPort);

        for (int i = 0; i < fastLedCount; i++)
        {
            osc.addConsumer(&consumers[i]);
        }
    }

    bool setupOsc()
    {
        return true;
    }

    void startApp()
    {
        xTaskCreate(&fastLedTask<APA102, 13, 16, BGR, 59>, "fastLedTask1", 10240, (void *)queues[0], 10, NULL);
        xTaskCreate(&fastLedTask<APA102, 2, 16, BGR, 59>, "fastLedTask2", 10240, (void *)queues[1], 10, NULL);
        xTaskCreate(&fastLedTask<APA102, 4, 16, BGR, 59>, "fastLedTask3", 10240, (void *)queues[2], 10, NULL);
        xTaskCreate(&fastLedTask<APA102, 15, 16, BGR, 59>, "fastLedTask4", 10240, (void *)queues[3], 10, NULL);
        xTaskCreate(&fastLedTask<APA102, 14, 16, BGR, 59>, "fastLedTask5", 10240, (void *)queues[4], 10, NULL);
        xTaskCreate(&fastLedTask<APA102, 5, 16, BGR, 59>, "fastLedTask6", 10240, (void *)queues[5], 10, NULL);
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