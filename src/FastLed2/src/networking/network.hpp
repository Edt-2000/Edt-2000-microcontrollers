#pragma once

// #include <WiFi.h>
#include <ETH.h>
#include "../debugging/logger.hpp"

bool _networkConnected;
void ethernetEventHandler(WiFiEvent_t event, WiFiEventInfo_t info)
{
    _networkConnected = false;

    switch (event) {
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
            PrintLnInfo("Network disconnected!");
            ESP.restart();
            break;
    }
}

class NetworkHelper
{
public:
    void startEthernet(uint8_t unit)
    {
        WiFi.onEvent(ethernetEventHandler);

        auto staticIP = IPAddress(10, 0, 0, 20 + unit);
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
