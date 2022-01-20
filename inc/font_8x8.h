/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/*! \file font_8x8.h
 *  \brief definitions and inline functions for accessing 8 by 8 bitmap font
 *
 */
#ifndef FONT_8X8_H
#define FONT_8X8_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!< \brief provides index of which ascii character is at what font bitmap index */
extern const uint16_t ascii2font8x8Index[128];
/*!< \brief horizontal 8 by 8 pixel size font bitmap */
extern const uint8_t font8x8Horizontal[760];
/*!< \brief vertical 8 by 8 pixel size font bitmap */
extern const uint8_t font8x8Vertical[760];

/*! \brief maps ascii characters to bitmap
 * Returns a pointer into a bitmap array that contains 8 by 8 font characters.
 * The pointer points to the top of the bitmap.
 * \param asciiChar ASCII character to transform, maximum value 127
 * \return pointer to a 8 by 8 bitmap corresponding to the ASCII character
 */
static inline const uint8_t* ascii2Font8x8(const uint8_t* font8x8, uint8_t asciiChar) {
  return font8x8 + ascii2font8x8Index[asciiChar];
}

#ifdef __cplusplus
}
#endif

#endif