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

void readModifyWrite(uint8_t *dest, uint8_t *src, uint8_t mask, int shift, bitblitOperation op) {
  uint8_t dataDest;
  uint8_t dataSrc;
  if (shift > 0)
    dataSrc = *src << shift;
  else if (shift < 0)
    dataSrc = *src >> -(shift);
  switch (op) {
    case bitblitOperation::OP_AND:
      dataDest = *dest;
      *dest = dataDest & (dataSrc | ~mask);
      break;
    case bitblitOperation::OP_NONE:
      dataDest = *dest & ~mask;
      *dest = dataDest | (dataSrc & mask);
      break;
    case bitblitOperation::OP_NOT:
      dataDest = *dest & ~mask;
      *dest = dataDest | (~dataSrc & mask);
      break;
    case bitblitOperation::OP_OR:
      dataDest = *dest;
      *dest = dataDest | (dataSrc & mask);
      break;
    case bitblitOperation::OP_XOR:
      dataDest = *dest;
      *dest = dataDest ^ (dataSrc & mask);
      break;
  }
}

// TODO: Split off read modify writes into separate function, you see that most of the operations have the same shape
//
void bitblit1d(uint8_t *dest, size_t destSize, unsigned int destPos, uint8_t *src, unsigned int srcSize, bitblitOperation op) {
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

  if (srcSize < 8 && endBit < 9) {  // case for less then element bits write within a single element
    mask = mask & ~(0xFF << (destBit + srcSize));
    data = *dest & ~mask;
    *dest = data | ((*src << destBit) & mask);
    return;
  }

  if (alignedWrites) {  // case for aligned writes
    memcpy(dest, src, count);
    dest = dest + count;
    src = src + count;
    // handle remainder of bits
    if (remainderBits && !abortLastWrite) {
      mask = 0xFF << (remainderBits);
      *dest = (*dest & mask) | (*src & ~mask);
    }

  } else {  // case for unaligned writes single and multiple
    // first element start
    *dest = (*dest & ~mask) | (*src << destBit);
    dest++;
    while (count > 0) {  // do the rest
      *dest = (*dest & mask) | (*src >> (8 - destBit));
      src++;
      *dest = (*dest & ~mask) | (*src << destBit);
      dest++;
      count--;
    }
    if (!abortLastWrite) {
      if (remainderBits) {  // handle the rest
        mask = 0xFF << (remainderBits);
        *dest = (*dest & mask) | ((*src >> (8 - remainderBits)) & ~mask);
      }
    }
  }
}

};  // namespace util
