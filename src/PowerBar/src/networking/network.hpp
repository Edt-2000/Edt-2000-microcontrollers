#pragma once

#include <WiFi.h>
#include <ETH.h>
#include "../debugging/logger.hpp"

bool _networkConnected;
void ethernetEventHandler(WiFiEvent_t event, WiFiEventInfo_t info)
{
    _networkConnected = false;

    switch (event)
    {
    case ARDUINO_EVENT_ETH_START:
    case ARDUINO_EVENT_WIFI_STA_START:
        PrintLnInfo("Starting network..");
        break;
    case ARDUINO_EVENT_ETH_CONNECTED:
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        PrintLnInfo("Network connected!");
        break;
    case ARDUINO_EVENT_ETH_GOT_IP:
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
        PrintLnInfo("Network got IP!");
        _networkConnected = true;
        break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        _networkConnected = false;
        break;
    }
}

class NetworkHelper
{
public:
    void startWifi()
    {
        WiFi.begin("nEDTwerk", "ChillenInJeSjon");
        WiFi.onEvent(ethernetEventHandler);

        auto staticIP = IPAddress(10, 0, 0, 30);
        auto gatewayIP = IPAddress(10, 0, 0, 1);
        auto subnet = IPAddress(255, 0, 0, 0);

        WiFi.config(staticIP, gatewayIP, subnet);
    }

    void startEthernet()
    {
        WiFi.onEvent(ethernetEventHandler);

        auto staticIP = IPAddress(10, 0, 0, 30);
        auto gatewayIP = IPAddress(10, 0, 0, 1);
        auto subnet = IPAddress(255, 0, 0, 0);

        ETH.begin();
        ETH.config(staticIP, gatewayIP, subnet);
    }

    bool networkIsConnected()
    {
        return _networkConnected;
    }
} Network;

extern NetworkHelper Network;
