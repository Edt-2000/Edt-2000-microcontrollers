#pragma once

#include <ArduinoJson.h>

#include "../settings.hpp"
#include "../debugging/logger.hpp"

using AnimationHandler = std::function<void(std::string animationName)>;

class JsonHandlerHelper
{
private:
    AnimationHandler animationCallback;
    JsonDocument serializeDoc;
    JsonDocument deserializeDoc;

public:
    void deserialize(uint8_t *data)
    {
        deserializeDoc.clear();
        auto error = deserializeJson(deserializeDoc, data);

        if (error)
        {
            PrintLnInfo("Error deserializing");
            return;
        }

        auto isAnimation = deserializeDoc.containsKey("animation");
        PrintDebug("Message has animation ");
        PrintLnDebug(isAnimation);

        auto isSettings = !isAnimation || (isAnimation && deserializeDoc.size() > 1);
        PrintDebug("Message has settings ");
        PrintLnDebug(isSettings);

        if (isSettings)
        {
            if (deserializeDoc.containsKey("color1"))
            {
                auto color = deserializeDoc["color1"];
                globalSettings.colors[0] = CHSV(color[0], color[1], color[2]);

                PrintDebug("Setting color[0] set to ");
                PrintDebug(globalSettings.colors[0].h);
                PrintDebug(",");
                PrintDebug(globalSettings.colors[0].s);
                PrintDebug(",");
                PrintLnDebug(globalSettings.colors[0].v);
            }
            if (deserializeDoc.containsKey("color2"))
            {
                auto color = deserializeDoc["color2"];
                globalSettings.colors[1] = CHSV(color[0], color[1], color[2]);

                PrintDebug("Setting color[1] set to ");
                PrintDebug(globalSettings.colors[1].h);
                PrintDebug(",");
                PrintDebug(globalSettings.colors[1].s);
                PrintDebug(",");
                PrintLnDebug(globalSettings.colors[1].v);
            }
            if (deserializeDoc.containsKey("speed"))
            {
                globalSettings.speed = deserializeDoc["speed"];
                if (globalSettings.speed == 0)
                {
                    globalSettings.speed = 1;
                }

                PrintDebug("Setting speed set to ");
                PrintLnDebug(globalSettings.speed);
            }
            if (deserializeDoc.containsKey("fade"))
            {
                globalSettings.fade = deserializeDoc["fade"];

                PrintDebug("Setting fade set to ");
                PrintLnDebug(globalSettings.fade);
            }
            if (deserializeDoc.containsKey("percentage"))
            {
                globalSettings.percentage = deserializeDoc["percentage"];

                PrintDebug("Setting percentage set to ");
                PrintLnDebug(globalSettings.percentage);
            }
            if (deserializeDoc.containsKey("angle"))
            {
                globalSettings.angle = deserializeDoc["angle"];

                PrintDebug("Setting angle set to ");
                PrintLnDebug(globalSettings.angle);
            }
        }

        if (isAnimation)
        {
            if (animationCallback)
            {
                animationCallback(deserializeDoc["animation"]);
            }
        }
    }

    void onAnimation(AnimationHandler callback)
    {
        animationCallback = callback;
    }
} JsonHandler;

extern JsonHandlerHelper JsonHandler;
