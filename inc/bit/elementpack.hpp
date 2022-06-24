/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file elementpack.hpp
 *
 * element packing routines
 *
 */
#ifndef ELEMENT_PACK_H
#define ELEMENT_PACK_H

#include <limits>
#include <bit/operations.hpp>
#include <bit/readmodifywrite.hpp>

namespace util {
/**
 * @brief puts the bits of the source into destination
 *
 * When using a larger destination then source, source is stepped through to completely fill destination
 *
 * @tparam destType Destination element type
 * @tparam srcType  Source element type
 * @param dest      pointer to destination elements
 * @param src       pointer to source elements
 * @param srcShift  factor to shift the source, positive is shift left, negative is shift right, maximum shift factor is maximum
 * bits of source
 * @param op        operation to execute
 */
template <typename destType, typename srcType>
void elementPack(destType *__restrict__ dest, const srcType *__restrict__ src, int srcShift, bitblitOperation op) noexcept {
  // same size
  if constexpr (std::numeric_limits<destType>::digits == std::numeric_limits<srcType>::digits) {
    const int maxDestShift = std::numeric_limits<destType>::digits;
    destType destMask = std::numeric_limits<destType>::max();

    if (srcShift == 0) {
      readModifyWrite(dest, src, destMask, srcShift, op);
    } else {
      if (srcShift > 0) {
        destMask = destMask << srcShift;
        readModifyWrite(dest, src, destMask, srcShift, op);
        src++;
        readModifyWrite(dest, src, static_cast<destType>(~destMask), -(maxDestShift - srcShift), op);
      } else {
        destMask = destMask >> -srcShift;
        readModifyWrite(dest, src, destMask, srcShift, op);
      }
    }
  }
  // dest larger then source
  else if constexpr (std::numeric_limits<destType>::digits > std::numeric_limits<srcType>::digits) {
    const int maxSrcShift = std::numeric_limits<srcType>::digits;
    int elementCount = std::numeric_limits<destType>::digits / std::numeric_limits<srcType>::digits;
    int shiftpos = std::numeric_limits<destType>::digits - std::numeric_limits<srcType>::digits;
    destType destMask = std::numeric_limits<srcType>::max() << shiftpos;
    if (srcShift == 0) {
      while (elementCount > 0) {
        readModifyWrite(dest, src, destMask, shiftpos, op);
        destMask = destMask >> std::numeric_limits<srcType>::digits;
        shiftpos -= std::numeric_limits<srcType>::digits;
        elementCount--;
        src++;
      }
    } else {
      if (srcShift > 0) {
        readModifyWrite(dest, src, static_cast<destType>(destMask << srcShift), shiftpos + srcShift, op);
        destMask = destMask >> (maxSrcShift - srcShift);
        shiftpos = shiftpos - (maxSrcShift - srcShift);
        src++;
        while (elementCount > 0) {
          readModifyWrite(dest, src, destMask, shiftpos, op);
          destMask = destMask >> std::numeric_limits<srcType>::digits;
          shiftpos -= std::numeric_limits<srcType>::digits;
          elementCount--;
          src++;
        }
      } else {
        destMask = destMask >> -srcShift;
        shiftpos = shiftpos - -srcShift;
        while (elementCount > 0) {
          readModifyWrite(dest, src, destMask, shiftpos, op);
          destMask = destMask >> std::numeric_limits<srcType>::digits;
          shiftpos -= std::numeric_limits<srcType>::digits;
          elementCount--;
          src++;
        }
      }
    }
  }
  // cant handle this, yet
  else
    static_assert(std::numeric_limits<destType>::digits >= std::numeric_limits<srcType>::digits,
                  "elementPack can only pack if source is smaller or equally sized then destination");
}
}  // namespace util

#endif