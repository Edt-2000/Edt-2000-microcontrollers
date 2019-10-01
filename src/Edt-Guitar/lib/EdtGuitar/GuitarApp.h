#pragma once

#include "core.h"

class GuitarApp : public App::CoreApp
{
private:
public:
    const char *wifiName;
    const char *wifiPassword;
    IPAddress localIp;
    IPAddress subnet;
    IPAddress broadcastIp;
    int broadcastPort;

    WiFiUDP udp;

    OSC::Arduino<OSC::StructMessage<SimpleMessage, uint32_t>> osc;

    CRGB leds[3];

    GuitarMessageProducer producer = GuitarMessageProducer("/GR", leds, 3);
    DrumMessageConsumer consumer = DrumMessageConsumer("/DR", leds, 3);

    GuitarApp(const char *wifiName, const char *wifiPassword, IPAddress localIp, IPAddress subnet, IPAddress broadcastIp, int broadcastPort)
        : wifiName(wifiName),
          wifiPassword(wifiPassword),
          localIp(localIp),
          subnet(subnet),
          broadcastIp(broadcastIp),
          broadcastPort(broadcastPort) {}

    void startSetupNetwork()
    {
        WiFi.disconnect();
        WiFi.mode(WIFI_STA);
        WiFi.config(localIp, IPAddress(10, 0, 0, 0), IPAddress(255, 0, 0, 0));
        WiFi.begin(wifiName, wifiPassword);

        yield();
    }

    bool setupNetwork()
    {
        yield();

        return WiFi.status() == WL_CONNECTED;
    }

    void startSetupOsc()
    {
        yield();

        udp.begin(broadcastPort);

        osc = OSC::Arduino<OSC::StructMessage<SimpleMessage, uint32_t>>(1, 1);
        osc.bindUDP(&udp, broadcastIp, broadcastPort);

        osc.addConsumer(&consumer);
        osc.addProducer(&producer);
    }

    bool setupOsc()
    {
        yield();

        return true;
    }

    void startApp()
    {
        Serial.println(WiFi.localIP());

        FastLED.addLeds<NEOPIXEL, 14>(leds, 3);
        for (auto &led : leds)
        {
            led = CRGB::Black;
        }

        yield();
    }

    void appLoop()
    {
        osc.loop(time.tOSC);

        if (time.tVISUAL)
        {
            fadeToBlackBy(leds, 3, 16);
            FastLED.show();
        }

        yield();
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