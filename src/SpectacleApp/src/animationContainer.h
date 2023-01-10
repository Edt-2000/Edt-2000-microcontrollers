#pragma once

#include "baseAnimation.h"
#include "core.h"
#include <list>

class AnimationContainer
{
private:
    static const uint8_t _maxAnimations = 24;

public:
    std::list<BaseAnimation *> animations;

    void addAnimation(BaseAnimation *animation)
    {
        if (animations.size() >= _maxAnimations)
        {
            return;
        }

        animations.push_back(animation);
    }

    void insertAnimation(BaseAnimation *animation)
    {
        animations.push_front(animation);
    }

    void resetAnimations()
    {
        animations.clear();
    }

    void animate()
    {
        for (auto animation : animations)
        {
            animation->animate();
        }

        animations.remove_if([=](BaseAnimation *animation)
                             { return animation->finished; });
    }
};
