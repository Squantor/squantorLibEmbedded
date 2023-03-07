/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file spi_regs.hpp
 *
 * mock SPI class data structure
 *
 */
#ifndef SPI_REGS_HPP
#define SPI_REGS_HPP

namespace registers {
template <size_t N>
struct spiRegisters {
  uint32_t bits;
  util::array<uint16_t, N> data;
};
}  // namespace registers

#endif