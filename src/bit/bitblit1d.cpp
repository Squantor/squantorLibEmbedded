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

// TODO change to zero checks and remove indexes
// TODO we could make aligned access a flag instead of a special mask?
// TODO: extract array aligned access, RMW is redundant for it
// but do not forget the last dangling bits in that case!
void bitblit1d(uint8_t *dest, size_t destSize, unsigned int destPos, uint8_t *src, unsigned int srcSize) {
  // compute indexes and limits
  unsigned int srcIndex = 0;
  unsigned int destIndex = destPos / 8;
  dest = dest + destPos / 8;
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
    data = *dest & ~mask;
    *dest = data | ((*src << destBit) & mask);
    return;
  }
  // first element
  data = *dest & ~mask;
  *dest = data | (*src << destBit);
  destIndex++;
  dest++;
  // continue
  while (destIndex != destIndexEnd) {
    if (mask != 0xFF)  // array aligned access, this is not needed
    {
      data = *dest & mask;
      *dest = data | (*src >> (8 - destBit));
    }
    srcIndex++;
    src++;
    data = *dest & ~mask;
    *dest = data | (*src << destBit);
    destIndex++;
    dest++;
  }
  // last element

  if ((destIndexEnd != destSize)) {  // check if the end operation would write over boundary
    if (mask == 0xFF) {              // if we had aligned access, then we need next srcIndex
      srcIndex++;
      src++;
    }
    // handle remaining bits
    unsigned int remainderBits = endBit & 7;
    if (remainderBits) {
      mask = 0xFF << (remainderBits);
      data = *dest & mask;
      *dest = data | ((*src >> remainderBits) & ~mask);
    }
  }
}

};  // namespace util
