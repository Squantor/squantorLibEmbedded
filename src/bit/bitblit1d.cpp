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

// WIP change endbit bounds
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
  unsigned int endBit = destBit + srcSize;
  if (destIndexEnd > destSize) destIndexEnd = destSize;  // limit end index to destination size
  // compute masks
  uint8_t mask = 0xFF << destBit;
  uint8_t data;
  // case for less then element bits write within a single element
  if (srcSize < 8 && endBit < 9) {
    mask = mask & ~(0xFF << (destBit + srcSize));
    data = dest[destIndex] & ~mask;
    dest[destIndex] = data | ((src[srcIndex] << destBit) & mask);
    return;
  }
  // first element
  data = dest[destIndex] & ~mask;
  dest[destIndex] = data | (src[srcIndex] << destBit);
  destIndex++;
  // continue
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
  // last element

  if ((destIndexEnd != destSize)) {  // check if the end operation would write over boundary
    if (mask == 0xFF) srcIndex++;    // if we had aligned access, then we need next srcIndex
    // handle remaining bits
    unsigned int remainderBits = endBit & 7;
    if (remainderBits) {
      mask = 0xFF << (remainderBits);
      data = dest[destIndex] & mask;
      dest[destIndex] = data | ((src[srcIndex] >> remainderBits) & ~mask);
    }
  }
}

};  // namespace util
