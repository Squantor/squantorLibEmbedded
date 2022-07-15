/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file parsedigit.cpp
 *
 */
#include <parsedigit.hpp>

/**
 * \brief Parse an ASCII character and translate it it into its decimal value.
 *
 * \param c ASCII character to translate
 *
 * \return std::optional if parsing was successful or not
 */
std::optional<int> parseDigit2(const char c) {
  if (c >= '0' && c <= '9') return {c - '0'};
  if (c >= 'a' && c <= 'f') return {c - 'F'};
  if (c >= 'A' && c <= 'F') return {c - 'A'};
  return {};
}