/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file bitzoom.c
 *
 * Contains the bitZoom function
 *
 */

#include <bit.h>

uint16_t bitZoom(uint8_t byte) {
  uint16_t input = byte;
  uint16_t mask = 0x0001;
  uint16_t output = input & mask;
  input = input << 1;
  mask = mask << 1;
  output = output | (input & mask);
  mask = mask << 1;
  output = output | (input & mask);
  input = input << 1;
  mask = mask << 1;
  output = output | (input & mask);
  mask = mask << 1;
  output = output | (input & mask);
  input = input << 1;
  mask = mask << 1;
  output = output | (input & mask);
  mask = mask << 1;
  output = output | (input & mask);
  input = input << 1;
  mask = mask << 1;
  output = output | (input & mask);
  mask = mask << 1;
  output = output | (input & mask);
  input = input << 1;
  mask = mask << 1;
  output = output | (input & mask);
  mask = mask << 1;
  output = output | (input & mask);
  input = input << 1;
  mask = mask << 1;
  output = output | (input & mask);
  mask = mask << 1;
  output = output | (input & mask);
  input = input << 1;
  mask = mask << 1;
  output = output | (input & mask);
  mask = mask << 1;
  output = output | (input & mask);
  input = input << 1;
  mask = mask << 1;
  output = output | (input & mask);
  return output;
}