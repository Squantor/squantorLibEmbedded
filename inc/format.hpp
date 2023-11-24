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

namespace util {
std::span<char> appendString(std::span<char> buffer, std::span<char> string);
}  // namespace util

#endif