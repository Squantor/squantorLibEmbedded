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
void bitblit2dsmall(destType *__restrict__ dest, unsigned int destWidth, unsigned int destHeight, unsigned int destX,
                    unsigned int destY, const srcType *__restrict__ src, unsigned int srcWidth, unsigned int srcHeight,
                    bitblitOperation op) noexcept {
  constexpr int destDigits = std::numeric_limits<destType>::digits;
  constexpr int srcDigits = std::numeric_limits<srcType>::digits;
  
}

};  // namespace util

#endif