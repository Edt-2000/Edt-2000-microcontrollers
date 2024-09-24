#pragma once

#include <esp_websocket_client.h>

#include "../debugging/logger.hpp"
#include "../debugging/status.hpp"
#include "../messaging/json.hpp"

const uint8_t OPCODE_DATAFRAME_TEXT = 1;

void onEvent(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data){
    if (event_id == WEBSOCKET_EVENT_DATA) {
        esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
        if (data->op_code == OPCODE_DATAFRAME_TEXT) {
            JsonHandler.deserialize((uint8_t*)(data->data_ptr));
        }
    }
    else if (event_id == WEBSOCKET_EVENT_CONNECTED) {
        Status.allOk();
    }
    else if (event_id == WEBSOCKET_EVENT_DISCONNECTED) {
        Status.setup();
    }
}

const esp_websocket_client_config_t ws_cfg = {
    .uri = "ws://10.0.0.201:5151/led",
};
esp_websocket_client_handle_t ws;

class WebSocketHelper
{
public:
    void begin()
    {
        PrintLnDebug("Starting web socket");

        ws = esp_websocket_client_init(&ws_cfg);

        esp_websocket_register_events(ws, WEBSOCKET_EVENT_ANY, onEvent, nullptr);

        esp_websocket_client_start(ws);

        PrintLnDebug("Started web socket");
    }

    void send(String data)
    {
        // TODO?
        //ws.sendTXT(data);
    }
} WebSocket;

extern WebSocketHelper WebSocket;
