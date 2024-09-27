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
            // if (deserializeDoc.containsKey("color3"))
            // {
            //     auto color = deserializeDoc["color3"];
            //     globalSettings.colors[2] = CHSV(color[0], color[1], color[2]);

            //     PrintDebug("Setting color[2] set to ");
            //     PrintDebug(globalSettings.colors[2].h);
            //     PrintDebug(",");
            //     PrintDebug(globalSettings.colors[2].s);
            //     PrintDebug(",");
            //     PrintLnDebug(globalSettings.colors[2].v);
            // }
            // if (deserializeDoc.containsKey("color4"))
            // {
            //     auto color = deserializeDoc["color4"];
            //     globalSettings.colors[3] = CHSV(color[0], color[1], color[2]);

            //     PrintDebug("Setting color[3] set to ");
            //     PrintDebug(globalSettings.colors[3].h);
            //     PrintDebug(",");
            //     PrintDebug(globalSettings.colors[3].s);
            //     PrintDebug(",");
            //     PrintLnDebug(globalSettings.colors[3].v);
            // }
            // if (deserializeDoc.containsKey("color5"))
            // {
            //     auto color = deserializeDoc["color5"];
            //     globalSettings.colors[4] = CHSV(color[0], color[1], color[2]);

            //     PrintDebug("Setting color[4] set to ");
            //     PrintDebug(globalSettings.colors[4].h);
            //     PrintDebug(",");
            //     PrintDebug(globalSettings.colors[4].s);
            //     PrintDebug(",");
            //     PrintLnDebug(globalSettings.colors[4].v);
            // }
            if (deserializeDoc.containsKey("led"))
            {
                globalSettings.led = deserializeDoc["led"];

                PrintDebug("Setting led set to ");
                PrintLnDebug(globalSettings.led);
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
            // if (deserializeDoc.containsKey("brightness"))
            // {
            //     globalSettings.brightness = deserializeDoc["brightness"];

            //     PrintDebug("Setting brightness set to ");
            //     PrintLnDebug(globalSettings.brightness);
            // }
            // if (deserializeDoc.containsKey("size"))
            // {
            //     globalSettings.size = deserializeDoc["size"];

            //     PrintDebug("Setting size set to ");
            //     PrintLnDebug(globalSettings.size);
            // }
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
