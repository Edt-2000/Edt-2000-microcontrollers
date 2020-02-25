#pragma once

#include <Animation.h>
#include <list>

namespace Animations
{
class Animations
{
private:
    static const uint8_t _maxAnimations = 12;

public:
    std::list<Animation> animations;

    uint8_t activeAnimations()
    {
        return animations.size();
    }

    void addAnimation(Animation animation)
    {
        if (animations.size() >= _maxAnimations)
        {
            return;
        }

        animations.push_back(animation);
    }

    void insertAnimation(Animation animation)
    {
        animations.push_front(animation);
    }

    Animation *getAnimation(AnimationType animationType)
    {
        for (auto &animation : animations)
        {
            if (animation.type == animationType)
            {
                return &animation;
            }
        }

        return nullptr;
    }

    void removeAnimation(AnimationType animationType)
    {
        animations.remove_if([=](const Animation &animation) { return animation.type == animationType; });
    }

    void removeAnimation(uint8_t animationNr)
    {
        uint8_t index = 0;
        animations.remove_if([=](const Animation &animation) mutable { return index++ == animationNr; });
    }

    void removeAnimation(Animation animationToRemove)
    {
        animations.remove_if([=](const Animation &animation) { return animation.type == animationToRemove.type && animation.state == animationToRemove.state; });
    }

    void resetAnimations()
    {
        animations.clear();
    }
};
} // namespace Animations