#pragma once

#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12

#include <ETH.h>

class EthernetClient
{
private:
  static bool _ethernetConnected = false;
  static const char *_hostname;

  static void _eventHandler(system_event_id_t event)
  {
    switch (event)
    {
    case SYSTEM_EVENT_ETH_START:
      ETH.setHostname(_hostname);
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      break;
    case SYSTEM_EVENT_ETH_GOT_IP:
      _ethernetConnected = true;
      break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
      _ethernetConnected = false;
      break;
    case SYSTEM_EVENT_ETH_STOP:
      _ethernetConnected = false;
      break;
    default:
      break;
    }
  }

public:
  EthernetClient(const char *hostname) : _hostname(hostname) {}

  void setup()
  {
    auto eventHandler = [this](system_event_id_t event) {
      _eventHandler(event);
    };

    WiFi.onEvent(eventHandler, system_event_id_t::SYSTEM_EVENT_MAX);
    ETH.begin();
  }

  bool isConnected()
  {
    return _ethernetConnected;
  }
};
