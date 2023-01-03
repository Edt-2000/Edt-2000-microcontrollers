#pragma once

#include "core.h"
#include "spectacleDevice.h"

class SpectacleDevice;

class BaseAnimation
{
public:
    bool finished = false;
    void virtual animate(SpectacleDevice *device) = 0;
};
