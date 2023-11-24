/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/*! \file format.hpp
 *  \brief definitions and for formatting functions
 *
 */

#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <span>
#include <cstdint>

namespace util {
std::span<char> appendString(std::span<char> buffer, std::span<char> string);
std::span<char> appendDigit(std::span<char> buffer, const std::uint8_t data);
}  // namespace util

#endif