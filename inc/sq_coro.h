/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file This header contains a coroutine implementation
 *
 * This implementation is inspired by the coroutine implementation
 * in putty but uses the "Labels as values" extension from GCC/CLANG.
 *
 * https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html
 *
 */
#ifndef COROUTINE_H
#define COROUTINE_H

#include "sq_coro_common.h"

/**
 * @brief Start of coroutine
 *
 */
#define CR_BEGIN                         \
  do {                                   \
    static void* crCurrent = &&CR_START; \
    goto* crCurrent;                     \
  CR_START:;

/**
 * @brief End of void function coroutines
 *
 */
#define CR_END(retval)    \
  crCurrent = &&CR_START; \
  return retval;          \
  }                       \
  while (0)

/**
 * @brief End of void function coroutines
 *
 */
#define CR_END_V          \
  crCurrent = &&CR_START; \
  return;                 \
  }                       \
  while (0)

/**
 * @brief Yield the coroutine while returning a value
 *
 */
#define CR_YIELD(retval)    \
  do {                      \
    crCurrent = &&CR_LABEL; \
    return (retval);        \
  CR_LABEL:;                \
  } while (0)

/**
 * @brief Yield the coroutine
 *
 */
#define CR_YIELD_V          \
  do {                      \
    crCurrent = &&CR_LABEL; \
    return;                 \
  CR_LABEL:;                \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 */
#define CR_WAIT(retval, cond)   \
  do {                          \
    crCurrent = &&CR_LABEL;     \
  CR_LABEL:;                    \
    if (!(cond)) return retval; \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 */
#define CR_WAIT_V(cond)     \
  do {                      \
    crCurrent = &&CR_LABEL; \
  CR_LABEL:;                \
    if (!(cond)) return;    \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning while returning a value
 *
 */
#define CR_STOP(retval)     \
  do {                      \
    crCurrent = &&CR_START; \
    return (retval);        \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning
 *
 */
#define CR_STOP_V           \
  do {                      \
    crCurrent = &&CR_START; \
    return;                 \
  } while (0)

#endif