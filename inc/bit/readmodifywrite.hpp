/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file readmodifywrite.hpp
 *
 * Contains read modify write routines
 *
 */
#ifndef READMODIFYWRITE_HPP
#define READMODIFYWRITE_HPP

#include <limits>
#include <cstdint>
#include <bit/operations.hpp>

namespace util {
/**
 * @brief Read, modifies and writes from source to destination with operation, the source is shifted and masked
 *
 * @tparam destType   destination element type
 * @tparam sourceType source element type
 * @param dest        pointer to destination
 * @param src         pointer to source
 * @param mask        mask to apply to source
 * @param shift       shift factor to apply to source
 * @param op          operation to perform
 */
template <typename destType, typename sourceType>
void readModifyWrite(destType *__restrict__ dest, sourceType *__restrict__ src, destType mask, int shift,
                     bitblitOperation op) noexcept {
  static_assert(!std::numeric_limits<destType>::is_signed && !std::numeric_limits<sourceType>::is_signed,
                "readModifyWrite only accepts unsigned types!");
  static_assert(std::numeric_limits<destType>::digits >= std::numeric_limits<sourceType>::digits,
                "source should have equal or less bits then destination!");
  destType dataSrc;
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
    case bitblitOperation::OP_MOV:
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
}  // namespace util

#endif
