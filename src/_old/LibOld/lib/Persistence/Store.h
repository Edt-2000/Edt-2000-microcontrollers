#pragma once

#include <EEPROM.h>

struct Config
{
    uint8_t type;
    uint8_t data;
};

class Store
{
private:
public:
    template <typename T>
    T get(uint8_t address){

    };

    uint8_t length()
    {
        return EEPROM.length();
    }
};