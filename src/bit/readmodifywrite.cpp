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