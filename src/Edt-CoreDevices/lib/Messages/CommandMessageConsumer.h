#pragma once

#include <OSCArduino.h>
#include <CommandMessage.h>

namespace Messages
{
class CommandMessageConsumer : public OSC::MessageConsumer<OSC::StructMessage<CommandMessage, uint32_t>>
{
private:
    const char *_pattern;
    QueueHandle_t _queue;

public:
    bool queueExhausted = false;

    CommandMessageConsumer()
    {
    }
    CommandMessageConsumer(const char *pattern, QueueHandle_t queue)
    {
        _pattern = pattern;
        _queue = queue;
    }

    const char *pattern()
    {
        return _pattern;
    }

    void callbackMessage(OSC::StructMessage<CommandMessage, uint32_t> *message)
    {
        // failed to insert into queue, probably due to high traffic
        // flagging this exhaustion occurance for debugging
        if (xQueueSend(_queue, &message->messageStruct, 0) == errQUEUE_FULL)
        {
            queueExhausted = true;
        }
    }
};
} // namespace Messages