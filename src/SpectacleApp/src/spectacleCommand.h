#pragma once

#include <OSCArduino.h>

struct SingleColorCommand
{
    uint32_t start;
    uint32_t end;
    uint32_t hue;
    uint32_t saturation;
    uint32_t value;
    uint32_t duration;

    CHSV getColor()
    {
        return CHSV(
            hue,
            // make color white when hue = 255
            hue == 255 ? 0x00 : saturation,
            value);
    }
};

struct TwinkleCommand
{
    uint32_t start;
    uint32_t end;
    uint32_t hue;
    uint32_t intensity;

    CHSV getColor()
    {
        return CHSV(
            hue,
            // make color white when hue = 255
            hue == 255 ? 0x00 : 0xff,
            0xff);
    }
};

struct DualColorCommand
{
    uint32_t start;
    uint32_t end;
    uint32_t hue1;
    uint32_t hue2;
    uint32_t percentage;
    uint32_t duration;

    CHSV getColor1()
    {
        return CHSV(
            hue1,
            // make color white when hue = 255
            hue1 == 255 ? 0x00 : 0xff,
            0xff);
    }
    CHSV getColor2()
    {
        return CHSV(
            hue2,
            // make color white when hue = 255
            hue2 == 255 ? 0x00 : 0xff,
            0xff);
    }
};

struct TheatreChaseCommand
{
    uint32_t hue1;
    uint32_t hue2;
    uint32_t speed;
    uint32_t progress;
};

struct MarqueeChaseCommand
{
    uint32_t speed;
    uint32_t orientation;
    uint32_t hue1;
    uint32_t hue2;
    uint32_t hue3;
    uint32_t hue4;
};

struct FireCommand
{
    uint32_t speed;
    uint32_t progress;
};

struct FillCommand
{
    uint32_t speed;
    uint32_t hue;
}

union Commands
{
    SingleColorCommand singleColor;
    DualColorCommand dualColor;
    TwinkleCommand twinkle;
    TheatreChaseCommand theatre;
    MarqueeChaseCommand marquee;
    FireCommand fire;
};
enum ColorCommands : uint32_t
{
    SingleSolid = 0,
    DualSolid = 9,
    Twinkle = 5,

    TheathreChase = 201,
    MarqueeChase = 202,
    Fire = 203,
    FillSolid = 204,
    FillDual = 205,

};
struct SpectacleCommand
{
    ColorCommands mode;

    Commands commands;
};
