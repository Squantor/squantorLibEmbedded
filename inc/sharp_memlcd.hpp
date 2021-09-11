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
    template <int xSize, int ySize, int shift>
    struct lcdConfig
    {
        static const int maxX = xSize;      /*!< X size of the LCD */
        static const int maxY = ySize;      /*!< Y size of the LCD */
        static const int addrShift = shift; /*!< amount of shift for putting address in right spot */
    };

    // few example LCD configurations
    using LS010B7DH04 = lcdConfig<128, 128, 8>;
    using LS011B7DH03 = lcdConfig<160, 68, 8>;
    using LS013B4DN04 = lcdConfig<96, 96, 8>;
    using LS013B7DH05 = lcdConfig<144, 168, 8>;
    using LS027B7DH01 = lcdConfig<400, 200, 8>;
    using LS032B7DD02 = lcdConfig<336, 536, 6>;

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
                frameBuffer[computeLineAddres(i)] = 0x01 | (i+1) << config::addrShift;
            }
        }

        int computeLineAddres(int line)
        {
            return line * ((config::maxX/16)+1);
        }

        void putPixel(uint16_t x, uint16_t y, uint8_t pixel)
        {
            // compute array index from x, and y coordinates
            int index = (x / 16) + 1 + (y * ((config::maxX/16)+1));
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
        array<uint16_t, ((config::maxX/16)+1) * config::maxY> frameBuffer;
    };

};

#endif