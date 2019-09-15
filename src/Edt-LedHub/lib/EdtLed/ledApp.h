#include <Arduino.h>
#include "core.h"

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

    OSC::Arduino<OSC::StructMessage<OSC::CommandMessage, uint8_t>> osc;

    FastLedTaskParameters tasks[2] = {
        { 1, 0, 10 },
        { 1, 127, 20}
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

        osc = OSC::Arduino<OSC::StructMessage<OSC::CommandMessage, uint8_t>>(sizeof(tasks), 0);
		osc.bindUDP(&EthernetClient::udp, broadcastIp, broadcastPort);
    }

    bool setupOsc()
    {
        return true;
    }

    void startApp()
    {
        xTaskCreate(&fastLedTask<APA102, 13, 16>, "fastLedTask1", 1024, (void *)&tasks[0], 10, NULL);
        xTaskCreate(&fastLedTask<APA102, 2, 16>, "fastLedTask2", 1024, (void *)&tasks[1], 10, NULL);
    }

    void appLoop()
    {
        osc.loop();

        // TODO: put in seperate task
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