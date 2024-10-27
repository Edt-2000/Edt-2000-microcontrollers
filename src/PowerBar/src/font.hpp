#pragma once

#include <FastLED.h>
#include "./leds.hpp"
#include "./settings.hpp"

#define MAX_DEFAULT_FONT_CHAR 96
#define DEFAULT_FONT_GLYPH_SIZE 5
#define DEFAULT_FONT_GLYPH_SIZE_WITH_KERNING (DEFAULT_FONT_GLYPH_SIZE + 1)
#define DEFAULT_FONT_CHAR_SIZE (DEFAULT_FONT_GLYPH_SIZE_WITH_KERNING * 8)

#define MAX_ICON_FONT_CHAR 2
#define ICON_FONT_GLYPH_SIZE 8
#define ICON_FONT_CHAR_SIZE ((ICON_FONT_GLYPH_SIZE) * 8)

#define FONT_OFFSET 32

#define SPECIFIC_COLOR_SEQUENCE_LENGTH 8

// 5x8 text font
const uint8_t defaultFont[MAX_DEFAULT_FONT_CHAR][DEFAULT_FONT_GLYPH_SIZE] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // space
    {0x00, 0x00, 0x5F, 0x00, 0x00}, // !
    {0x00, 0x07, 0x00, 0x07, 0x00}, // "
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, // #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // $
    {0x23, 0x13, 0x08, 0x64, 0x62}, // %
    {0x36, 0x49, 0x55, 0x22, 0x50}, // &
    {0x00, 0x05, 0x03, 0x00, 0x00}, // '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // )
    {0x14, 0x08, 0x3E, 0x08, 0x14}, // *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // +
    {0x00, 0x50, 0x30, 0x00, 0x00}, // ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // -
    {0x00, 0x60, 0x60, 0x00, 0x00}, // .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // /
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, // :
    {0x00, 0x56, 0x36, 0x00, 0x00}, // ;
    {0x08, 0x14, 0x22, 0x41, 0x00}, // <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // >
    {0x02, 0x01, 0x51, 0x09, 0x06}, // ?
    {0x32, 0x49, 0x79, 0x41, 0x3E}, // @
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
    {0x26, 0x49, 0x49, 0x49, 0x32}, // S - changed from {0x46, 0x49, 0x49, 0x49, 0x31},
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
    {0x3F, 0x40, 0x30, 0x40, 0x3F}, // W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // X
    {0x03, 0x04, 0x78, 0x04, 0x03}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // Z
    {0x00, 0x7F, 0x41, 0x41, 0x00}, // [
    {0x02, 0x04, 0x08, 0x10, 0x20}, // backslash
    {0x00, 0x41, 0x41, 0x7F, 0x00}, // ]
    {0x04, 0x02, 0x01, 0x02, 0x04}, // ^
    {0x80, 0x80, 0x80, 0x80, 0x80}, // _
    {0x00, 0x03, 0x05, 0x00, 0x00}, // `
    {0x20, 0x54, 0x54, 0x54, 0x78}, // a
    {0x7F, 0x48, 0x44, 0x44, 0x38}, // b
    {0x38, 0x44, 0x44, 0x44, 0x20}, // c
    {0x38, 0x44, 0x44, 0x48, 0x7F}, // d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // e
    {0x08, 0x7E, 0x09, 0x01, 0x02}, // f
    {0x0C, 0x52, 0x52, 0x52, 0x3E}, // g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // h
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // i
    {0x20, 0x40, 0x44, 0x3D, 0x00}, // j
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // l
    {0x7C, 0x04, 0x78, 0x04, 0x78}, // m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // o
    {0x7C, 0x14, 0x14, 0x14, 0x08}, // p
    {0x08, 0x14, 0x14, 0x18, 0x7C}, // q
    {0x7C, 0x08, 0x04, 0x04, 0x08}, // r
    {0x48, 0x54, 0x54, 0x54, 0x20}, // s
    {0x04, 0x3F, 0x44, 0x40, 0x20}, // t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // x
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, // y
    {0x44, 0x64, 0x54, 0x4C, 0x44}, // z
    {0x00, 0x08, 0x36, 0x41, 0x00}, // {
    {0x00, 0x00, 0x7F, 0x00, 0x00}, // |
    {0x00, 0x41, 0x36, 0x08, 0x00}, // }
    {0x02, 0x01, 0x02, 0x04, 0x02}  // ~
};

// 8x8 icon font
const uint8_t iconFont[MAX_ICON_FONT_CHAR][ICON_FONT_GLYPH_SIZE] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // space
    {0x0c, 0x1e, 0x3e, 0x7c, 0x3e, 0x1e, 0x0c, 0x00}  // ! -> ❤️
};

const CHSV specificColorSequence[SPECIFIC_COLOR_SEQUENCE_LENGTH] = {
    CHSV(0, 255, 255),
    CHSV(95, 255, 255),
    CHSV(158, 255, 255),
    CHSV(18, 255, 255),
    CHSV(129, 255, 255),
    CHSV(238, 255, 255),
    CHSV(18, 255, 255),
    CHSV(183, 255, 255)};

enum struct TextAlign
{
    left,
    center,
    right
};

struct RenderResult
{
    bool rendered;
    uint8_t size;

