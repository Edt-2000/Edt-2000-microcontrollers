#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <list>

#include "animation.hpp"
#include "time.hpp"
#include "debugging/logger.hpp"

class AnimatorHelper
{
private:
    std::map<std::string, std::vector<Animation *>> animations;

    // current animations
    std::list<Animation *> currentAnimations;
    bool mustBeStopped = false;

    const std::function<bool(Animation *)> idle = [](Animation *animation)
    {
        return !animation->isActive();
    };

public:
    void addAnimation(Animation *animation)
    {
        auto name = animation->name();

        if (animations.find(name) == animations.end())
        {
            std::vector<Animation *> container;
            animations[name] = container;
        }

        animations[name].push_back(animation);
    }

    void changeAnimation(std::string animationName)
    {
        PrintDebug("Animation requested: ");
        PrintLnDebug(animationName.c_str());

        auto animation = animations[animationName];
        auto handlesMultipleAnimations = animation.size() > 1;

        auto hasRunningAnimations = currentAnimations.size() > 0;

        if (hasRunningAnimations)
        {
            PrintLnDebug("Has running animations");

            if (mustBeStopped || !handlesMultipleAnimations)
            {
                PrintLnDebug("Stopping animations");
                for (auto animation : currentAnimations)
                {
                    animation->stop();
                }
                currentAnimations.clear();
            }
        }

        mustBeStopped = !handlesMultipleAnimations;

        auto idleAnimations = std::find_if(animation.begin(), animation.end(), idle);

        if (idleAnimations != animation.end())
        {
            PrintLnInfo("Starting animation..");
            auto idleAnimation = idleAnimations[0];

            idleAnimation->start();

            currentAnimations.push_back(idleAnimation);
        }
        else
        {
            PrintLnDebug("Resetting first animation..");

            auto firstAnimation = currentAnimations.front();
            firstAnimation->start();
        }

        Time.interrupt();
    }

    void loop()
    {
        for (auto animation : currentAnimations)
        {
            if (animation->isActive())
            {
                animation->loop();
            }
        }

        currentAnimations.remove_if(idle);

        Time.loop();
    }
} Animator;

extern AnimatorHelper Animator;
