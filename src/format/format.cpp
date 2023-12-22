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

/**
 * @brief Generic decimal conversion routine
 *
 * @param buffer span to append the decimal number to
 * @param data number to translate to decimal and append
 * @param divider division factor to start out with
 * @return span with available space
 */
static std::span<char> appendDecGeneric(std::span<char> buffer, std::uint32_t data, uint32_t divider) {
  bool supressDigits = true;
  std::span result = buffer;
  std::uint32_t idx;
  while (divider > 0) {
    idx = data / divider;
    if (idx != 0)
      supressDigits = false;
    if (!supressDigits)
      result = appendDigit(result, idx);
    data -= idx * divider;
    divider = divider / 10;
  }
  if (supressDigits == true)
    result = appendDigit(result, idx);
  return result;
}

std::span<char> appendChar(std::span<char> buffer, char c) {
  std::span<char>::iterator output = buffer.begin();
  if (output != buffer.end() - 1) {
    *output = c;
    output++;
  }
  *output = '\0';
  return std::span<char>(output, buffer.end());
}

std::span<char> appendString(std::span<char> buffer, std::span<char> string) {
  std::span<char> result = buffer;
  std::span<char>::iterator input = string.begin();

  while (buffer.begin() != buffer.end() && input != string.end() && *input != '\0') {
    result = appendChar(result, *input);
    input++;
  }
  return result;
}

std::span<char> appendDigit(std::span<char> buffer, const std::uint32_t data) {
  std::span<char> result = buffer;
  result = appendChar(result, hextable[data & 0x0F]);
  return result;
}

std::span<char> appendDigit(std::span<char> buffer, const std::int32_t data) {
  std::span<char> result = buffer;
  result = appendChar(result, hextable[data & 0x0F]);
  return result;
}

std::span<char> appendDigit(std::span<char> buffer, const std::uint16_t data) {
  std::span<char> result = buffer;
  result = appendChar(result, hextable[data & 0x0F]);
  return result;
}

std::span<char> appendDigit(std::span<char> buffer, const std::int16_t data) {
  std::span<char> result = buffer;
  result = appendChar(result, hextable[data & 0x0F]);
  return result;
}

std::span<char> appendDigit(std::span<char> buffer, const std::uint8_t data) {
  std::span<char> result = buffer;
  result = appendChar(result, hextable[data & 0x0F]);
  return result;
}

std::span<char> appendDigit(std::span<char> buffer, const std::int8_t data) {
  std::span<char> result = buffer;
  result = appendChar(result, hextable[data & 0x0F]);
  return result;
}

std::span<char> appendHex(std::span<char> buffer, std::uint32_t data) {
  std::span result = buffer;
  for (int i = 0; i < 8; i++) {
    std::uint32_t value = 0xF0000000 & data;
    value = value >> 28;
    result = appendDigit(result, static_cast<std::uint32_t>(value));
    data = data << 4;
  }
  return result;
}

std::span<char> appendHex(std::span<char> buffer, std::uint16_t data) {
  std::span result = buffer;
  for (int i = 0; i < 4; i++) {
    std::uint16_t value = 0xF000 & data;
    value = value >> 12;
    result = appendDigit(result, static_cast<std::uint32_t>(value));
    data = data << 4;
  }
  return result;
}

std::span<char> appendHex(std::span<char> buffer, std::uint8_t data) {
  std::span result = buffer;
  result = appendDigit(result, static_cast<std::uint32_t>(data >> 4));
  result = appendDigit(result, static_cast<std::uint32_t>(data));
  return result;
}

std::span<char> appendDec(std::span<char> buffer, std::uint32_t data) {
  return appendDecGeneric(buffer, data, 1000000000);
}

std::span<char> appendDec(std::span<char> buffer, std::uint16_t data) {
  return appendDecGeneric(buffer, static_cast<std::uint32_t>(data), 10000);
}

std::span<char> appendDec(std::span<char> buffer, std::uint8_t data) {
  return appendDecGeneric(buffer, static_cast<std::uint32_t>(data), 100);
}

std::span<char> appendDec(std::span<char> buffer, std::int32_t data) {
  if (data < 0) {
    buffer = appendChar(buffer, '-');
    data = -data;
  }
  return appendDecGeneric(buffer, data, 1000000000);
}

std::span<char> appendDec(std::span<char> buffer, std::int16_t data) {
  if (data < 0) {
    buffer = appendChar(buffer, '-');
    data = -data;
  }
  return appendDecGeneric(buffer, static_cast<std::uint32_t>(data), 10000);
}

std::span<char> appendDec(std::span<char> buffer, std::int8_t data) {
  if (data < 0) {
    buffer = appendChar(buffer, '-');
    data = -data;
  }
  return appendDecGeneric(buffer, static_cast<std::uint32_t>(data), 100);
}

}  // namespace util