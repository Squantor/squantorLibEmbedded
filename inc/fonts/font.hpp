/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** @file font.hpp
 *  @brief font class definition
 *
 */
#ifndef FONT_HPP
#define FONT_HPP

#include <cstdint>
#include <span>

namespace sqEmbedded {

struct font {
  font(std::uint16_t x, std::uint16_t y, std::span<const uint8_t> bitmap, std::span<const uint16_t> table)
    : xSize{x}, ySize{y}, fontBitmap{bitmap}, translationTable{table} {}
  constexpr inline std::span<const uint8_t> ascii2Font(std::uint8_t asciiChar) {
    return fontBitmap.subspan(translationTable[asciiChar], ySize);
  }
  const uint16_t xSize;
  const uint16_t ySize;
  const std::span<const uint8_t> fontBitmap;
  const std::span<const uint16_t> translationTable;
};
}  // namespace sqEmbedded

#endif