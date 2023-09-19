#pragma once

#include "core.h"

class BaseAnimation
{
public:
    bool fullControl = false;
    bool finished = false;
    bool virtual animate(bool progressAnimation) = 0;
};
