#pragma once

#include <EEPROM.h>
#include "../devices/dmxDriverConfig.hpp"

#define COUNTLOCATION 10
#define DEVICELOCATION 11

class DmxStorage
{
public:
    static void init()
    {
        EEPROM.begin(255);
    }

    static void clearDeviceConfig()
	{
		setDeviceCount(0);
	}

    static uint8_t getDeviceCount()
    {
        uint8_t count = 0;

        EEPROM.get(COUNTLOCATION, count);

        return count;
    }

    static void setDeviceCount(uint8_t count)
    {
        EEPROM.put(COUNTLOCATION, count);
        EEPROM.commit();
    }

    static DmxDriverConfig getDeviceConfig(uint8_t nr)
    {
        DmxDriverConfig config;

        EEPROM.get(DEVICELOCATION + (sizeof(DmxDriverConfig) * nr), config);

        return config;
    }

    static void setDeviceConfig(DmxDriverConfig config)
    {
        uint8_t nr = getDeviceCount();

        EEPROM.put(DEVICELOCATION + (sizeof(DmxDriverConfig) * nr), config);
        EEPROM.commit();

        setDeviceCount(nr + 1);
    }
};
