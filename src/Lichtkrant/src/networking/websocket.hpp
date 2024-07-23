#pragma once

#include <AsyncWebSocket.h>
#include <ArduinoJson.h>

#include "../settings.hpp"

using WSAnimationHandler = std::function<void(const char *animationName)>;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

JsonDocument doc;

WSAnimationHandler animationCallback;

void onEvent(
    AsyncWebSocket *server,
    AsyncWebSocketClient *client,
    AwsEventType type,
    void *arg,
    uint8_t *data,
    size_t len)
{
    if (type == WS_EVT_DATA)
    {
        doc.clear();
        auto error = deserializeJson(doc, data);

        if (!error)
        {
            if (doc.containsKey("animation"))
            {
                if (animationCallback)
                {
                    animationCallback(doc["animation"]);
                }
            }
            else
            {
                if (doc.containsKey("text"))
                {
                    globalSettings.text = doc["text"];

                    Serial.print("Setting text set to ");
                    Serial.println(globalSettings.text);
                }
                if (doc.containsKey("color1"))
                {
                    auto color = doc["color1"];
                    globalSettings.colors[0] = CHSV(color[0], color[1], color[2]);

                    Serial.print("Setting color[0] set to ");
                    Serial.print(globalSettings.colors[0].h);
                    Serial.print(",");
                    Serial.print(globalSettings.colors[0].s);
                    Serial.print(",");
                    Serial.println(globalSettings.colors[0].v);
                }
                if (doc.containsKey("color2"))
                {
                    auto color = doc["color2"];
                    globalSettings.colors[1] = CHSV(color[0], color[1], color[2]);

                    Serial.print("Setting color[1] set to ");
                    Serial.print(globalSettings.colors[1].h);
                    Serial.print(",");
                    Serial.print(globalSettings.colors[1].s);
                    Serial.print(",");
                    Serial.println(globalSettings.colors[1].v);
                }
                if (doc.containsKey("color3"))
                {
                    auto color = doc["color3"];
                    globalSettings.colors[2] = CHSV(color[0], color[1], color[2]);

                    Serial.print("Setting color[2] set to ");
                    Serial.print(globalSettings.colors[2].h);
                    Serial.print(",");
                    Serial.print(globalSettings.colors[2].s);
                    Serial.print(",");
                    Serial.println(globalSettings.colors[2].v);
                }
                if (doc.containsKey("color4"))
                {
                    auto color = doc["color4"];
                    globalSettings.colors[3] = CHSV(color[0], color[1], color[2]);

                    Serial.print("Setting color[3] set to ");
                    Serial.print(globalSettings.colors[3].h);
                    Serial.print(",");
                    Serial.print(globalSettings.colors[3].s);
                    Serial.print(",");
                    Serial.println(globalSettings.colors[3].v);
                }
                if (doc.containsKey("color5"))
                {
                    auto color = doc["color5"];
                    globalSettings.colors[4] = CHSV(color[0], color[1], color[2]);

                    Serial.print("Setting color[4] set to ");
                    Serial.print(globalSettings.colors[4].h);
                    Serial.print(",");
                    Serial.print(globalSettings.colors[4].s);
                    Serial.print(",");
                    Serial.println(globalSettings.colors[4].v);
                }
                if (doc.containsKey("speed"))
                {
                    globalSettings.speed = doc["speed"];
                    if (globalSettings.speed == 0)
                    {
                        globalSettings.speed = 1;
                    }
                    
                    Serial.print("Setting speed set to ");
                    Serial.println(globalSettings.speed);
                }
                if (doc.containsKey("brightness"))
                {
                    globalSettings.brightness = doc["brightness"];
                    
                    Serial.print("Setting brightness set to ");
                    Serial.println(globalSettings.brightness);
                }
                if (doc.containsKey("size"))
                {
                    globalSettings.size = doc["size"];
                    
                    Serial.print("Setting size set to ");
                    Serial.println(globalSettings.size);
                }
            }
        }
    }
    else if (type == WS_EVT_CONNECT)
    {
        Serial.println("Client connected");
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.println("Client disconnected");
    }
}

class WebSocketHelper
{
public:
    void begin()
    {
        Serial.println("Starting web socket");

        ws.onEvent(onEvent);
        server.addHandler(&ws);
        server.begin();

        Serial.println("Started web socket");
    }

    void onAnimation(WSAnimationHandler callback)
    {
        animationCallback = callback;
    }

} WebSocket;

extern WebSocketHelper WebSocket;
