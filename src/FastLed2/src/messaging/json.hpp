#pragma once

#include <ArduinoJson.h>

#include "../settings.hpp"
#include "../debugging/logger.hpp"

using AnimationHandler = std::function<void(std::string animationName)>;
AnimationHandler animationCallback;

JsonDocument doc;

class JsonDeserializerHelper
{
public:
    void deserialize(uint8_t *data)
    {
        auto error = deserializeJson(doc, data);

        if (!error)
        {
            auto isAnimation = doc.containsKey("animation");
            auto isSettings = !isAnimation || (isAnimation && doc.size() > 1);

            if (isSettings)
            {
                if (doc.containsKey("text"))
                {
                    globalSettings.text = doc["text"];

                    PrintDebug("Setting text set to ");
                    PrintLnDebug(globalSettings.text);
                }
                if (doc.containsKey("color1"))
                {
                    auto color = doc["color1"];
                    globalSettings.colors[0] = CHSV(color[0], color[1], color[2]);

                    PrintDebug("Setting color[0] set to ");
                    PrintDebug(globalSettings.colors[0].h);
                    PrintDebug(",");
                    PrintDebug(globalSettings.colors[0].s);
                    PrintDebug(",");
                    PrintLnDebug(globalSettings.colors[0].v);
                }
                if (doc.containsKey("color2"))
                {
                    auto color = doc["color2"];
                    globalSettings.colors[1] = CHSV(color[0], color[1], color[2]);

                    PrintDebug("Setting color[1] set to ");
                    PrintDebug(globalSettings.colors[1].h);
                    PrintDebug(",");
                    PrintDebug(globalSettings.colors[1].s);
                    PrintDebug(",");
                    PrintLnDebug(globalSettings.colors[1].v);
                }
                if (doc.containsKey("color3"))
                {
                    auto color = doc["color3"];
                    globalSettings.colors[2] = CHSV(color[0], color[1], color[2]);

                    PrintDebug("Setting color[2] set to ");
                    PrintDebug(globalSettings.colors[2].h);
                    PrintDebug(",");
                    PrintDebug(globalSettings.colors[2].s);
                    PrintDebug(",");
                    PrintLnDebug(globalSettings.colors[2].v);
                }
                if (doc.containsKey("color4"))
                {
                    auto color = doc["color4"];
                    globalSettings.colors[3] = CHSV(color[0], color[1], color[2]);

                    PrintDebug("Setting color[3] set to ");
                    PrintDebug(globalSettings.colors[3].h);
                    PrintDebug(",");
                    PrintDebug(globalSettings.colors[3].s);
                    PrintDebug(",");
                    PrintLnDebug(globalSettings.colors[3].v);
                }
                if (doc.containsKey("color5"))
                {
                    auto color = doc["color5"];
                    globalSettings.colors[4] = CHSV(color[0], color[1], color[2]);

                    PrintDebug("Setting color[4] set to ");
                    PrintDebug(globalSettings.colors[4].h);
                    PrintDebug(",");
                    PrintDebug(globalSettings.colors[4].s);
                    PrintDebug(",");
                    PrintLnDebug(globalSettings.colors[4].v);
                }
                if (doc.containsKey("speed"))
                {
                    globalSettings.speed = doc["speed"];
                    if (globalSettings.speed == 0)
                    {
                        globalSettings.speed = 1;
                    }

                    PrintDebug("Setting speed set to ");
                    PrintLnDebug(globalSettings.speed);
                }
                if (doc.containsKey("brightness"))
                {
                    globalSettings.brightness = doc["brightness"];

                    PrintDebug("Setting brightness set to ");
                    PrintLnDebug(globalSettings.brightness);
                }
                if (doc.containsKey("size"))
                {
                    globalSettings.size = doc["size"];

                    PrintDebug("Setting size set to ");
                    PrintLnDebug(globalSettings.size);
                }
            }

            if (isAnimation)
            {
                if (animationCallback)
                {
                    animationCallback(doc["animation"]);
                }
            }
        }
    }

    void onAnimation(AnimationHandler callback)
    {
        animationCallback = callback;
    }
} JsonDeserializer;

extern JsonDeserializerHelper JsonDeserializer;
