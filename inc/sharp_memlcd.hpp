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
#include <string.h>
#include <array.hpp>
#include <bitblit.hpp>

namespace util {
template <int xSize, int ySize, int shift>
struct lcdConfig {
  static constexpr inline auto maxX = xSize;      /*!< X size of the LCD */
  static constexpr inline auto maxY = ySize;      /*!< Y size of the LCD */
  static constexpr inline auto addrShift = shift; /*!< amount of shift for putting address in right spot */
};

// few example LCD configurations
using LS010B7DH04 = lcdConfig<128, 128, 8>;
using LS011B7DH03 = lcdConfig<160, 68, 8>;
using LS013B4DN04 = lcdConfig<96, 96, 8>;
using LS013B7DH03 = lcdConfig<128, 128, 8>;
using LS013B7DH05 = lcdConfig<144, 168, 8>;
using LS027B7DH01 = lcdConfig<400, 240, 8>;
using LS032B7DD02 = lcdConfig<336, 536, 6>;

template <typename config>
struct sharpMemLcd {
  void init(void) {
    static_assert(config::maxX > 0, "display cant have zero X");
    static_assert(config::maxY > 0, "display cant have zero Y");
    // TODO static asserts if display X is not multiple of 16
    // clear the buffer, it also sets up the sharp additional bits
    setBuffer(0x0000);
  }

  int computeLineAddres(uint16_t line) {
    return line * ((config::maxX / 16) + 1);
  }

  int computeColumnAddres(uint16_t column) {
    return (column / 16) + 1;
  }

  void putPixel(uint16_t x, uint16_t y, uint8_t pixel) {
    int index = computeColumnAddres(x) + computeLineAddres(y);
    if (pixel == 0)
      frameBuffer[index] = frameBuffer[index] & ~(0x01 << (x & 0xF));
    else
      frameBuffer[index] = frameBuffer[index] | (0x01 << (x & 0xF));
  }

  uint8_t getPixel(const uint8_t *block, uint16_t blockWidth, uint16_t x, uint16_t y) {
    uint8_t mask = 1 << (x & 0x07);
    int index = (x / 8) + (y * (blockWidth / 8));
    return (block[index] & mask);
  }

  void lcdUpdate(auto xferFunction) {
    xferFunction(frameBuffer.begin(), frameBuffer.end());
  }

  void flipVcom(auto xferFunction) {
    // update all vcoms in all bits
    // TODO, change this when doing LCD update with dirty lines
    for (uint16_t i = 0; i < config::maxY; i++) {
      frameBuffer[computeLineAddres(i)] = frameBuffer[computeLineAddres(i)] ^ 0x0002;
    }
    // the first word of the framebuffer contains always a vcom signal
    xferFunction(frameBuffer.begin(), frameBuffer.begin() + 1);
  }

  void setBuffer(uint16_t value) {
    for (uint16_t &frameData : frameBuffer) {
      frameData = value;
    }

    for (uint16_t i = 0; i < config::maxY; i++) {
      // add M0, M1, M2 bits and line addres to beginning of each line entry
      frameBuffer[computeLineAddres(i)] = 0x01 | (i + 1) << config::addrShift;
    }
  }

  // xPos, yPos, blockWidth, blockHeight are in bits!
  void bitBlockTransfer(unsigned int xPos, unsigned int yPos, const uint8_t *block, unsigned int blockWidth,
                        unsigned int blockHeight, bitblitOperation op) {
    // the framebuffer contains some out of band data, fix this
    bitblit2dsmall(frameBuffer.__data, maxX+16, maxY, xPos+16, yPos, block, blockWidth, blockHeight, op);
    // TODO: make lines dirty that have been touched
  }

  // Adding two 16 bit words per row for spi data setup and teardown
  array<uint16_t, ((config::maxX / 16) + 1) * config::maxY> frameBuffer;
  static const uint16_t maxX = config::maxX;
  static const uint16_t maxY = config::maxY;
};

};  // namespace util

#endif