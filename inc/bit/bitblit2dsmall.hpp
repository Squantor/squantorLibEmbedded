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
  // compute iteration limits for width and height
  unsigned int widthCount;
  if ((destX + srcWidth) >= destWidth)
    widthCount = destWidth - destX;
  else
    widthCount = srcWidth;
  unsigned int heightCount;
  if ((destY + srcHeight) >= destHeight)
    heightCount = destHeight - destY;
  else
    heightCount = srcHeight;

  destType destMask;
  srcType srcMask;
  destType *currDestLine;
  const srcType *currSrcLine;

  unsigned int x, y;
  y = heightCount;
  while (y > 0) {
    x = widthCount;
    // do X iteration
    destMask = 1 << (destX & (destDigits - 1));
    srcMask = 1;
    currDestLine = dest;
    currSrcLine = src;
    while (x > 0) {
      bool srcPixel = (*currSrcLine & srcMask) ? true : false;
      // transfer a bit according to operation
      x--;
      srcMask = srcMask << 1;
      if (srcMask == 0) {
        srcMask = 1;
        currSrcLine++;
      }
      destMask = destMask << 1;
      if (destMask == 0) {
        destMask = 1;
        currDestLine++;
      }
    }
    y--;
    dest = dest + (destWidth / destDigits);
    src = src + (srcWidth / srcDigits);
  }
}

};  // namespace util

#endif