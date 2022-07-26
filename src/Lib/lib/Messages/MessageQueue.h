#pragma once

#include <core.h>
// #include <Arduino.h>
// #include <OSCArduino.h>
// #include <CommandMessage.h>
// #include <IMessage.h>
// #include <OSCStructMessage.h>

namespace Messages
{
    // template <ESPIChipsets CHIPSET, uint8_t DATA_PIN, uint8_t CLOCK_PIN, EOrder RGB_ORDER, uint8_t NUMBER_OF_LEDS>
    class MessageQueue : public OSC::MessageConsumer
    {
    private: 
        Devices::EdtDevice *_device;

    public:
        // QueueHandle_t taskQueue;
        // bool queueExhausted = false;

        const char *const oscAddress;
        // TaskFunction_t taskFunction;
        // const uint32_t taskStackDepth;

        MessageQueue(const char *oscAddress, Devices::EdtDevice *device) //, TaskFunction_t taskFunction, const uint32_t taskStackDepth, const UBaseType_t queueElements)
            : oscAddress(oscAddress)                                     //, taskFunction(taskFunction), taskStackDepth(taskStackDepth)
        {
            _device = device;
            //_message = new OSC::StructMessage<Messages::CommandMessage, uint32_t>();

            // taskQueue = xQueueCreate(queueElements, sizeof(T));

            // if (taskQueue == NULL)
            // {
            //     Serial.println("Queue failed to create.");
            // }
        }

        void start()
        {
            Serial.println(oscAddress);
            _device->init();
            // xTaskCreate(taskFunction, oscAddress, 10240, taskQueue, 10, NULL);
        }

        const char *address()
        {
            return oscAddress;
        }

        void callbackMessage(OSC::IMessage * message)
        {
            auto structMessage = (OSC::StructMessage<Messages::CommandMessage, uint32_t>*)message;

            _device->handleMessage(&(structMessage->messageStruct));
            // failed to insert into queue, probably due to high traffic
            // flagging this exhaustion occurance for debugging
            // if (xQueueSend(taskQueue, &_message.messageStruct, 0) == errQUEUE_FULL)
            // {
            //     queueExhausted = true;
            // }
        }

        void loop()
        {
            _device->animate();
        }
    };
} // namespace Messages