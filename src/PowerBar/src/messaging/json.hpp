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
            if (deserializeDoc.containsKey("text1"))
            {
                String text = deserializeDoc["text1"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.texts[0] = newText;

                globalSettings.textCount = 1;

                PrintDebug("Setting texts[0] set to ");
                PrintLnDebug(globalSettings.texts[0]);
            }
            if (deserializeDoc.containsKey("text2"))
            {
                String text = deserializeDoc["text2"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.texts[1] = newText;

                globalSettings.textCount = 2;

                PrintDebug("Setting texts[1] set to ");
                PrintLnDebug(globalSettings.texts[1]);
            }
            if (deserializeDoc.containsKey("text3"))
            {
                String text = deserializeDoc["text3"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.texts[2] = newText;

                globalSettings.textCount = 3;

                PrintDebug("Setting texts[2] set to ");
                PrintLnDebug(globalSettings.texts[2]);
            }
            if (deserializeDoc.containsKey("text4"))
            {
                String text = deserializeDoc["text4"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.texts[3] = newText;

                globalSettings.textCount = 4;

                PrintDebug("Setting texts[3] set to ");
                PrintLnDebug(globalSettings.texts[3]);
            }
            if (deserializeDoc.containsKey("text5"))
            {
                String text = deserializeDoc["text5"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.texts[4] = newText;

                globalSettings.textCount = 5;

                PrintDebug("Setting texts[4] set to ");
                PrintLnDebug(globalSettings.texts[4]);
            }
            if (deserializeDoc.containsKey("text6"))
            {
                String text = deserializeDoc["text6"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.texts[5] = newText;

                globalSettings.textCount = 6;

                PrintDebug("Setting texts[5] set to ");
                PrintLnDebug(globalSettings.texts[5]);
            }
            if (deserializeDoc.containsKey("text7"))
            {
                String text = deserializeDoc["text7"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.texts[6] = newText;

                globalSettings.textCount = 7;

                PrintDebug("Setting texts[6] set to ");
                PrintLnDebug(globalSettings.texts[6]);
            }
            if (deserializeDoc.containsKey("text8"))
            {
                String text = deserializeDoc["text8"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.texts[7] = newText;

                globalSettings.textCount = 8;

                PrintDebug("Setting texts[7] set to ");
                PrintLnDebug(globalSettings.texts[7]);
            }
            if (deserializeDoc.containsKey("text9"))
            {
                String text = deserializeDoc["text9"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.texts[8] = newText;

                globalSettings.textCount = 9;

                PrintDebug("Setting texts[8] set to ");
                PrintLnDebug(globalSettings.texts[8]);
            }
            if (deserializeDoc.containsKey("text10"))
            {
                String text = deserializeDoc["text10"].as<String>();

                // copy text to avoid getting string that references some internal memory in JsonDoc which might get reused
                String newText = String(text);

                globalSettings.texts[9] = newText;

                globalSettings.textCount = 10;

                PrintDebug("Setting texts[9] set to ");
                PrintLnDebug(globalSettings.texts[9]);
            }
            if (deserializeDoc.containsKey("displayAllTexts"))
            {
                globalSettings.displayAllTexts = deserializeDoc["displayAllTexts"] == "true";

                PrintDebug("Setting displayAllTexts set to ");
                PrintLnDebug(globalSettings.displayAllTexts);
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

        PrintDebug("texts[0] is ");
        PrintLnDebug(globalSettings.texts[0]);
        serializeDoc["text1"] = globalSettings.texts[0];

        PrintDebug("texts[1] is ");
        PrintLnDebug(globalSettings.texts[1]);
        serializeDoc["text2"] = globalSettings.texts[1];

        PrintDebug("texts[2] is ");
        PrintLnDebug(globalSettings.texts[2]);
        serializeDoc["text3"] = globalSettings.texts[2];

        PrintDebug("texts[3] is ");
        PrintLnDebug(globalSettings.texts[3]);
        serializeDoc["text4"] = globalSettings.texts[3];

        PrintDebug("texts[4] is ");
        PrintLnDebug(globalSettings.texts[4]);
        serializeDoc["text5"] = globalSettings.texts[4];

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
