#pragma once

#include <vector>
#include <EEPROM.h>

#include "devices/dmxDriver.hpp"
#include "devices/dmxDriverConfig.hpp"
#include "serial/dmxSerial.hpp"
#include "devices/ledSpotDriver.hpp"

class DmxDevicesHelper
{
public:
    void init()
    {
        EEPROM.begin(255);
        DmxSerial::Initialize(DmxDirection::output);

        auto led1 = new LedSpotDriver();
        led1->initialize(10, 0, 255, 0);
        _devices.push_back(led1);
        
        auto led2 = new LedSpotDriver();
        led2->initialize(16, 30, 255, 0);
        _devices.push_back(led2);
    }

    void loop()
    {
        for (auto & device : _devices) {
            device->loop();
        }
    }
private:
    std::vector<DmxDriver*> _devices;

} DmxDevices;

extern DmxDevicesHelper DmxDevices;
