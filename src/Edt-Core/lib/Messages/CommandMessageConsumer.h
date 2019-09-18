#pragma once

#include <Blinker.h>
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
    CommandMessageConsumer(const char *pattern, QueueHandle_t queue) : MessageConsumer()
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
        if (xQueueSend(_queue, &message->messageStruct, 0))
        {
            // queue exhausted
            // App::Blinker::signalFailure();
        }
    }
};
} // namespace Messages