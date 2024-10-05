#pragma once

#include <WebSocketsServer.h>
#include <ArduinoJson.h>

#include "../debugging/logger.hpp"
#include "../debugging/status.hpp"
#include "../messaging/json.hpp"

WebSocketsServer ws(80);

using StateChangedHandler = std::function<void()>;
StateChangedHandler stateChangedCallback;

void onEvent(
    uint8_t num, 
    WStype_t type, 
    uint8_t * data, 
    size_t lengthh)
{
    PrintInfo("MESSAGE ");
    PrintLnInfo(type);

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

        ws.begin();
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
