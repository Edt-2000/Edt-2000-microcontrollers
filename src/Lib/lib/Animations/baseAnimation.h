#pragma once

#include "core.h"

class BaseAnimation
{
public:
    bool finished = false;
    void virtual animate() = 0;
};
