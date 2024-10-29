#pragma once

#include <ArduinoJson.h>

#include "../settings.hpp"
#include "../debugging/logger.hpp"

using AnimationHandler = std::function<void(std::string animationName)>;
using StateChangedHandler = std::function<void()>;

class JsonHandlerHelper
{
private:
    AnimationHandler animationCallback;
    StateChangedHandler stateChangedCallback;
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
            if (deserializeDoc.containsKey("text"))
            {
                String text = deserializeDoc["text"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.text = newText;

                PrintDebug("Setting text set to ");
                PrintLnDebug(globalSettings.text);
            }
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
            if (deserializeDoc.containsKey("color3"))
            {
                auto color = deserializeDoc["color3"];
                globalSettings.colors[2] = CHSV(color[0], color[1], color[2]);

                PrintDebug("Setting color[2] set to ");
                PrintDebug(globalSettings.colors[2].h);
                PrintDebug(",");
                PrintDebug(globalSettings.colors[2].s);
                PrintDebug(",");
                PrintLnDebug(globalSettings.colors[2].v);
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
            if (deserializeDoc.containsKey("brightness"))
            {
                globalSettings.brightness = deserializeDoc["brightness"];

                PrintDebug("Setting brightness set to ");
                PrintLnDebug(globalSettings.brightness);

                if (globalSettings.brightness <= 0)
                {
                    globalSettings.brightness = 1;
                }
            }
            if (deserializeDoc.containsKey("font"))
            {
                globalSettings.font = deserializeDoc["font"];

                PrintDebug("Setting font set to ");
                PrintLnDebug(globalSettings.font);
            }
            if (deserializeDoc.containsKey("variant"))
            {
                globalSettings.variant = deserializeDoc["variant"];

                PrintDebug("Setting variant set to ");
                PrintLnDebug(globalSettings.variant);
            }
            if (deserializeDoc.containsKey("colorCount"))
            {
                globalSettings.colorCount = deserializeDoc["colorCount"];

                if (globalSettings.colorCount == 0)
                {
                    globalSettings.colorCount = 1;
                }
                else if (globalSettings.colorCount > 3)
                {
                    globalSettings.colorCount = 3;
                }

                PrintDebug("Setting colorCount set to ");
                PrintLnDebug(globalSettings.colorCount);
            }
            if (deserializeDoc.containsKey("flashCount"))
            {
                globalSettings.flashCount = deserializeDoc["flashCount"];

                if (globalSettings.flashCount <= 0)
                {
                    globalSettings.flashCount = 1;
                }

                PrintDebug("Setting flashCount set to ");
                PrintLnDebug(globalSettings.flashCount);
            }
            if (deserializeDoc.containsKey("textSplitPosition"))
            {
                globalSettings.textSplitPosition = deserializeDoc["textSplitPosition"];

                if (globalSettings.textSplitPosition < 0)
                {
                    globalSettings.textSplitPosition = 0;
                }

                PrintDebug("Setting textSplitPosition set to ");
                PrintLnDebug(globalSettings.textSplitPosition);
            }
        }

        if (isAnimation)
        {
            if (animationCallback)
            {
                animationCallback(deserializeDoc["animation"]);
            }
        }

        if (stateChangedCallback)
        {
            stateChangedCallback();
        }
    }

    String serialize(const char *animationName)
    {
        serializeDoc.clear();
        if (animationName != nullptr)
        {
            PrintDebug("animation is ");
            PrintLnDebug(animationName);
            serializeDoc["animation"] = animationName;
        }

        PrintDebug("text is ");
        PrintLnDebug(globalSettings.text);
        serializeDoc["text"] = globalSettings.text;

        PrintDebug("color[0] is ");
        PrintDebug(globalSettings.colors[0].h);
        PrintDebug(",");
        PrintDebug(globalSettings.colors[0].s);
        PrintDebug(",");
        PrintLnDebug(globalSettings.colors[0].v);
        serializeDoc["color1"][0] = globalSettings.colors[0].h;
        serializeDoc["color1"][1] = globalSettings.colors[0].s;
        serializeDoc["color1"][2] = globalSettings.colors[0].v;

        PrintDebug("color[1] is ");
        PrintDebug(globalSettings.colors[1].h);
        PrintDebug(",");
        PrintDebug(globalSettings.colors[1].s);
        PrintDebug(",");
        PrintLnDebug(globalSettings.colors[1].v);
        serializeDoc["color2"][0] = globalSettings.colors[1].h;
        serializeDoc["color2"][1] = globalSettings.colors[1].s;
        serializeDoc["color2"][2] = globalSettings.colors[1].v;

        PrintDebug("color[2] is ");
        PrintDebug(globalSettings.colors[2].h);
        PrintDebug(",");
        PrintDebug(globalSettings.colors[2].s);
        PrintDebug(",");
        PrintLnDebug(globalSettings.colors[2].v);
        serializeDoc["color3"][0] = globalSettings.colors[2].h;
        serializeDoc["color3"][1] = globalSettings.colors[2].s;
        serializeDoc["color3"][2] = globalSettings.colors[2].v;

        PrintDebug("speed is ");
        PrintLnDebug(globalSettings.speed);
        serializeDoc["speed"] = globalSettings.speed;

        PrintDebug("brightness is ");
        PrintLnDebug(globalSettings.brightness);
        serializeDoc["brightness"] = globalSettings.brightness;

        PrintDebug("font is ");
        PrintLnDebug(globalSettings.font);
        serializeDoc["font"] = globalSettings.font;

        auto json = String();

        serializeJson(serializeDoc, json);

        return json;
    }

    void onAnimation(AnimationHandler callback)
    {
        animationCallback = callback;
    }

    void onStateChange(StateChangedHandler callback)
    {
        stateChangedCallback = callback;
    }
} JsonHandler;

extern JsonHandlerHelper JsonHandler;
