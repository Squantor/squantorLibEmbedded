/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file parsedigit.c
 *
 */
#include <parsedigit.h>
#include <ctype.h>

/**
 * \brief Parse an ASCII character and translate it it into its decimal value.
 *
 * \param c     ASCII character to translate
 * \param value pointer to an int that will contained the value of the character
 *
 * \return true for successful translation
 */
bool parseDigit(const char c, unsigned int *value) {
  if (c >= '0' && c <= '9') {
    *value = c - '0';
    return true;
  }
  if (c >= 'a' && c <= 'f') {
    *value = c - 'a';
    return true;
  }
  if (c >= 'A' && c <= 'F') {
    *value = c - 'A';
    return true;
  }
  return false;
}