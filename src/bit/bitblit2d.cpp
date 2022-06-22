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

void bitblit2d(__restrict uint8_t *dest, unsigned int destWidth, unsigned int destHeight, unsigned int destX, unsigned int destY,
               __restrict uint8_t *src, unsigned int srcWidth, unsigned int srcHeight, bitblitOperation op) noexcept {
  // TODO check if destX and destY are out of bounds
  // compute counts and clamp if needed
  const unsigned int elementBitCnt = 8;  // size of elements in src/dest
  unsigned int countX, countY;
  bool abortLastWrite;
  if ((srcWidth + destX) >= destWidth) {
    countX = (destWidth - destX) / elementBitCnt;
    abortLastWrite = true;
  } else {
    countX = srcWidth / elementBitCnt;
    abortLastWrite = false;
  }
  if ((srcHeight + destY) >= destHeight) {
    countY = (destHeight - destY);
  } else {
    countY = srcHeight;
  }

  // extract special case for aligned writes and adjust counts
  bool alignedWrites = (destX & 7) == 0;
  if (countX > 0 && !alignedWrites) countX--;
  dest = dest + (destX / elementBitCnt);
  // compute masks and bit positions
  unsigned int destBit = destX & 7;
  unsigned int endBit = destBit + srcWidth;
  unsigned int remainderBits = endBit & 7;
  uint8_t mask;
  uint8_t *currentLine;

  while (countY > 0) {
    mask = 0xFF << destBit;  // reset mask computation
    currentLine = dest;
    // TODO reset countX every iteration!
    if (srcWidth < elementBitCnt && endBit < 9) {  // case for less then element bits write within a single element
      mask = mask & ~(0xFF << (destBit + srcWidth));
      readModifyWrite(currentLine, src, mask, destBit, op);

    } else if (alignedWrites) {  // case for aligned writes
      unsigned int i = countX;
      while (i > 0) {
        readModifyWrite(currentLine, src, mask, 0, op);
        currentLine++;
        src++;
        i--;
      }
      if (remainderBits && !abortLastWrite) {  // handle remainder of bits
        mask = 0xFF >> (remainderBits);
        readModifyWrite(currentLine, src, mask, 0, op);
      }

    } else {  // case for unaligned writes single and multiple
      // first element start
      readModifyWrite(currentLine, src, mask, destBit, op);
      currentLine++;
      while (countX > 0) {  // do the rest
        readModifyWrite(currentLine, src, ~mask, -(elementBitCnt - destBit), op);
        src++;
        readModifyWrite(currentLine, src, mask, destBit, op);
        currentLine++;
        countX--;
      }
      if (!abortLastWrite && remainderBits) {  // handle last
        mask = 0xFF >> (remainderBits);
        readModifyWrite(currentLine, src, mask, -(elementBitCnt - destBit), op);
      }
    }
    // point source pointer to next line
    dest = dest + (destWidth / elementBitCnt);
    countY--;
  }
}
};  // namespace util
