/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file format.cpp
 *
 * Formatting functions
 *
 */

#include <format.hpp>

constexpr char hextable[] = "0123456789ABCDEF";

namespace util {

std::span<char> appendString(std::span<char> buffer, std::span<char> string) {
  std::span<char>::iterator output = buffer.begin();
  std::span<char>::iterator input = string.begin();

  while (output != buffer.end() - 1 && input != string.end() && *input != '\0') {
    *output = *input;
    output++;
    input++;
  }
  if (output == buffer.end() - 1)
    *output = '\0';
  return std::span<char>(output, buffer.end());
}

std::span<char> appendDigit(std::span<char> buffer, const std::uint8_t data) {
  std::span<char>::iterator output = buffer.begin();
  if (output != buffer.end() - 1) {
    *output = hextable[data & 0x0F];
    output++;
  }
  if (output == buffer.end() - 1)
    *output = '\0';
  return std::span<char>(output, buffer.end());
}

}  // namespace util