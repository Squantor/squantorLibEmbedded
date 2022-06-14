/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file bitblit.hpp
 *
 * Contains bit block transfer routines
 *
 */
#ifndef BITBLIT_H
#define BITBLIT_H

#include <stdint.h>
#include <stddef.h>

namespace util {
enum class bitblitOperation { OP_NONE, OP_NOT, OP_AND, OP_OR, OP_XOR };

/**
 * @brief One dimensional bit block transfer function
 *
 * @param dest      destination buffer
 * @param destSize  destination buffer in bytes
 * @param destPos   destination position in bits
 * @param src       source buffer
 * @param srcSize   sourcebuffer size in bits
 */
void bitblit1d(uint8_t *dest, size_t destSize, int destPos, uint8_t *src, int srcSize);

};  // namespace util

#endif