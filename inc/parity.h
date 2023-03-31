/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file parity.h
 *
 * Contains parity calculation function prototypes
 *
 */
#ifndef PARITY_H
#define PARITY_H

#include <stdint.h>
#include <stdbool.h>

#define sq_parityEven(X) \
  _Generic((X), uint8_t : sq_parityEvenU8, uint16_t : sq_parityEvenU16, uint32_t : sq_parityEvenU32, uint64_t : sq_parityEvenU64)(X)
#define sq_parityOdd(X) \
  _Generic((X), uint8_t : sq_parityOddU8, uint16_t : sq_parityOddU16, uint32_t : sq_parityOddU32, uint64_t : sq_parityOddU64)(X)

/**
 * @brief Compute even parity
 *
 * @param value input for parity calculation
 * @return true parity odd
 * @return false parity even
 */
bool sq_parityEvenU8(uint8_t value);

/**
 * @brief Compute even parity
 *
 * @param value input for parity calculation
 * @return true parity odd
 * @return false parity even
 */
bool sq_parityEvenU16(uint16_t value);

/**
 * @brief Compute even parity
 *
 * @param value input for parity calculation
 * @return true parity odd
 * @return false parity even
 */
bool sq_parityEvenU32(uint32_t value);

/**
 * @brief Compute even parity
 *
 * @param value input for parity calculation
 * @return true parity odd
 * @return false parity even
 */
bool sq_parityEvenU64(uint64_t value);

/**
 * @brief Compute odd parity
 *
 * @param value input for parity calculation
 * @return true parity even
 * @return false parity odd
 */
bool sq_parityOddU8(uint8_t value);

/**
 * @brief Compute odd parity
 *
 * @param value input for parity calculation
 * @return true parity even
 * @return false parity odd
 */
bool sq_parityOddU16(uint16_t value);

/**
 * @brief Compute odd parity
 *
 * @param value input for parity calculation
 * @return true parity even
 * @return false parity odd
 */
bool sq_parityOddU32(uint32_t value);

/**
 * @brief Compute odd parity
 *
 * @param value input for parity calculation
 * @return true parity even
 * @return false parity odd
 */
bool sq_parityOddU64(uint64_t value);

#endif