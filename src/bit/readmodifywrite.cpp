/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file readmodifywrite.cpp
 *
 * Contains read modify write routines
 *
 */
#include <bitblit.hpp>

namespace util {

#if 0
/**
 * @brief Read Modify Write while masking the source and displacing it with operation op
 *
 * @param dest  pointer to destination element
 * @param src   pointer to source element
 * @param mask  mask to apply to source and destination
 * @param shift shift to apply to source, positive is shift left, negative is right
 * @param op    operation to execute
 */
void readModifyWrite(__restrict uint8_t *dest, __restrict uint8_t *src, uint8_t mask, int shift, bitblitOperation op) noexcept;

/**
 * @brief Read Modify Write while masking the source and displacing it with operation op
 *
 * @param dest  pointer to destination element
 * @param src   pointer to source element
 * @param mask  mask to apply to source and destination
 * @param shift shift to apply to source, positive is shift left, negative is right
 * @param op    operation to execute
 */
void readModifyWrite(__restrict uint16_t *dest, __restrict uint8_t *src, uint16_t mask, int shift, bitblitOperation op) noexcept;

/**
 * @brief Read Modify Write while masking the source and displacing it with operation op
 *
 * @param dest  pointer to destination element
 * @param src   pointer to source element
 * @param mask  mask to apply to source and destination
 * @param shift shift to apply to source, positive is shift left, negative is right
 * @param op    operation to execute
 */
void readModifyWrite(__restrict uint32_t *dest, __restrict uint8_t *src, uint32_t mask, int shift, bitblitOperation op) noexcept;

void readModifyWrite(__restrict uint8_t *dest, __restrict uint8_t *src, uint8_t mask, int shift, bitblitOperation op) noexcept {
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

void readModifyWrite(__restrict uint16_t *dest, __restrict uint8_t *src, uint16_t mask, int shift, bitblitOperation op) noexcept {
  uint16_t dataSrc;
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

void readModifyWrite(__restrict uint32_t *dest, __restrict uint8_t *src, uint32_t mask, int shift, bitblitOperation op) noexcept {
  uint32_t dataSrc;
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
#endif

}  // namespace util