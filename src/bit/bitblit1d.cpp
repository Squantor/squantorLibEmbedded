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
#include <string.h>

namespace util {

void bitblit1d(uint8_t *dest, size_t destSize, unsigned int destPos, uint8_t *src, unsigned int srcSize) {
  // compute indexes and limits
  bool alignedWrites = (destPos & 7) == 0;
  unsigned int count = srcSize / 8;
  // clamp index and abort last write
  bool abortLastWrite = false;
  if ((srcSize + destPos) / 8 >= destSize) {
    count = destSize - (destPos / 8);
    abortLastWrite = true;
  };
  if (count > 0 && !alignedWrites) count--;
  dest = dest + destPos / 8;
  // compute masks
  unsigned int destBit = destPos & 7;
  unsigned int endBit = destBit + srcSize;
  uint8_t mask = 0xFF << destBit;
  uint8_t data;
  // case for less then element bits write within a single element
  if (srcSize < 8 && endBit < 9) {
    mask = mask & ~(0xFF << (destBit + srcSize));
    data = *dest & ~mask;
    *dest = data | ((*src << destBit) & mask);
    return;
  }

  if (alignedWrites) {  // faster path for aligned writes
    memcpy(dest, src, count);
    dest = dest + count;
  } else {
    // first element
    data = *dest & ~mask;
    *dest = data | (*src << destBit);
    dest++;
    // continue
    while (count > 0) {
      data = *dest & mask;
      *dest = data | (*src >> (8 - destBit));
      src++;
      data = *dest & ~mask;
      *dest = data | (*src << destBit);
      dest++;
      count--;
    }
  }
  if (!abortLastWrite) {
    // last element
    if (alignedWrites) {  // if we had aligned access, then we need next srcIndex
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
