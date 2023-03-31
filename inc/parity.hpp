/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file parity.hpp
 *
 * Contains parity calculation function templates, inspired by:
 * http://www.graphics.stanford.edu/%7Eseander/bithacks.html#ParityParallel
 *
 */
#ifndef PARITY_HPP
#define PARITY_HPP

#include <cstdint>
#include <limits>
#include <type_traits>

namespace util {

/**
 * @brief computes Even parity of a simple type
 *
 * @tparam T type of value, must be unsigned
 * @param value value to calculate parity over
 * @return true parity set
 * @return false parity clear
 */
template <typename T>
bool parityEven(T value) {
  static_assert(std::is_signed<T>::value == false);
  constexpr int bitCnt = std::numeric_limits<T>::digits;
  // XOR is used as a carry less add operation that we progressivly fold bits into eachother
  if constexpr (bitCnt >= 64) value ^= value >> 32;
  if constexpr (bitCnt >= 32) value ^= value >> 16;
  if constexpr (bitCnt >= 16) value ^= value >> 8;
  value ^= value >> 4;
  // we are down to 4 bit, we can use a lookup table to compute the final parity
  value &= 0xf;
  return ((0x9669u >> value) & 1) == 0;
}

/**
 * @brief computes odd parity of a simple type
 *
 * @tparam T type of value, must be unsigned
 * @param value value to calculate parity over
 * @return true parity set
 * @return false parity clear
 */
template <typename T>
bool parityOdd(T value) {
  return !parityEven<T>(value);
}

}  // namespace util

#endif