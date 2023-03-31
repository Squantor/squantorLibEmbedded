/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file parity.c
 *
 * Various parity calcuation functions
 *
 */
#include <parity.h>

bool sq_parityEvenU8(uint8_t value) {
  value ^= value >> 4;
  value &= 0xf;
  return ((0x9669u >> value) & 1) == 0;
}

bool sq_parityEvenU16(uint16_t value) {
  value ^= value >> 8;
  value ^= value >> 4;
  value &= 0xf;
  return ((0x9669u >> value) & 1) == 0;
}

bool sq_parityEvenU32(uint32_t value) {
  value ^= value >> 16;
  value ^= value >> 8;
  value ^= value >> 4;
  value &= 0xf;
  return ((0x9669u >> value) & 1) == 0;
}

bool sq_parityEvenU64(uint64_t value) {
  value ^= value >> 32;
  value ^= value >> 16;
  value ^= value >> 8;
  value ^= value >> 4;
  value &= 0xf;
  return ((0x9669u >> value) & 1) == 0;
}

bool sq_parityOddU8(uint8_t value) {
  return !sq_parityEvenU8(value);
}

bool sq_parityOddU16(uint16_t value) {
  return !sq_parityEvenU16(value);
}

bool sq_parityOddU32(uint32_t value) {
  return !sq_parityEvenU32(value);
}

bool sq_parityOddU64(uint64_t value) {
  return !sq_parityEvenU64(value);
}