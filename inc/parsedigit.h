/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 * \file parsedigit.h
 * 
 */ 
#ifndef PARSEDIGIT_H
#define PARSEDIGIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool parseDigit(const char c, unsigned int *value);

#ifdef __cplusplus
}
#endif

#endif