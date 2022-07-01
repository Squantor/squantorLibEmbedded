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
#include <bit/operations.hpp>
#include <bit/readmodifywrite.hpp>
#include <bit/bitblit1d.hpp>
#include <bit/bitblit2dfast.hpp>
#include <bit/bitblit2dsmall.hpp>

namespace util {

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
               __restrict const uint8_t *src, unsigned int srcWidth, unsigned int srcHeight, bitblitOperation op) noexcept;

};  // namespace util

#endif