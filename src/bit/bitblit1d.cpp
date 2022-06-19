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
  uint8_t dataSrc;
  if (shift > 0)
    dataSrc = *src << shift;
  else if (shift < 0)
    dataSrc = *src >> -(shift);
  else
    dataSrc = *src;
  switch (op) {
    case bitblitOperation::OP_AND:
      *dest = *dest & (dataSrc | ~mask);
      break;
    case bitblitOperation::OP_NONE:
      *dest = (*dest & ~mask) | (dataSrc & mask);
      break;
    case bitblitOperation::OP_NOT:
      *dest = (*dest & ~mask) | (~dataSrc & mask);
      break;
    case bitblitOperation::OP_OR:
      *dest = *dest | (dataSrc & mask);
      break;
    case bitblitOperation::OP_XOR:
      *dest = *dest ^ (dataSrc & mask);
      break;
  }
}

void bitblit1d(uint8_t *dest, size_t destSize, unsigned int destPos, uint8_t *src, unsigned int srcSize, bitblitOperation op) {
  // compute count and clamp if needed
  unsigned int count;
  bool abortLastWrite;
  if ((srcSize + destPos) / 8 >= destSize) {
    count = destSize - (destPos / 8);
    abortLastWrite = true;
  } else {
    count = srcSize / 8;
    abortLastWrite = false;
  }
  // extract special case for aligned writes and adjust counts
  bool alignedWrites = (destPos & 7) == 0;
  if (count > 0 && !alignedWrites) count--;
  dest = dest + destPos / 8;
  // compute masks and bit positions
  unsigned int destBit = destPos & 7;
  unsigned int endBit = destBit + srcSize;
  unsigned int remainderBits = endBit & 7;
  uint8_t mask = 0xFF << destBit;

  if (srcSize < 8 && endBit < 9) {  // case for less then element bits write within a single element
    mask = mask & ~(0xFF << (destBit + srcSize));
    readModifyWrite(dest, src, mask, destBit, op);
    return;
  }

  if (alignedWrites) {  // case for aligned writes
    unsigned int i = count;
    while (i > 0) {
      readModifyWrite(dest, src, mask, 0, op);
      dest++;
      src++;
      i--;
    }
    if (remainderBits && !abortLastWrite) {  // handle remainder of bits
      mask = 0xFF >> (remainderBits);
      readModifyWrite(dest, src, mask, 0, op);
    }

  } else {  // case for unaligned writes single and multiple
    // first element start
    readModifyWrite(dest, src, mask, destBit, op);
    dest++;
    while (count > 0) {  // do the rest
      readModifyWrite(dest, src, ~mask, -(8 - destBit), op);
      src++;
      readModifyWrite(dest, src, mask, destBit, op);
      dest++;
      count--;
    }
    if (!abortLastWrite && remainderBits) {  // handle last
      mask = 0xFF >> (remainderBits);
      readModifyWrite(dest, src, mask, -(8 - destBit), op);
    }
  }
}
};  // namespace util
