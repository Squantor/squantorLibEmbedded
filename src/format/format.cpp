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
}  // namespace util