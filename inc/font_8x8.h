/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef FONT_8X8_H
#define FONT_8X8_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!< \brief provides index of which ascii character is at what font bitmap index */
extern const uint16_t ascii2font8x8[128];
/*!< \brief 8 by 8 pixel size font bitmap */
extern const uint8_t font8x8[760];

#ifdef __cplusplus
}
#endif

#endif