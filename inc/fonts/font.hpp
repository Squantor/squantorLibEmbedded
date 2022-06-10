/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/*! \file font.h
 *  \brief definitions and code commonly used for monospaced fonts
 *
 */
#ifndef FONT_H
#define FONT_H

#include <stdint.h>

struct font {
  const uint16_t xSize;
  const uint16_t ySize;
  const uint8_t *fontBitmap;
  const uint16_t *ascii2index;
};

#endif