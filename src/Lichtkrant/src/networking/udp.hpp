#pragma once

#include <functional>

#include <Arduino.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>

#include "../settings.hpp"

using UDPAnimationHandler = std::function<void(const char *animationName)>;

AsyncUDP udp;

JsonDocument doc;

UDPAnimationHandler animationCallback;

void onEvent(AsyncUDPPacket& packet)
{
    doc.clear();
    
    auto error = deserializeJson(doc, packet.data());

    if (!error)
        {
            auto isAnimation = doc.containsKey("animation");
            auto isSettings = !isAnimation || (isAnimation && doc.size() > 1);
            
            if (isSettings)
            {
                if (doc.containsKey("text"))
                {
                    globalSettings.text = doc["text"];

                    // Serial.print("Setting text set to ");
                    // Serial.println(globalSettings.text);
                }
                if (doc.containsKey("color1"))
                {
                    auto color = doc["color1"];
                    globalSettings.colors[0] = CHSV(color[0], color[1], color[2]);

                    // Serial.print("Setting color[0] set to ");
                    // Serial.print(globalSettings.colors[0].h);
                    // Serial.print(",");
                    // Serial.print(globalSettings.colors[0].s);
                    // Serial.print(",");
                    // Serial.println(globalSettings.colors[0].v);
                }
                if (doc.containsKey("color2"))
                {
                    auto color = doc["color2"];
                    globalSettings.colors[1] = CHSV(color[0], color[1], color[2]);

                    // Serial.print("Setting color[1] set to ");
                    // Serial.print(globalSettings.colors[1].h);
                    // Serial.print(",");
                    // Serial.print(globalSettings.colors[1].s);
                    // Serial.print(",");
                    // Serial.println(globalSettings.colors[1].v);
                }
                if (doc.containsKey("color3"))
                {
                    auto color = doc["color3"];
                    globalSettings.colors[2] = CHSV(color[0], color[1], color[2]);

                    // Serial.print("Setting color[2] set to ");
                    // Serial.print(globalSettings.colors[2].h);
                    // Serial.print(",");
                    // Serial.print(globalSettings.colors[2].s);
                    // Serial.print(",");
                    // Serial.println(globalSettings.colors[2].v);
                }
                if (doc.containsKey("color4"))
                {
                    auto color = doc["color4"];
                    globalSettings.colors[3] = CHSV(color[0], color[1], color[2]);

                    // Serial.print("Setting color[3] set to ");
                    // Serial.print(globalSettings.colors[3].h);
                    // Serial.print(",");
                    // Serial.print(globalSettings.colors[3].s);
                    // Serial.print(",");
                    // Serial.println(globalSettings.colors[3].v);
                }
                if (doc.containsKey("color5"))
                {
                    auto color = doc["color5"];
                    globalSettings.colors[4] = CHSV(color[0], color[1], color[2]);

                    // Serial.print("Setting color[4] set to ");
                    // Serial.print(globalSettings.colors[4].h);
                    // Serial.print(",");
                    // Serial.print(globalSettings.colors[4].s);
                    // Serial.print(",");
                    // Serial.println(globalSettings.colors[4].v);
                }
                if (doc.containsKey("speed"))
                {
                    globalSettings.speed = doc["speed"];
                    if (globalSettings.speed == 0)
                    {
                        globalSettings.speed = 1;
                    }
                    
                    // Serial.print("Setting speed set to ");
                    // Serial.println(globalSettings.speed);
                }
                if (doc.containsKey("brightness"))
                {
                    globalSettings.brightness = doc["brightness"];
                    
                    // Serial.print("Setting brightness set to ");
                    // Serial.println(globalSettings.brightness);
                }
                if (doc.containsKey("size"))
                {
                    globalSettings.size = doc["size"];
                    
                    // Serial.print("Setting size set to ");
                    // Serial.println(globalSettings.size);
                }
            }

            if (isAnimation)
            {
                if (animationCallback)
                {
                    animationCallback(doc["animation"]);
                }
            }
        }
}

class UdpHelper {
    public:
    void begin() {
        udp.listen(12345);
        udp.onPacket(onEvent);
    }

    void onAnimation(UDPAnimationHandler callback)
    {
        animationCallback = callback;
    }
} Udp;

extern UdpHelper Udp;
