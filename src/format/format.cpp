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
    result = appendDigit(result, static_cast<uint32_t>(value));
    data = data << 4;
  }
  return result;
}

std::span<char> appendHex(std::span<char> buffer, std::uint16_t data) {
  std::span result = buffer;
  for (int i = 0; i < 4; i++) {
    std::uint16_t value = 0xF000 & data;
    value = value >> 12;
    result = appendDigit(result, static_cast<uint32_t>(value));
    data = data << 4;
  }
  return result;
}

std::span<char> appendHex(std::span<char> buffer, std::uint8_t data) {
  std::span result = buffer;
  result = appendDigit(result, static_cast<uint32_t>(data >> 4));
  result = appendDigit(result, static_cast<uint32_t>(data));
  return result;
}

std::span<char> appendDec(std::span<char> buffer, std::uint32_t data) {
  bool supressDigits = true;
  std::span result = buffer;
  std::uint32_t num = 1000000000;
  std::uint8_t idx;
  while (num > 0) {
    idx = data / num;
    if (idx != 0)
      supressDigits = false;
    if (!supressDigits)
      result = appendDigit(result, idx);
    data -= idx * num;
    num = num / 10;
  }
  return result;
}

std::span<char> appendDec(std::span<char> buffer, std::uint16_t data) {
  bool supressDigits = true;
  std::span result = buffer;
  std::uint32_t num = 10000;
  std::uint8_t idx;
  while (num > 0) {
    idx = data / num;
    if (idx != 0)
      supressDigits = false;
    if (!supressDigits)
      result = appendDigit(result, idx);
    data -= idx * num;
    num = num / 10;
  }
  return result;
}

std::span<char> appendDec(std::span<char> buffer, std::uint8_t data) {
  bool supressDigits = true;
  std::span result = buffer;
  std::uint32_t num = 100;
  std::uint8_t idx;
  while (num > 0) {
    idx = data / num;
    if (idx != 0)
      supressDigits = false;
    if (!supressDigits)
      result = appendDigit(result, idx);
    data -= idx * num;
    num = num / 10;
  }
  return result;
}

}  // namespace util