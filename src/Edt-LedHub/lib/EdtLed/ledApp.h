#include <Arduino.h>
#include "core.h"

QueueHandle_t queues[2] = {
     xQueueCreate(3, sizeof(OSC::CommandMessage)),
     xQueueCreate(3, sizeof(OSC::CommandMessage))
};

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

    OSC::Arduino<OSC::StructMessage<OSC::CommandMessage, uint32_t>> osc;

    FastLedTaskParameters tasks[2] = {
        { 1, queues[0] },
        { 1, queues[1] }
    };

    CommandMessageConsumer consumers[2] = {
        { "/F1", queues[0] },
        { "/F2", queues[1] }
    };

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

        osc = OSC::Arduino<OSC::StructMessage<OSC::CommandMessage, uint32_t>>(1, 0);
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
        xTaskCreate(&fastLedTask<APA102, 13, 16, BGR>, "fastLedTask1", 10240, (void *)&tasks[0], 10, NULL);
        xTaskCreate(&fastLedTask<APA102, 2, 16, BGR>, "fastLedTask2", 10240, (void *)&tasks[1], 10, NULL);
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
    bool appRestartRequired() {
        return !EthernetClient::ethernetIsConnected();
    }
};