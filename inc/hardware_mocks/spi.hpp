/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file spi.hpp
 *
 * hardware mock SPI class template used for testing drivers but also useful for other things
 *
 */
#ifndef SPI_HPP
#define SPI_HPP

#include <cstdint>
#include <cstddef>
#include <array.hpp>

template <auto& peripheralRegisters, typename chipEnables>
class spi {
 public:
  void init() {
    peripheralRegisters.bits = 0;
    for (auto& x : peripheralRegisters.data) {
      x = 0;
    }
  }
  void transmit(chipEnables chipEnable, uint16_t* data, uint32_t bitCount, bool lastTransaction) {
    size_t currentIndex = 0;
    size_t endIndex = bitCount / (sizeof(uint16_t) * 8);
    uint32_t bitsRemaining = bitCount;
    (void)chipEnable;
    for (; currentIndex < endIndex; currentIndex++) {
      peripheralRegisters.data[currentIndex] = data[currentIndex];
      bitsRemaining -= 16;
    }
    // handle last bits
    uint16_t mask = ~(0xFFFF << bitsRemaining);
    peripheralRegisters.data[currentIndex] = data[currentIndex] & mask;
    peripheralRegisters.bits = bitCount;
    (void)lastTransaction;
  }
  // TODO transceive
  // TODO receive
 private:
};

#endif