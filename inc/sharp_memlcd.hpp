/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 *\file sharp_memlcd.hpp
 * 
 * Driver class template for sharp memory LCD's
 * 
 */ 
#ifndef SHARP_MEMLCD_HPP
#define SHARP_MEMLCD_HPP

#include <cstdint>
#include <cstddef>
#include <array.hpp>

namespace util
{
    template <int xSize, int ySize>
    struct lcdConfig
    {
        static const int maxX = xSize;
        static const int maxY = ySize;
    };

    // few LCD configurations predefined
    using LS010B7DH04 = lcdConfig<128, 128>;
    using LS013B4DN04 = lcdConfig<96, 96>;
    using LS013B7DH05 = lcdConfig<144, 168>;
    using LS027B7DH01 = lcdConfig<400, 200>;

    template <typename config>
    struct sharpMemLcd
    {
        void init(void)
        {
            static_assert(config::maxX > 0, "display cant have zero X");
            static_assert(config::maxY > 0, "display cant have zero Y");
            // TODO static asserts if display X is not multiple of 16
            // initialize the LCD specific data of the framebuffer
            for(uint16_t i = 0; i < config::maxY; i++)
            {
                // add M0, M1, M2 bits and line addres to beginning of each line entry
                frameBuffer[computeLineAddres(i)] = 0x8000 | (i+1);
                // clear dummy word as we will use that as a line update flag
                frameBuffer[computeLineAddres(i) + (config::maxX/16)+1] = 0x0000;
            }
        }

        int computeLineAddres(int line)
        {
            return line * ((config::maxX/16)+2);
        }

        void putPixel(uint16_t x, uint16_t y, uint8_t pixel)
        {
            // compute array index from x, and y coordinates
            int index = (x / 16) + 1 + (y * ((config::maxX/16)+2));
            if(pixel == 0)
                frameBuffer[index] = frameBuffer[index] & ~(0x01 << (x & 0xF));
            else
                frameBuffer[index] = frameBuffer[index] | (0x01 << (x & 0xF));            
        }

        void flipVcom()
        {
            for(uint16_t i = 0; i < config::maxY; i++)
            {
                frameBuffer[computeLineAddres(i)] = frameBuffer[computeLineAddres(i)] ^ 0x0002;
            } 
        }

        // Adding two 16 bit words per row for spi data setup and teardown
        array<uint16_t, ((config::maxX/16)+2) * config::maxY> frameBuffer;
    };

};

#endif