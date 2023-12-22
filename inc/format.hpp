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
/**
 * @brief Appends a string to a span
 *
 * Appends a string to the input span and returns a span with remaining space
 * The string is added at the beginning of this span
 *
 * @param buffer span to append the string to
 * @param string string to append to the span
 * @return span with available space
 */
std::span<char> appendString(std::span<char> buffer, std::span<char> string);

/**
 * @brief Appends a character to a span
 *
 * @param buffer span to append the character to
 * @param c character to append to the span
 * @return span with available space
 */
std::span<char> appendChar(std::span<char> buffer, char c);

/**
 * @brief Appends a digit to a span
 *
 * Appends a digit to the input span and returns a span with remaining space
 * The first 4 bits of data are evaluated and translated from 0 to F (hex)
 *
 * @param buffer span to append the digit to
 * @param data digit to add to the span, only the first 4 bits are evaluated
 * @return span with available space
 */
std::span<char> appendDigit(std::span<char> buffer, const std::uint32_t data);

/**
 * @brief Appends a hexidecimal number to a span
 *
 * Appends a hex number to the input span and returns a span with remaining space
 * The 32 bit number results into 8 hex digits, leading zeroes are printed
 *
 * @param buffer span to append the hex number to
 * @param data number to translate to hex and append
 * @return span with available space
 */
std::span<char> appendHex(std::span<char> buffer, std::uint32_t data);

/**
 * @brief Appends a hexidecimal number to a span
 *
 * Appends a hex number to the input span and returns a span with remaining space
 * The 16 bit number results into 4 hex digits, leading zeroes are printed
 *
 * @param buffer span to append the hex number to
 * @param data number to translate to hex and append
 * @return span with available space
 */
std::span<char> appendHex(std::span<char> buffer, std::uint16_t data);

/**
 * @brief Appends a hexidecimal number to a span
 *
 * Appends a hex number to the input span and returns a span with remaining space
 * The 8 bit number results into 2 hex digits, leading zeroes are printed
 *
 * @param buffer span to append the hex number to
 * @param data number to translate to hex and append
 * @return span with available space
 */
std::span<char> appendHex(std::span<char> buffer, std::uint8_t data);

/**
 * @brief Appends a decimal number to a span
 *
 * Appends a decimal number to the input span and returns a span with remaining space
 * Leading zeroes are not printed
 *
 * @param buffer span to append the decimal number to
 * @param data number to translate to decimal and append
 * @return span with available space
 */
std::span<char> appendDec(std::span<char> buffer, std::uint32_t data);

/**
 * @brief Appends a decimal number to a span
 *
 * Appends a decimal number to the input span and returns a span with remaining space
 * Leading zeroes are not printed
 *
 * @param buffer span to append the decimal number to
 * @param data number to translate to decimal and append
 * @return span with available space
 */
std::span<char> appendDec(std::span<char> buffer, std::uint16_t data);

/**
 * @brief Appends a decimal number to a span
 *
 * Appends a decimal number to the input span and returns a span with remaining space
 * Leading zeroes are not printed
 *
 * @param buffer span to append the decimal number to
 * @param data number to translate to decimal and append
 * @return span with available space
 */
std::span<char> appendDec(std::span<char> buffer, std::uint8_t data);

/**
 * @brief Appends a decimal number to a span
 *
 * Appends a decimal number to the input span and returns a span with remaining space
 * Leading zeroes are not printed, sign is printed in front
 *
 * @param buffer span to append the decimal number to
 * @param data number to translate to decimal and append
 * @return span with available space
 */
std::span<char> appendDec(std::span<char> buffer, std::int32_t data);

/**
 * @brief Appends a decimal number to a span
 *
 * Appends a decimal number to the input span and returns a span with remaining space
 * Leading zeroes are not printed, sign is printed in front
 *
 * @param buffer span to append the decimal number to
 * @param data number to translate to decimal and append
 * @return span with available space
 */
std::span<char> appendDec(std::span<char> buffer, std::int16_t data);

/**
 * @brief Appends a decimal number to a span
 *
 * Appends a decimal number to the input span and returns a span with remaining space
 * Leading zeroes are not printed, sign is printed in front
 *
 * @param buffer span to append the decimal number to
 * @param data number to translate to decimal and append
 * @return span with available space
 */
std::span<char> appendDec(std::span<char> buffer, std::int8_t data);

}  // namespace util

#endif