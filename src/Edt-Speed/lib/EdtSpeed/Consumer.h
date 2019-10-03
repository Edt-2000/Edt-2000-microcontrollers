#pragma once

#include "IMessage.h"
#include "Message.h"
#include "OSCStructMessage.h"
#include "OSCMessageConsumer.h"

class Consumer : public OSC::MessageConsumer
{
private:
    OSC::StructMessage<Message, uint32_t> _message;

public:
    const char *pattern()
    {
        return "/O";
    }

    OSC::IMessage *message()
    {
        return &_message;
    }

    void callbackMessage()
    {
    }
};