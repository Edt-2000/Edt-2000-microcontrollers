#pragma once

#include <WiFi.h>
#include <ETH.h>

static bool _ethernetConnected;
static void ethernetEventHandler(WiFiEvent_t event, WiFiEventInfo_t info)
{
    _ethernetConnected = false;

    switch (event) {
        case ARDUINO_EVENT_ETH_START:
            // Serial.println("Starting ethernet..");
            break;
        case ARDUINO_EVENT_ETH_CONNECTED:
            // Serial.println("Ethernet connected!");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP:
            // Serial.println("Ethernet got IP!");
            _ethernetConnected = true;
            break;
    }
    
    _ethernetConnected = true;
}

class NetworkHelper
{
public:
    void startEthernet(IPAddress ip)
    {
        WiFi.onEvent(ethernetEventHandler);

        // ESP32 ETH has ethernet client - otherwise its WiFi.begin() and WiFi.config()
        ETH.begin();
        ETH.config(ip, IPAddress(10, 0, 0, 1), IPAddress(255, 0, 0, 0));
    }

    bool ethernetIsConnected()
    {
        return _ethernetConnected;
    }
} Network;

extern NetworkHelper Network;
