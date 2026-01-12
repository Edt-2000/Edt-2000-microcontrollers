#pragma once

#include <ArduinoJson.h>
#include <EEPROM.h>
#include <list>
#include <memory>

#include "devices/dmxDriver.hpp"
#include "devices/dmxDriverConfig.hpp"
#include "serial/dmxSerial.hpp"
#include "storage/dmxStorage.hpp"

#include "devices/fixedSingleChannelDriver.hpp"
#include "devices/jbSystemLedPar56.hpp"
#include "devices/ledSpotDriver.hpp"
#include "devices/showTecCompactParDriver.hpp"
#include "devices/threeChannelLedDriver.hpp"

class DmxDevicesHelper
{
public:
    void init()
    {
        DmxStorage::init();
        DmxSerial::Initialize(DmxDirection::output);

        auto deviceCount = DmxStorage::getDeviceCount();
        if (deviceCount == 0) {
            return;
        }
        
        uint8_t deviceSpacing = 60 / deviceCount;

        for (uint8_t i = 0; i < deviceCount; i++) {
            auto config = DmxStorage::getDeviceConfig(i);

            auto led = getDriver(config.type);
            led->initialize(config.address, i * deviceSpacing, config.maximumBrightness, config.minimumBrightness);

            _devices.push_back(led);
        }
    }

    void loop()
    {
        for (auto &device : _devices)
        {
            device->loop();
        }
    }

    void handleConfig(JsonDocument document)
    {
        for (auto& device : _devices)
        {
            delete device;
        }
        _devices.clear();

        auto dmxDevices = document["dmx"].as<JsonArray>();
        uint8_t deviceCount = dmxDevices.size();

        if (deviceCount == 0)
        {
            deviceCount = 1;
        }

        uint8_t deviceSpacing = 60 / deviceCount;

        uint8_t index = 0;

        DmxStorage::clearDeviceConfig();

        for (auto device : dmxDevices)
        {
            auto type = device["type"].as<std::string>();
            auto deviceType = getType(type);

            PrintDebug("Adding dmx device ");
            PrintLnDebug(type.c_str());

            auto address = device["address"].as<uint16_t>();
            auto min = device["minimumBrightness"].as<uint8_t>();
            auto max = device["maximumBrightness"].as<uint8_t>();

            if (max == 0) {
                max = 255;
            }
            if (min >= max) {
                min = 0;
                max = 255;
            }

            auto led = getDriver(deviceType);
            led->initialize(address, index * deviceSpacing, max, min);

            _devices.push_back(led);

            auto config = DmxDriverConfig();
            config.type = deviceType;
            config.address = address;
            config.minimumBrightness = min;
            config.maximumBrightness = max;

            DmxStorage::setDeviceConfig(config);

            index++;
        }
    }

    DmxDeviceType getType(std::string type)
    {
        if (type == "LedSpot")
        {
            return DmxDeviceType::LedSpot;
        }
        else if (type == "ThreeChannelLed")
        {
            return DmxDeviceType::ThreeChannelLed;
        }
        else if (type == "FixedSingleChannel")
        {
            return DmxDeviceType::FixedSingleChannel;
        }
        else if (type == "ShowTecCompactPar8channel")
        {
            return DmxDeviceType::ShowTecCompactPar8channel;
        }
        else if (type == "ShowTecCompactPar4channel")
        {
            return DmxDeviceType::ShowTecCompactPar4channel;
        }
        else if (type == "ShowTecCompactPar3channel")
        {
            return DmxDeviceType::ShowTecCompactPar3channel;
        }
        else if (type == "JbSystemLedPar56")
        {
            return DmxDeviceType::JbSystemLedPar56;
        }

        return DmxDeviceType::FixedSingleChannel;
    }

    DmxDriver *getDriver(DmxDeviceType type)
    {
        if (type == DmxDeviceType::LedSpot)
        {
            return new LedSpotDriver();
        }
        else if (type == DmxDeviceType::ThreeChannelLed)
        {
            return new ThreeChannelLedDriver();
        }
        else if (type == DmxDeviceType::FixedSingleChannel)
        {
            return new FixedSingleChannelDriver();
        }
        else if (type == DmxDeviceType::ShowTecCompactPar8channel)
        {
            return new ShowTecCompactParDriver(8);
        }
        else if (type == DmxDeviceType::ShowTecCompactPar4channel)
        {
            return new ShowTecCompactParDriver(4);
        }
        else if (type == DmxDeviceType::ShowTecCompactPar3channel)
        {
            return new ShowTecCompactParDriver(3);
        }
        else if (type == DmxDeviceType::JbSystemLedPar56)
        {
            return new JbSystemLedPar56Driver();
        }

        return new FixedSingleChannelDriver();
    }

private:
    std::list<DmxDriver *> _devices;

} DmxDevices;

extern DmxDevicesHelper DmxDevices;
