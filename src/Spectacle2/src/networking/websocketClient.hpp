#pragma once

#include <WiFiNINA.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

#include "../debugging/logger.hpp"
#include "../debugging/status.hpp"
#include "../messaging/json.hpp"

WebSocketsClient ws;

using StateChangedHandler = std::function<void()>;
StateChangedHandler stateChangedCallback;

void onEvent(
    WStype_t type,
    uint8_t *data,
    size_t length)
{
    if (type == WStype_TEXT)
    {
        JsonHandler.deserialize(data);
    }
    else if (type == WStype_CONNECTED)
    {
        Status.allOk();
    }
    else if (type == WStype_DISCONNECTED)
    {
        Status.setup();
    }
}

class WebSocketHelper
{
public:
    void begin()
    {
        PrintLnDebug("Starting web socket");

        ws.begin("10.0.0.201", 5151, "/led/spectacle");
        ws.onEvent(onEvent);

        PrintLnDebug("Started web socket");
    }

    void loop()
    {
        ws.loop();
    }

    void onStateChange(StateChangedHandler callback)
    {
        stateChangedCallback = callback;
    }

} WebSocket;

extern WebSocketHelper WebSocket;
