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
  // TODO it is a shame that we leave remaining bits of a source element unused
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

  // position pointer to right location
  dest = dest + (destX / elementBitCnt);
  dest = dest + (destY * destWidth / elementBitCnt);

  // extract special case for aligned writes and adjust counts
  bool alignedWrites = (destX & 7) == 0;
  if (countX > 0 && !alignedWrites) countX--;

  // compute masks and bit positions
  const unsigned int destBit = destX & 7;
  const unsigned int endBit = destBit + srcWidth;
  const unsigned int remainderBits = endBit & 7;
  uint8_t mask;
  uint8_t *currentDestLine;
  uint8_t *currentSourceLine;

  while (countY > 0) {
    mask = 0xFF << destBit;  // reset mask computation
    currentDestLine = dest;
    currentSourceLine = src;
    unsigned int i = countX;
    if (srcWidth < elementBitCnt && endBit < 9) {  // case for less then element bits write within a single element
      mask = mask & ~(0xFF << (destBit + srcWidth));
      readModifyWrite(currentDestLine, currentSourceLine, mask, destBit, op);

    } else if (alignedWrites) {  // case for aligned writes

      while (i > 0) {
        readModifyWrite(currentDestLine, currentSourceLine, mask, 0, op);
        currentDestLine++;
        currentSourceLine++;
        i--;
      }
      if (remainderBits && !abortLastWrite) {  // handle remainder of bits
        mask = 0xFF >> (remainderBits);
        readModifyWrite(currentDestLine, currentSourceLine, mask, 0, op);
      }

    } else {  // case for unaligned writes single and multiple
      // first element start
      readModifyWrite(currentDestLine, currentSourceLine, mask, destBit, op);
      currentDestLine++;
      while (i > 0) {  // do the rest
        readModifyWrite(currentDestLine, currentSourceLine, static_cast<uint8_t>(~mask), -(elementBitCnt - destBit), op);
        currentSourceLine++;
        readModifyWrite(currentDestLine, currentSourceLine, mask, destBit, op);
        currentDestLine++;
        i--;
      }
      if (!abortLastWrite && remainderBits) {  // handle last
        mask = 0xFF >> (remainderBits);
        readModifyWrite(currentDestLine, currentSourceLine, mask, -(elementBitCnt - destBit), op);
      }
    }
    // point source pointer to next line
    dest = dest + (destWidth / elementBitCnt);
    // what if our source is less then elementBitCnt wide?
    if ((srcWidth / elementBitCnt) == 0)
      src++;  // just add one, TODO we could use the remaining bits
    else
      src = src + (srcWidth / elementBitCnt);
    countY--;
  }
}
};  // namespace util
