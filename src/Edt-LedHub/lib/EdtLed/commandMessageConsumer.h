#include "OSCArduino.h"
#include "commandMessage.h"
#include "fastLedTask.h"

class CommandMessageConsumer : public OSC::MessageConsumer<OSC::StructMessage<OSC::CommandMessage, uint32_t>>
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

    void callbackMessage(OSC::StructMessage<OSC::CommandMessage, uint32_t> *message)
	{
        Serial.println("MESSAGE");
        Serial.println(message->messageStruct.command);
        Serial.println(message->messageStruct.commands.twinkle.start);
        Serial.println(message->messageStruct.commands.twinkle.end);
        Serial.println(message->messageStruct.commands.twinkle.hue);
        Serial.println(message->messageStruct.commands.twinkle.intensity);
        
        xQueueSend(_queue, &message->messageStruct, 0);
	}
};