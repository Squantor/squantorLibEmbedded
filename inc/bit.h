/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file bit.h
 *
 * Contains various bit manipulation related functions
 *
 */
#ifndef BIT_H
#define BIT_H

#include <stdint.h>

/*! \brief "Zooms" into an 8 bit integer to a 16 bit integer
 *
 * The zooming process is best described that each bit is doubled up and then shifted into its position
 * For example 01010011 becomes 0011001100001111
 * \param byte input uint8_t data
 * \return expanded uint8_t data
 */
uint16_t bitZoom(uint8_t byte);

#endif