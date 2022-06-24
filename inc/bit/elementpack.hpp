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
 * @param shift     factor to shift the source, positive is shift left, negative is shift right
 * @param op        operation to execute
 */
template <typename destType, typename srcType>
void elementPack(destType *__restrict__ dest, srcType *__restrict__ src, int shift, bitblitOperation op) noexcept {
  // same size
  if constexpr (std::numeric_limits<destType>::digits == std::numeric_limits<srcType>::digits) {
    destType mask = std::numeric_limits<destType>::max();
    int maxShift = std::numeric_limits<destType>::digits;
    if (shift == 0) {
      readModifyWrite(dest, src, mask, shift, op);
    } else {
      if (shift > 0) {
        mask = mask << shift;
        readModifyWrite(dest, src, mask, shift, op);
        src++;
        readModifyWrite(dest, src, static_cast<destType>(~mask), -(maxShift - shift), op);
      } else {
        mask = mask >> -shift;
        readModifyWrite(dest, src, mask, shift, op);
      }
    }
  }
  // dest larger then source
  else if constexpr (std::numeric_limits<destType>::digits > std::numeric_limits<srcType>::digits) {
    int elementCount = std::numeric_limits<destType>::digits / std::numeric_limits<srcType>::digits;
    int shiftpos = std::numeric_limits<destType>::digits - std::numeric_limits<srcType>::digits;
    destType mask = std::numeric_limits<srcType>::max() << shiftpos;

    if (shift == 0) {
      while (elementCount > 0) {
        readModifyWrite(dest, src, mask, shiftpos, op);
        mask = mask >> std::numeric_limits<srcType>::digits;
        shiftpos -= std::numeric_limits<srcType>::digits;
        elementCount--;
        src++;
      }
    } else {
      if (shift > 0) {
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