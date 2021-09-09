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
    template <size_t lineCount, size_t rowCount>
    struct sharpMemLcd
    {
        void init(void)
        {
            static_assert(lineCount > 0, "display cant have zero lines");
            static_assert(rowCount > 0, "display cant have zero rows");
            // initialize the LCD specific data of the framebuffer
            for(uint16_t i = 0; i < lineCount; i++)
            {
                // add M0, M1, M2 bits and line addres to beginning of each line entry
                frameBuffer[computeLineAddres(i)] = 0x8000 | (i+1);
                // clear dummy word as we will use that as a line update flag
                frameBuffer[computeLineAddres(i) + (rowCount/16)+1] = 0x0000;
            }
        }

        int computeLineAddres(int line)
        {
            return line * ((rowCount/16)+2);
        }

        // Adding two 16 bit words per row for spi data setup and teardown
        array<uint16_t, ((rowCount/16)+2) * lineCount> frameBuffer;
    };

};

#endif