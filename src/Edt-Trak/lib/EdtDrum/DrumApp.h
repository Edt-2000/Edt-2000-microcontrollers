#pragma once

#include "core.h"

class DrumApp : public App::CoreApp
{
private:
public:
    uint8_t *macAddress;
    IPAddress localIp;
    IPAddress subnet;
    IPAddress broadcastIp;
    int broadcastPort;

    EthernetUDP udp;

    OSC::Arduino<OSC::StructMessage<SimpleMessage, uint32_t>> osc;

    DrumMessageProducer producer = DrumMessageProducer("/DR");

    DrumApp(uint8_t *macAddress, IPAddress localIp, IPAddress subnet, IPAddress broadcastIp, int broadcastPort)
        : macAddress(macAddress),
          localIp(localIp),
          subnet(subnet),
          broadcastIp(broadcastIp),
          broadcastPort(broadcastPort)
    {
    }

    void startSetupNetwork()
    {
        Ethernet.begin(macAddress, localIp);
    }

    bool setupNetwork()
    {
        return true;
    }

    void startSetupOsc()
    {
        udp.begin(broadcastPort);

        osc = OSC::Arduino<OSC::StructMessage<SimpleMessage, uint32_t>>(0, 1);
        osc.bindUDP(&udp, broadcastIp, broadcastPort);

        osc.addProducer(&producer);
    }

    bool setupOsc()
    {
        return true;
    }

    void startApp()
    {
    }

    void appLoop()
    {
        osc.loop(true);
    }

    bool appRestartRequired()
    {
        return false;
    }

    bool appWarningRequired()
    {
        return false;
    }
};