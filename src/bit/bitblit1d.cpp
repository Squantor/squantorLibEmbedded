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

// TODO: Split off read modify writes into separate function, you see that most of the operations have the same shape
//
void bitblit1d(uint8_t *dest, size_t destSize, unsigned int destPos, uint8_t *src, unsigned int srcSize) {
  // compute indexes and limits
  bool alignedWrites = (destPos & 7) == 0;
  unsigned int count = srcSize / 8;
  // clamp index and abort last write
  bool abortLastWrite = false;
  if ((srcSize + destPos) / 8 >= destSize) {
    count = destSize - (destPos / 8);
    abortLastWrite = true;
  }
  if (count > 0 && !alignedWrites) count--;
  dest = dest + destPos / 8;
  // compute masks and bit positions
  unsigned int destBit = destPos & 7;
  unsigned int endBit = destBit + srcSize;
  unsigned int remainderBits = endBit & 7;
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
    src = src + count;
    if (remainderBits && !abortLastWrite) {
      mask = 0xFF << (remainderBits);
      *dest = (*dest & mask) | (*src & ~mask);
    }
  } else {  // unaligned writes
    // first element
    *dest = (*dest & ~mask) | (*src << destBit);
    dest++;
    // continue
    while (count > 0) {
      *dest = (*dest & mask) | (*src >> (8 - destBit));
      src++;
      *dest = (*dest & ~mask) | (*src << destBit);
      dest++;
      count--;
    }
    if (!abortLastWrite) {
      // handle remaining bits
      if (remainderBits) {
        mask = 0xFF << (remainderBits);
        *dest = (*dest & mask) | ((*src >> (8 - remainderBits)) & ~mask);
      }
    }
  }
}

};  // namespace util
