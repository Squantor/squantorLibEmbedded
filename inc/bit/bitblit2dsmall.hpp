/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file bitblit2dsmall.hpp
 *
 * 2d bitblit routine, small version
 *
 */
#ifndef BITBLIT2DSMALL_HPP
#define BITBLIT2DSMALL_HPP

#include <limits>
#include <bit/operations.hpp>
#include <bit/readmodifywrite.hpp>

namespace util {

/**
 * @brief
 *
 * @param dest
 * @param destWidth
 * @param destHeight
 * @param destX
 * @param destY
 * @param src
 * @param srcWidth
 * @param srcHeight
 * @param op
 */
void bitblit2dsmall(__restrict uint8_t *dest, unsigned int destWidth, unsigned int destHeight, unsigned int destX,
                    unsigned int destY, __restrict const uint8_t *src, unsigned int srcWidth, unsigned int srcHeight,
                    bitblitOperation op) noexcept;
{}

};  // namespace util

#endif