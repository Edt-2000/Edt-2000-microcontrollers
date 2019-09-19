#pragma once

#include "core.h"

const int fastLedCount = 6;
const int rgbLedCount = 0;

const int messageConsumerCount = fastLedCount + rgbLedCount;

// TODO: all these instantiations can be made a bit nicer

// QueueHandle_t queues[messageConsumerCount] = {
//     xQueueCreate(3, sizeof(Messages::CommandMessage)),
//     xQueueCreate(3, sizeof(Messages::CommandMessage)),
//     xQueueCreate(3, sizeof(Messages::CommandMessage)),
//     xQueueCreate(3, sizeof(Messages::CommandMessage)),
//     xQueueCreate(3, sizeof(Messages::CommandMessage)),
//     xQueueCreate(3, sizeof(Messages::CommandMessage))};

// Messages::CommandMessageConsumer messageConsumers[messageConsumerCount] = {
//     {"/F1", queues[0]},
//     {"/F2", queues[1]},
//     {"/F3", queues[2]},
//     {"/F4", queues[3]},
//     {"/F5", queues[4]},
//     {"/F6", queues[5]}};

//Tasks::CommandMessageTask tasks[] = {
auto task1 = Tasks::CommandMessageTask("/R1", &hardwiredRgbLedTask<3, 32, 0, 1>, 5120, 3);
auto task2 = Tasks::CommandMessageTask("/F1", &fastLedTask<APA102, 13, 16, BGR, 59>, 5120, 3);
auto task3 = Tasks::CommandMessageTask("/F2", &fastLedTask<APA102, 2, 16, BGR, 59>, 5120, 3);
auto task4 = Tasks::CommandMessageTask("/F3", &fastLedTask<APA102, 4, 16, BGR, 59>, 5120, 3);
auto task5 = Tasks::CommandMessageTask("/F4", &fastLedTask<APA102, 15, 16, BGR, 59>, 5120, 3);
auto task6 = Tasks::CommandMessageTask("/F5", &fastLedTask<APA102, 14, 16, BGR, 59>, 5120, 3);
auto task7 = Tasks::CommandMessageTask("/F6", &fastLedTask<APA102, 5, 16, BGR, 59>, 5120, 3);

Tasks::CommandMessageTask tasks[] = {
    auto task1 = Tasks::CommandMessageTask("/R1", &hardwiredRgbLedTask<3, 32, 0, 1>, 5120, 3);
auto task2 = Tasks::CommandMessageTask("/F1", &fastLedTask<APA102, 13, 16, BGR, 59>, 5120, 3);
auto task3 = Tasks::CommandMessageTask("/F2", &fastLedTask<APA102, 2, 16, BGR, 59>, 5120, 3);
auto task4 = Tasks::CommandMessageTask("/F3", &fastLedTask<APA102, 4, 16, BGR, 59>, 5120, 3);
auto task5 = Tasks::CommandMessageTask("/F4", &fastLedTask<APA102, 15, 16, BGR, 59>, 5120, 3);
auto task6 = Tasks::CommandMessageTask("/F5", &fastLedTask<APA102, 14, 16, BGR, 59>, 5120, 3);
auto task7 = Tasks::CommandMessageTask("/F6", &fastLedTask<APA102, 5, 16, BGR, 59>, 5120, 3)
}
;

class LedApp : public App::CoreApp
{
private:
public:
    const char *ledAppHostname;
    IPAddress localIp;
    IPAddress subnet;
    IPAddress broadcastIp;
    int broadcastPort;

    OSC::Arduino<OSC::StructMessage<Messages::CommandMessage, uint32_t>> osc;

    LedApp(const char *ledAppHostname, IPAddress localIp, IPAddress subnet, IPAddress broadcastIp, int broadcastPort)
        : ledAppHostname(ledAppHostname),
          localIp(localIp),
          subnet(subnet),
          broadcastIp(broadcastIp),
          broadcastPort(broadcastPort) {}

    void startSetupNetwork()
    {
        EthernetClient::setupEthernet(ledAppHostname, localIp, subnet);
    }

    bool setupNetwork()
    {
        return EthernetClient::ethernetIsConnected();
    }

    void startSetupOsc()
    {
        EthernetClient::setupUdp(broadcastPort);

        osc = OSC::Arduino<OSC::StructMessage<Messages::CommandMessage, uint32_t>>(7, 0);
        osc.bindUDP(&EthernetClient::udp, broadcastIp, broadcastPort);

        osc.addConsumer(&task1.messageConsumer);
        osc.addConsumer(&task2.messageConsumer);
        osc.addConsumer(&task3.messageConsumer);
        osc.addConsumer(&task4.messageConsumer);
        osc.addConsumer(&task5.messageConsumer);
        osc.addConsumer(&task6.messageConsumer);
        osc.addConsumer(&task7.messageConsumer);

        // for (int i = 0; i < sizeof(tasks); i++)
        // {
        //     osc.addConsumer(&tasks[i].messageConsumer);
        // }
    }

    bool setupOsc()
    {
        return true;
    }

    void startApp()
    {
        // for (int i = 0; i < sizeof(tasks); i++)
        // {
        //     tasks[i].start();
        // }
        task1.start();
        task2.start();
        task3.start();
        task4.start();
        task5.start();
        task6.start();
        task7.start();
        // xTaskCreate(&fastLedTask<APA102, 13, 16, BGR, 59>, "fastLedTask1", 10240, (void *)queues[0], 10, NULL);
        // xTaskCreate(&fastLedTask<APA102, 2, 16, BGR, 59>, "fastLedTask2", 10240, (void *)queues[1], 10, NULL);
        // xTaskCreate(&fastLedTask<APA102, 4, 16, BGR, 59>, "fastLedTask3", 10240, (void *)queues[2], 10, NULL);
        // xTaskCreate(&fastLedTask<APA102, 15, 16, BGR, 59>, "fastLedTask4", 10240, (void *)queues[3], 10, NULL);
        // xTaskCreate(&fastLedTask<APA102, 14, 16, BGR, 59>, "fastLedTask5", 10240, (void *)queues[4], 10, NULL);
        // xTaskCreate(&fastLedTask<APA102, 5, 16, BGR, 59>, "fastLedTask6", 10240, (void *)queues[5], 10, NULL);

        // //xTaskCreate(&hardwiredRgbLedTask<3, 32, 0, 1>, "rgbLedTask1", 10240, (void *)queues[6], 10, NULL);

        // rgbTest.start();
    }

    void appLoop()
    {
        osc.loop(time.tOSC);

        if (time.tVISUAL)
        {
            FastLED.show();
        }
    }

    // check for failure modes when the ESP must be reset
    bool appRestartRequired()
    {
        return !EthernetClient::ethernetIsConnected();
    }

    // check for queue exhaustion in the consumers of the OSC messages
    bool appWarningRequired()
    {
        // for (int i = 0; i < sizeof(tasks); i++)
        // {
        //     // if (tasks[i].messageConsumer.queueExhausted)
        //     // {
        //     //     return true;
        //     // }
        // }

        return false;
    }
};