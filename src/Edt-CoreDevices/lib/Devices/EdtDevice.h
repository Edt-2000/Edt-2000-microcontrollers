#pragma once

#include "CommandMessage.h"

namespace Devices
{
class EdtDevice
{
public:
    virtual void init() = 0;
    virtual void handleMessage(Messages::CommandMessage message) = 0;
    virtual void animate() = 0;
};
} // namespace Device