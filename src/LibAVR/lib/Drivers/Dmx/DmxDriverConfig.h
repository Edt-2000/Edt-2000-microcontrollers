#pragma once

#include "FadeMode.h"
#include "DmxDriver.h"

namespace Drivers
{
    namespace Dmx
    {
        enum class DmxDeviceType : uint8_t
        {
            Unknown = 0,
            LedSpot = 1,
            ThreeChannelLed = 2,
            ShowTecCompactPar = 3,
            FixedSingleChannel = 4
        };

        struct DmxDriverConfig
        {
        public:
            DmxDeviceType type;
            uint16_t address;
            uint8_t maximumBrightness;
            uint8_t minimumBrightness;
        };
    }
}