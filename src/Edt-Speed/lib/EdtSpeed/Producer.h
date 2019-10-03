#pragma once

#include "IMessage.h"
#include "Message.h"
#include "OSCStructMessage.h"
#include "OSCMessageProducer.h"

class Producer : public OSC::MessageProducer
{
private:
    OSC::StructMessage<Message, uint32_t> _message;

public:
    OSC::IMessage *generateMessage()
    {
        return &_message;
    }

    void loop()
    {
    }
};