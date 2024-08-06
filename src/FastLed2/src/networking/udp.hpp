#pragma once

#include <functional>

#include <Arduino.h>
#include <AsyncUDP.h>

#include "../messaging/json.hpp"

AsyncUDP udp;

void onEvent(AsyncUDPPacket& packet)
{
    JsonHandler.deserialize(packet.data());
}

class UdpHelper {
    public:
    void begin() {
        PrintLnDebug("Starting udp");

        udp.listen(12345);
        udp.onPacket(onEvent);
        
        PrintLnDebug("Started udp");
    }
} Udp;

extern UdpHelper Udp;
