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

// TODO see if you can refactor this into bitblit1d
static void bitblit1dSingle(uint8_t *dest, size_t destSize, unsigned int destPos, uint8_t src, unsigned int srcSize) {
  // compute indexes and limits
  unsigned int destIndex = destPos / 8;
  unsigned int destBit = destPos & 7;
  unsigned int endBit = destBit + srcSize;
  // compute masks
  uint8_t mask = 0xFF << destBit;
  uint8_t data;
  // non crossing case
  if (endBit < 9) {
    mask = mask & ~(0xFF << (destBit + srcSize));
    data = dest[destIndex] & ~mask;
    dest[destIndex] = data | ((src << destBit) & mask);
  } else {
    data = dest[destIndex] & ~mask;
    dest[destIndex] = data | (src << destBit);
    destIndex++;
    // write remaining bits
    unsigned int srcRemaining = endBit & 7;
    mask = 0xFF << srcRemaining;
    data = dest[destIndex] & mask;
    dest[destIndex] = data | ((src >> (8 - destBit)) & ~mask);
  }
}

// TODO change the idiom of 0xFF >> (8 - n) to ~(0xFF << n) for mask generation
// TODO change from indices to pointer math
// TODO change to zero checks
// TODO we could make aligned access a flag instead of a special mask?
// TODO: extract array aligned access, RMW is redundant for it
// but do not forget the last dangling bits in that case!
void bitblit1d(uint8_t *dest, size_t destSize, unsigned int destPos, uint8_t *src, unsigned int srcSize) {
  // compute indexes and limits
  unsigned int srcIndex = 0;
  unsigned int destIndex = destPos / 8;
  unsigned int destBit = destPos & 7;
  unsigned int destOffset = destPos == 0 ? 0 : 1;
  unsigned int destIndexEnd = (destPos + srcSize + destOffset) / 8;
  if (destIndexEnd > destSize) destIndexEnd = destSize;
  // compute masks
  uint8_t mask = 0xFF << destBit;
  uint8_t data;
  // case for less then 8 bits we need to modify the mask
  if (srcSize < 8) {
    bitblit1dSingle(dest, destSize, destPos, src[0], srcSize);
    return;
  }
  // starting stage
  data = dest[destIndex] & ~mask;
  dest[destIndex] = data | (src[srcIndex] << destBit);
  destIndex++;
  // iteration
  while (destIndex != destIndexEnd) {
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
