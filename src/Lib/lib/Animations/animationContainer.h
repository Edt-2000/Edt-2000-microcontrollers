#pragma once

#include "baseAnimation.h"
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

    bool animate(bool progressAnimation)
    {
        bool shouldOutput = false;

        for (auto animation : animations)
        {
            bool output = animation->animate(progressAnimation);
            shouldOutput = shouldOutput || output;
        }

        animations.remove_if([=](BaseAnimation *animation)
                             { if (animation->finished) { delete animation; return true; } return false; });

        return shouldOutput;   
    }
};
