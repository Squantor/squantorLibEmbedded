/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef DELAY_CYCLES_H
#define DELAY_CYCLES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/** \brief Cycle accurate delay function
 *
 * \param cycles amount of cycles to delay, one delay loop is 4 cycles
 */
void delay_cycles(uint32_t cycles);

#ifdef __cplusplus
}
#endif

#endif