    RenderResult() : rendered(0), size(0) {}
    RenderResult(bool rendered, uint8_t size) : rendered(rendered), size(size) {}
};

class FontRendererHelper
{
public:
    bool displayText(const String *text, TextAlign align, int colorIndex)
    {
        return displayText(text, getOffset(text, align), 0, colorIndex);
    }

    bool displayText(const String *text, TextAlign align, int8_t offsetX, int8_t offsetY, int colorIndex)
    {
        return displayText(text, getOffset(text, align) + offsetX, offsetY, colorIndex);
    }

    bool displayText(const String *text, int8_t startX, int8_t startY, int colorIndex)
    {
        return displayText(text, 0, text->length(), startX, startY, colorIndex);
    }

    bool displayText(const String *text, uint8_t offset, uint8_t length, int8_t startX, int8_t startY, int colorIndex)
    {
        auto hasRendered = false;

        uint8_t currentIndex = offset;
        uint8_t textLength = offset + length;
        auto maxTextLength = text->length();

        while (currentIndex < textLength && startX < MAX_WIDTH)
        {
            auto letterColor = getColor(colorIndex, currentIndex, maxTextLength);
            RenderResult renderResult;

            if (globalSettings.font == 0)
            {
                renderResult = drawLetterDefaultFont(text->charAt(currentIndex) - FONT_OFFSET, startX, startY, letterColor);
            }
            else if (globalSettings.font == 1)
            {
                renderResult = drawLetterIconFont(text->charAt(currentIndex) - FONT_OFFSET, startX, startY, letterColor);
            }

            hasRendered = hasRendered || renderResult.rendered;

            currentIndex++;
            startX += renderResult.size;
        }

        return hasRendered;
    }

    int8_t getOffset(const String *text, TextAlign align)
    {
        int8_t offset = 0;
        uint8_t size = globalSettings.font == 1 ? ICON_FONT_GLYPH_SIZE : DEFAULT_FONT_GLYPH_SIZE_WITH_KERNING;

        if (align != TextAlign::left)
        {
            offset = MAX_WIDTH - (text->length() * size);
        }
        if (align == TextAlign::center)
        {
            offset /= 2;
        }

        return offset;
    }

private:
    RenderResult drawLetterDefaultFont(uint8_t letter, int8_t startX, int8_t startY, CRGB color)
    {
        if (letter >= MAX_DEFAULT_FONT_CHAR)
        {
            return RenderResult(false, DEFAULT_FONT_GLYPH_SIZE_WITH_KERNING);
        }

        if (startX < -DEFAULT_FONT_GLYPH_SIZE || startX > MAX_WIDTH)
        {
            return RenderResult(false, DEFAULT_FONT_GLYPH_SIZE_WITH_KERNING);
        }

        for (uint8_t i = 0; i < DEFAULT_FONT_GLYPH_SIZE; i++)
        {
            uint8_t column = defaultFont[letter][i];

            for (uint8_t j = 0; j < 8; j++)
            {
                if (column & (1 << j))
                {
                    uint8_t x = startX + i;
                    uint8_t y = startY + (7 - j);

                    if (x >= 0 && x < MAX_WIDTH && y >= 0 && y < 8)
                    {
                        uint16_t ledIndex = x * 8 + y;
                        leds[ledIndex] = color;
                    }
                }
            }
        }

        return RenderResult(true, DEFAULT_FONT_GLYPH_SIZE_WITH_KERNING);
    }

    RenderResult drawLetterIconFont(uint8_t letter, int8_t startX, int8_t startY, CRGB color)
    {
        if (letter >= MAX_ICON_FONT_CHAR)
        {
            return RenderResult(false, ICON_FONT_GLYPH_SIZE);
        }

        if (startX < -ICON_FONT_GLYPH_SIZE || startX > MAX_WIDTH)
        {
            return RenderResult(false, ICON_FONT_GLYPH_SIZE);
        }

        for (uint8_t i = 0; i < ICON_FONT_GLYPH_SIZE; i++)
        {
            uint8_t column = iconFont[letter][i];

            for (uint8_t j = 0; j < 8; j++)
            {
                if (column & (1 << j))
                {
                    uint8_t x = startX + i;
                    uint8_t y = startY + (7 - j);

                    if (x >= 0 && x < MAX_WIDTH && y >= 0 && y < 8)
                    {
                        uint16_t ledIndex = x * 8 + y;
                        leds[ledIndex] = color;
                    }
                }
            }
        }

        return RenderResult(true, ICON_FONT_GLYPH_SIZE);
    }

    CHSV getColor(int colorIndex, uint8_t letterIndex, uint8_t textLength)
    {
        if (globalSettings.textSplitPosition > 0 && letterIndex >= globalSettings.textSplitPosition)
        {
            colorIndex++;
        }

        auto color = globalSettings.colorAt(colorIndex);

        if (isRainbow(color) && textLength > 0)
        {
            return CHSV((255 / textLength) * letterIndex, 255, 255);
        }
        else if (isSpecificColorSequence(color) && textLength > 0)
        {
            return specificColorSequence[letterIndex % SPECIFIC_COLOR_SEQUENCE_LENGTH];
        }
        else
        {
            return color;
        }
    }

} FontRenderer;

extern FontRendererHelper FontRenderer;
