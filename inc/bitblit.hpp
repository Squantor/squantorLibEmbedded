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

/**
 * @brief
 *
 */
enum class bitblitOperation { OP_MOV, OP_NOT, OP_AND, OP_OR, OP_XOR };

/**
 * @brief One dimensional bit block transfer function
 *
 * @param dest      destination buffer
 * @param destSize  destination buffer in bytes
 * @param destPos   destination position in bits
 * @param src       source buffer
 * @param srcSize   sourcebuffer size in bits
 */
void bitblit1d(uint8_t *dest, size_t destSize, unsigned int destPos, uint8_t *src, unsigned int srcSize, bitblitOperation op);

/**
 * @brief Read Modify Write while masking the source and displacing it with operation op
 *
 * @param dest  pointer to destination element
 * @param src   pointer to source element
 * @param mask  mask to apply to source and destination
 * @param shift shift to apply to source, positive is shift left, negative is right
 * @param op    operation to execute
 */
void readModifyWrite(uint8_t *dest, uint8_t *src, uint8_t mask, int shift, bitblitOperation op);

};  // namespace util

#endif