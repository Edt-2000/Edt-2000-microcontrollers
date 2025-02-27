#pragma once

#include <iostream>
#include <map>

#include "animation.hpp"
#include "leds.hpp"
#include "time.hpp"
#include "debugging/logger.hpp"

class AnimatorHelper
{
private:
    std::map<std::string, Animation *> animations;

    // current animation that's active - can be null
    Animation *currentAnimation = nullptr;

public:
    void addAnimation(Animation *animation)
    {
        animations[animation->name()] = animation;
    }

    void changeAnimation(std::string animationName)
    {
        PrintDebug("Animation requested: ");
        PrintLnDebug(animationName.c_str());

        auto foundAnimation = animations.find(animationName);
        if (foundAnimation == animations.end())
        {
            PrintLnDebug("Animation not found.");
            return;
        }

        auto animation = foundAnimation->second;

        if (currentAnimation == animation)
        {
            PrintLnInfo("Stopping animation.");

            currentAnimation->stop();
            currentAnimation = nullptr;

            Time.interrupt();
            return;
        }
        else if (currentAnimation != nullptr)
        {
            PrintDebug("Stopping animation ");
            PrintDebug(currentAnimation->name());
            PrintLnDebug("..");

            currentAnimation->stop();
            Time.interrupt();
        }

        PrintLnInfo("Starting animation..");
        animation->start();

        currentAnimation = animation;
    }

    void loop()
    {
        Time.loop();

        // copy animation pointer over to avoid race conditions
        auto animation = currentAnimation;
        if (animation != nullptr)
        {
            if (animation->isActive())
            {
                animation->loop();
            }
            else
            {
                animation->stopped();

                // animation has finished
                currentAnimation = nullptr;
            }
        }
    }

    const char *currentAnimationName()
    {
        if (currentAnimation != nullptr)
        {
            return currentAnimation->name();
        }
        else
        {
            return nullptr;
        }
    }
} Animator;

extern AnimatorHelper Animator;
