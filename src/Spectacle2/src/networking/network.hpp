#pragma once

#include <WiFiNINA.h>

#include "../debugging/logger.hpp"

bool _networkConnected;

class NetworkHelper
{
public:
    void startWiFi()
    {
        _networkConnected = false;

        auto staticIP = IPAddress(10, 0, 0, 99);
        auto gatewayIP = IPAddress(10, 0, 0, 1);
        auto subnet = IPAddress(255, 0, 0, 0);

        WiFi.config(staticIP, INADDR_NONE, gatewayIP, subnet);
        
        WiFi.begin("nEDTwerk", "ChillenInJeSjon");

        auto status = WiFi.status();

        while (status != WL_CONNECTED)
        {
            PrintLnInfo("Connecting to WiFi..");
            delay(1000);
            status = WiFi.status();
        }

        _networkConnected = true;
    }

    bool networkIsConnected()
    {
        return _networkConnected;
    }
} Network;

extern NetworkHelper Network;
