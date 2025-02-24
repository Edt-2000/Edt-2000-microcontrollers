#pragma once

#include "../animation.hpp"
#include "../settings.hpp"
#include <FastLED.h>

#include "../leds.hpp"

/**
 * Adapted from MatrixFireFast
 *
 * MatrixFireFast - A fire simulation for NeoPixel (and other?) matrix
 * displays on Arduino (or ESP8266) using FastLED.
 *
 * Author: Patrick Rigney (https://www.toggledbits.com/)
 * Copyright 2020 Patrick H. Rigney, All Rights Reserved.
 *
 * Github: https://github.com/toggledbits/MatrixFireFast
 * License information can be found at the above Github link.
 *
 * Please donate in support of my projects: https://www.toggledbits.com/donate
 *
 * For configuration information and processor selection, please see
 * the README file at the above Github link.
 */

#define MAT_W 8 /* Size (columns) of entire matrix */
#define MAT_H 8 /* and rows */

#define PANELS_W 10 /* Number of panels wide */
#define PANELS_H 1  /* Number of panels tall */

class FireAnimation : public Animation
{
private:
    uint8_t nflare;

public:
    FireAnimation()
    {
    }

    const char *name()
    {
        return "fire";
    }

    bool mustRunSolo()
    {
        return true;
    }

    void start()
    {
        nflare = 0;
        _isActive = true;
    }

    void stop()
    {
        _isActive = false;
    }

    void loop()
    {
        do
        {
            make_fire();

            show();

            delay(66);

        } while (_isActive);
    }

    /* Display size; can be smaller than matrix size, and if so, you can move the origin.
     * This allows you to have a small fire display on a large matrix sharing the display
     * with other stuff. See README at Github. */
    const static uint16_t rows = MAT_H * PANELS_H;
    const static uint16_t cols = MAT_W * PANELS_W;
    const static uint16_t xorg = 0;
    const static uint16_t yorg = 0;

    /* Flare constants */
    const static uint8_t flarerows = 2;    /* number of rows (from bottom) allowed to flare */
    const static uint8_t maxflare = 8;     /* max number of simultaneous flares */
    const static uint8_t flarechance = 50; /* chance (%) of a new flare (if there's room) */
    const static uint8_t flaredecay = 14;  /* decay rate of flare radiation; 14 is good */

    uint8_t pix[rows][cols];

    uint32_t flare[maxflare];

    const static uint8_t phy_h = MAT_W;
    const static uint8_t phy_w = MAT_H;

    static uint16_t pos(uint16_t col, uint16_t row)
    {
        uint16_t phy_x = xorg + (uint16_t)row;
        uint16_t phy_y = yorg + (uint16_t)col;

        return phy_x + phy_y * phy_w;
    }

    static uint32_t isqrt(uint32_t n)
    {
        if (n < 2)
        {
            return n;
        }

        uint32_t smallCandidate = isqrt(n >> 2) << 1;
        uint32_t largeCandidate = smallCandidate + 1;
        return (largeCandidate * largeCandidate > n) ? smallCandidate : largeCandidate;
    }

    // Set pixels to intensity around flare
    void glow(int x, int y, int z)
    {
        int b = z * 10 / flaredecay + 1;
        for (int i = (y - b); i < (y + b); ++i)
        {
            for (int j = (x - b); j < (x + b); ++j)
            {
                if (i >= 0 && j >= 0 && i < rows && j < cols)
                {
                    int d = (flaredecay * isqrt((x - j) * (x - j) + (y - i) * (y - i)) + 5) / 10;
                    uint8_t n = 0;
                    if (z > d)
                    {
                        n = z - d;
                    }
                    if (n > pix[i][j])
                    { // can only get brighter
                        pix[i][j] = n;
                    }
                }
            }
        }
    }

    void newflare()
    {
        if (nflare < maxflare && random(1, 101) <= flarechance)
        {
            int x = random(0, cols);
            int y = random(0, flarerows);
            int z = 10;
            flare[nflare++] = (z << 16) | (y << 8) | (x & 0xff);
            glow(x, y, z);
        }
    }

    /** make_fire() animates the fire display. It should be called from the
     *  loop periodically (at least as often as is required to maintain the
     *  configured refresh rate). Better to call it too often than not enough.
     *  It will not refresh faster than the configured rate. But if you don't
     *  call it frequently enough, the refresh rate may be lower than
     *  configured.
     */
    void make_fire()
    {
        uint16_t i, j;

        // First, move all existing heat points up the display and fade
        for (i = rows - 1; i > 0; --i)
        {
            for (j = 0; j < cols; ++j)
            {
                uint8_t n = 0;
                if (pix[i - 1][j] > 0)
                {
                    n = pix[i - 1][j] - 1;
                }
                pix[i][j] = n;
            }
        }

        // Heat the bottom row
        for (j = 0; j < cols; ++j)
        {
            i = pix[0][j];
            if (i > 0)
            {
                pix[0][j] = random(5, 9);
            }
        }

        // flare
        for (i = 0; i < nflare; ++i)
        {
            int x = flare[i] & 0xff;
            int y = (flare[i] >> 8) & 0xff;
            int z = (flare[i] >> 16) & 0xff;
            glow(x, y, z);
            if (z > 1)
            {
                flare[i] = (flare[i] & 0xffff) | ((z - 1) << 16);
            }
            else
            {
                // This flare is out
                for (int j = i + 1; j < nflare; ++j)
                {
                    flare[j - 1] = flare[j];
                }
                --nflare;
            }
        }
        newflare();

        // Set and draw
        for (i = 0; i < rows; ++i)
        {
            for (j = 0; j < cols; ++j)
            {
                leds[pos(j, i)] = HeatColor(24 * pix[i][j]);
            }
        }
    }
};
