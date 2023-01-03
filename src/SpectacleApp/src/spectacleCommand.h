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

struct RainbowCommand
{
    // 0 - 127
    uint32_t start;
    uint32_t end;

    // 0 - 255
    uint32_t hue;
    uint32_t deltaHue;
    uint32_t duration;
};

struct VuMeterCommand
{
    // 0 - 127
    uint32_t start;
    uint32_t end;
    uint32_t center;

    // 0 - 255
    uint32_t hue;
    uint32_t deltaHue;
    uint32_t intensity;
};

struct ChaseCommand
{
    // 0 - 255
    uint32_t hue;
    uint32_t speed;
    uint32_t fadeSpeed;
    uint32_t direction;

    CHSV getColor()
    {
        return CHSV(
            hue,
            // make color white when hue = 255
            hue == 255 ? 0x00 : 0xff,
            0xff);
    }
};

struct TheatreChaseCommand
{
    uint32_t hue1;
    uint32_t hue2;
    uint32_t speed;

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
};

struct StroboCommand
{
    // 0 - 255
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

union Commands
{
    SingleColorCommand singleColor;
    DualColorCommand dualColor;
    RainbowCommand rainbow;
    VuMeterCommand vuMeter;
    TwinkleCommand twinkle;
    ChaseCommand chase;
    StroboCommand strobo;

    TheatreChaseCommand theater;
    MarqueeChaseCommand marquee;
    FireCommand fire;
};
enum ColorCommands : uint32_t
{
    // DONE:
    SingleSolid = 0,
    SinglePulse = 1,
    SingleSpark = 7,
    RainbowSolid = 2,
    RainbowPulse = 3,
    RainbowSpark = 8,
    DualSolid = 9,
    DualPulse = 10,
    DualSparkle = 11,
    Twinkle = 5,
    Strobo = 6,
    TheaterChase = 201,
    Fire = 203,

    // TODO:
    Chase = 12,
    VuMeter = 4,

    MarqueeChase = 202,
    FillSolid = 204,
    FillDual = 205,

};
struct SpectacleCommand
{
    ColorCommands mode;

    Commands commands;
};
