#pragma once

#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12

#include <ETH.h>

namespace EthernetClient
{

  bool _ethernetConnected;
  const char *_hostname;
  WiFiUDP udp;

  void ethernetEventHandler(WiFiEvent_t event)
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

  void setupEthernet(const char *hostname, IPAddress localIp, IPAddress subnet)
  {
    _ethernetConnected = false;
    _hostname = hostname;

    WiFi.onEvent(ethernetEventHandler);

    ETH.begin();
    ETH.config(localIp, IPAddress(0, 0, 0, 0), subnet);
  }

  bool ethernetIsConnected()
  {
    return _ethernetConnected;
  }

  void setupUdp(int port)
  {
    udp.begin(port);
  }

} // namespace EthernetClient