#pragma once

#include <Arduino.h>
#include <CommandMessage.h>
#include <CommandMessageConsumer.h>

using namespace Messages;

namespace Tasks
{
struct CommandMessageTask
{
public:
    QueueHandle_t taskQueue;
    CommandMessageConsumer messageConsumer;

    const char *const oscAddress;
    TaskFunction_t taskFunction;
    const uint32_t taskStackDepth;

    CommandMessageTask(const char *oscAddress, TaskFunction_t taskFunction, const uint32_t taskStackDepth, const UBaseType_t queueElements)
        : oscAddress(oscAddress), taskFunction(taskFunction), taskStackDepth(taskStackDepth)
    {
        taskQueue = xQueueCreate(queueElements, sizeof(CommandMessage));
        messageConsumer = CommandMessageConsumer("/F1", taskQueue);
    }

    void start()
    {
        xTaskCreate(taskFunction, oscAddress, 10240, (void *)taskQueue, 10, NULL);
    }
};
} // namespace Tasks