#pragma once

#include <AsyncWebSocket.h>
#include <ArduinoJson.h>

#include "../settings.hpp"

using WSAnimationHandler = std::function<void(const char *animationName)>;
using WSSettingsHandler = std::function<void(Settings newSettings)>;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

JsonDocument doc;

WSAnimationHandler animationCallback;
WSSettingsHandler settingsCallback;

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
                if (animationCallback) {
                    animationCallback(doc["animation"]);
                }
            }
            else {

            }
        }
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

    void onSettings(WSSettingsHandler callback)
    {
        settingsCallback = callback;
    }

} WebSocket;

extern WebSocketHelper WebSocket;
