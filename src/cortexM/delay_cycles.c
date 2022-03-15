/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/* \brief cycle accurate delay loop
 * Cycle accurate delay loop for Cortex M processors, taken from this forum post by
 * Alex Taradov on the eevblog forum on arm NOP discussion:
 * https://www.eevblog.com/forum/microcontrollers/arm-nop/msg3935962/#msg3935962
 */
#include <delay_cycles.h>

__attribute__((noinline, section(".ramfunc"))) void delay_cycles(uint32_t cycles) {
  cycles /= 4;

  asm volatile(
    "1: sub %[cycles], %[cycles], #1 \n"
    "   nop \n"
    "   bne 1b \n"
    : [cycles] "+l"(cycles));
}