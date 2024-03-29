#pragma once

#include <Arduino.h>
#include <OSCArduino.h>
#include <CommandMessage.h>
#include <IMessage.h>
#include <OSCStructMessage.h>

namespace Messages
{
    template <typename T>
    class MessageQueue : public OSC::MessageConsumer
    {
    private:
        OSC::StructMessage<T, uint32_t> _message;

    public:
        QueueHandle_t taskQueue;
        bool queueExhausted = false;

        const char *const oscAddress;
        TaskFunction_t taskFunction;
        const uint32_t taskStackDepth;

        MessageQueue(const char *oscAddress, TaskFunction_t taskFunction, const uint32_t taskStackDepth, const UBaseType_t queueElements)
            : oscAddress(oscAddress), taskFunction(taskFunction), taskStackDepth(taskStackDepth)
        {
            taskQueue = xQueueCreate(queueElements, sizeof(T));

            if (taskQueue == NULL)
            {
                Serial.println("Queue failed to create.");
            }
        }

        void start()
        {
            xTaskCreate(taskFunction, oscAddress, 10240, taskQueue, 10, NULL);
        }

        const char *address()
        {
            return oscAddress;
        }

        OSC::IMessage *message()
        {
            return &_message;
        }

        void callbackMessage()
        {
            // failed to insert into queue, probably due to high traffic
            // flagging this exhaustion occurance for debugging
            if (xQueueSend(taskQueue, &_message.messageStruct, 0) == errQUEUE_FULL)
            {
                queueExhausted = true;
            }
        }
    };
} // namespace Messages