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
  // start of bitblit
  // compute limits as we will write out of the buffer somehow and this will be common!
  // compute indexes
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
  // start
  data = dest[destIndex] & ~mask;
  dest[destIndex] = data | (src[srcIndex] << destBit);
  destIndex++;
  // iteration
  while (destIndex != destIndexEnd) {
    // TODO: extract aligned access, RMW is redundant for it
    // but do not forget the last dangling bits in that case!
    if (mask != 0xFF)  // aligned access, this is not needed
    {
      data = dest[destIndex] & mask;
      dest[destIndex] = data | (src[srcIndex] >> (8 - destBit));
    }
    srcIndex++;
    data = dest[destIndex] & ~mask;
    dest[destIndex] = data | (src[srcIndex] << destBit);
    destIndex++;
  }
  // end
  // check for aligned access and writing over boundary
  if ((mask != 0xFF) && (destIndexEnd != destSize)) {
    data = dest[destIndex] & mask;
    dest[destIndex] = data | (src[srcIndex] >> (8 - destBit));
  }
}

};  // namespace util
