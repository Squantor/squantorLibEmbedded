/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file hardware_mocks.hpp
 *
 * main entrypoint for hardware mocks used by device drivers
 *
 */
#ifndef HARDWARE_MOCKS_HPP
#define HARDWARE_MOCKS_HPP

#include <cstddef>
#include <cstdint>
#include <array.hpp>

namespace util {
namespace hardware_mocks {

#include "hardware_mocks/spi_regs.hpp"
#include "hardware_mocks/spi.hpp"

}  // namespace hardware_mocks
}  // namespace util

#endif