#pragma once

#include <AsyncWebSocket.h>
#include <ArduinoJson.h>

#include "../debugging/logger.hpp"
#include "../messaging/json.hpp"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

using StateChangedHandler = std::function<void()>;
StateChangedHandler stateChangedCallback;

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
        JsonHandler.deserialize(data);
    }
    else if (type == WS_EVT_CONNECT)
    {
        PrintLnDebug("Client connected");
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        PrintLnDebug("Client disconnected");
    }
}

class WebSocketHelper
{
public:
    void begin()
    {
        PrintLnDebug("Starting web socket");

        ws.onEvent(onEvent);
        server.addHandler(&ws);
        server.begin();

        PrintLnDebug("Started web socket");
    }

    void send(String data)
    {
        ws.textAll(data);
    }

    void cleanUp()
    {
        ws.cleanupClients();
    }

    void onStateChange(StateChangedHandler callback)
    {
        stateChangedCallback = callback;
    }

} WebSocket;

extern WebSocketHelper WebSocket;
