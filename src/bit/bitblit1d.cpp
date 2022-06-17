/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file bitblit.cpp
 *
 * Contains bit block transfer routines
 *
 */
#include <bitblit.hpp>

namespace util {

// TODO change from indices to pointer math
// TODO change to zero checks
void bitblit1d(uint8_t *dest, size_t destSize, unsigned int destPos, uint8_t *src, unsigned int srcSize) {
  // compute indexes and limits
  unsigned int srcIndex = 0;
  unsigned int destIndex = destPos / 8;
  unsigned int destBit = destPos & 7;
  unsigned int destOffset = destPos == 0 ? 0 : 1;
  unsigned int destIndexEnd = (destPos + srcSize + destOffset) / 8;
  if (destIndexEnd > destSize) destIndexEnd = destSize;
  // do we have less then a byte to transfer? Split off into different function and return
  if (srcSize < 8) {
    // TODO blit less then 8 bits
    return;
  }
  // compute mask
  uint8_t mask = 0xFF << destBit;
  uint8_t data;
  // starting stage
  data = dest[destIndex] & ~mask;
  dest[destIndex] = data | (src[srcIndex] << destBit);
  destIndex++;
  // iteration
  while (destIndex != destIndexEnd) {
    // TODO: extract array aligned access, RMW is redundant for it
    // but do not forget the last dangling bits in that case!
    if (mask != 0xFF)  // array aligned access, this is not needed
    {
      data = dest[destIndex] & mask;
      dest[destIndex] = data | (src[srcIndex] >> (8 - destBit));
    }
    srcIndex++;
    data = dest[destIndex] & ~mask;
    dest[destIndex] = data | (src[srcIndex] << destBit);
    destIndex++;
  }
  // end stage
  // check if the end operation would write over boundary
  if ((destIndexEnd != destSize)) {
    // check for array aligned access
    if ((mask != 0xFF)) {
      data = dest[destIndex] & mask;
      dest[destIndex] = data | (src[srcIndex] >> (8 - destBit));
      // aligned access but we have some remaining bits
    } else if (srcSize & 7) {
      unsigned int srcRemaining = srcSize & 7;
      mask = 0xFF << srcRemaining;
      srcIndex++;
      data = dest[destIndex] & mask;
      dest[destIndex] = data | (src[srcIndex] & ~mask);
    }
  }
}

};  // namespace util
