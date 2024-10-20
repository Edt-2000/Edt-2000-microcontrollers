#pragma once

#include "DmxDriver.h"

enum class DmxDeviceType : uint8_t
{
    Unknown = 0,
    LedSpot = 1,
    ThreeChannelLed = 2,
    ShowTecCompactPar8channel = 3,
    FixedSingleChannel = 4,
    ShowTecCompactPar4channel = 5,
    ShowTecCompactPar3channel = 6,
    JbSystemLedPar56 = 7
};

struct DmxDriverConfig
{
public:
    DmxDeviceType type;
    uint16_t address;
    uint8_t maximumBrightness;
    uint8_t minimumBrightness;
};
