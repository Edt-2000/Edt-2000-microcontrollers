#pragma once

#include "core.h"

class BaseAnimation
{
public:
    bool finished = false;
    bool virtual animate(bool progressAnimation) = 0;
};
