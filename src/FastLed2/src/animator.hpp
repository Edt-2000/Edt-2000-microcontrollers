#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <list>

#include "animation.hpp"
#include "fader.hpp"
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
    const std::function<bool(Animation *)> loopIfNotIdle = [](Animation *animation)
    {
        auto active = animation->isActive();
        if (active) {
            animation->loop();
        }
        return !active;
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

        auto foundAnimations = animations.find(animationName);
        if (foundAnimations == animations.end())
        {
            PrintLnInfo("Animation not found!");
            return;
        }

        auto animation = foundAnimations->second;

        auto isSingular = animation.size() == 1 && animation[0]->mustRunSolo();

        auto hasRunningAnimations = currentAnimations.size() > 0;

        if (hasRunningAnimations)
        {
            PrintLnDebug("Has running animations");

            if (mustBeStopped && currentAnimations.front() == animation[0])
            {
                PrintLnDebug("Stopping current animation");

                currentAnimations.front()->stop();
                
                mustBeStopped = false;

                Time.interrupt();
                return;
            }

            if (mustBeStopped || isSingular)
            {
                PrintLnDebug("Stopping animations");

                for (auto const& animation : currentAnimations)
                {
                    animation->stop();
                }
            }
        }

        if (isSingular)
        {
            PrintLnInfo("Starting singular animation..");

            animation[0]->start();

            mustBeStopped = isSingular;
            currentAnimations.push_back(animation[0]);
            return;
        }

        auto idleAnimations = std::find_if(animation.begin(), animation.end(), idle);

        if (idleAnimations != animation.end())
        {
            PrintLnInfo("Starting animation..");
            auto idleAnimation = idleAnimations[0];

            idleAnimation->start();

            if (idleAnimation->isActive())
            {
                mustBeStopped = isSingular;
                currentAnimations.push_back(idleAnimation);
            }
        }
        else
        {
            PrintLnDebug("Resetting first animation and moving it to the end..");

            mustBeStopped = isSingular;

            auto animation = currentAnimations.front();
            animation->start();

            currentAnimations.pop_front();
            currentAnimations.push_back(animation);
        }

        Time.interrupt();
    }

    void loop()
    {
        Time.loop();

        if (Time.t10ms)
        {
            Fader.loop();
        }

        currentAnimations.remove_if(loopIfNotIdle);
    }
} Animator;

extern AnimatorHelper Animator;
