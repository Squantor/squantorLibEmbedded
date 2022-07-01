/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file bitblit2dfast.hpp
 *
 * 2d bitblit routine, fast version
 *
 */
#ifndef BITBLIT2DFAST_HPP
#define BITBLIT2DFAST_HPP

#include <limits>
#include <bit/operations.hpp>
#include <bit/readmodifywrite.hpp>

namespace util {

/**
 * @brief
 *
 * @tparam destType
 * @tparam srcType
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
template <typename destType, typename srcType>
void bitblit2dfast(destType *__restrict__ dest, unsigned int destWidth, unsigned int destHeight, unsigned int destX,
                   unsigned int destY, const srcType *__restrict__ src, unsigned int srcWidth, unsigned int srcHeight,
                   bitblitOperation op) noexcept {}

};  // namespace util

#endif