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
 * @brief operations
 *
 */
enum class bitblitOperation { OP_MOV, OP_NOT, OP_AND, OP_OR, OP_XOR };

/**
 * @brief One dimensional bit block transfer function
 *
 * @param dest      destination buffer
 * @param destWidth destination buffer in bytes TODO: Change this to bits, makes more sense
 * @param destX     destination position in bits
 * @param src       source buffer
 * @param srcWidth  sourcebuffer size in bits
 */
void bitblit1d(__restrict uint8_t *dest, size_t destWidth, unsigned int destX, __restrict uint8_t *src, unsigned int srcWidth,
               bitblitOperation op) noexcept;

/**
 * @brief Two dimensional bit block transfer
 *
 * @param dest        destination buffer
 * @param destWidth   destination buffer width
 * @param destHeight  destination buffer height
 * @param destX       destination X position to write source
 * @param destY       destination Y position to write source
 * @param src         source buffer
 * @param srcWidth    source width
 * @param srcHeight   source height
 * @param op          operation to execute
 */
void bitblit2d(__restrict uint8_t *dest, unsigned int destWidth, unsigned int destHeight, unsigned int destX, unsigned int destY,
               __restrict uint8_t *src, unsigned int srcWidth, unsigned int srcHeight, bitblitOperation op) noexcept;

/**
 * @brief Read Modify Write while masking the source and displacing it with operation op
 *
 * @param dest  pointer to destination element
 * @param src   pointer to source element
 * @param mask  mask to apply to source and destination
 * @param shift shift to apply to source, positive is shift left, negative is right
 * @param op    operation to execute
 */
void readModifyWrite(__restrict uint8_t *dest, __restrict uint8_t *src, uint8_t mask, int shift, bitblitOperation op) noexcept;

/**
 * @brief Read Modify Write while masking the source and displacing it with operation op
 *
 * @param dest  pointer to destination element
 * @param src   pointer to source element
 * @param mask  mask to apply to source and destination
 * @param shift shift to apply to source, positive is shift left, negative is right
 * @param op    operation to execute
 */
void readModifyWrite(__restrict uint16_t *dest, __restrict uint8_t *src, uint16_t mask, int shift, bitblitOperation op) noexcept;

/**
 * @brief Read Modify Write while masking the source and displacing it with operation op
 *
 * @param dest  pointer to destination element
 * @param src   pointer to source element
 * @param mask  mask to apply to source and destination
 * @param shift shift to apply to source, positive is shift left, negative is right
 * @param op    operation to execute
 */
void readModifyWrite(__restrict uint32_t *dest, __restrict uint8_t *src, uint32_t mask, int shift, bitblitOperation op) noexcept;

};  // namespace util

#endif