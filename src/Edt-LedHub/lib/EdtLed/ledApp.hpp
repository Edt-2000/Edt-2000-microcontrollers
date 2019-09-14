#include <Arduino.h>
#include "core.hpp"

struct TaskConfig
{
    int channel;
    int delay;
    TaskConfig(int channel, int delay) : channel(channel), delay(delay) {}
};

TaskConfig *task1;
TaskConfig *task2;

void blinkTask(void *parameters)
{
    auto config = (TaskConfig *)parameters;

    bool on = false;
    int channel = config->channel;
    int delayTime = config->delay;

    while (true)
    {
        digitalWrite(channel, on);

        on = !on;

        delay(delayTime);
    }
}

class LedApp : public CoreApp
{
private:
    EthernetClient _ethernetClient;
public: 
    int setupCount = 0;

    LedApp(const char * ledAppHostname) : _ethernetClient(ledAppHostname) {}

    void startSetupNetwork() {
        _ethernetClient.setup();
    }

    bool setupNetwork()
    {
        return _ethernetClient.isConnected();
    }

    void startSetupOsc() {

    }

    bool setupOsc()
    {
        delay(100);
        return ++setupCount > 40;
    }

    void startApp()
    {
        pinMode(0, OUTPUT);
        pinMode(1, OUTPUT);

        task1 = new TaskConfig(0, 500);
        task2 = new TaskConfig(1, 10000);

        xTaskCreate(&blinkTask, "blinkTask1", 2048, (void *)task1, 10, NULL);
        xTaskCreate(&blinkTask, "blinkTask2", 2048, (void *)task2, 10, NULL);
    }

    void appLoop() {
        
    }
};