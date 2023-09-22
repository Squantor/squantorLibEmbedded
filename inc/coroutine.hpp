/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file This header contains a coroutine implementation
 *
 * This implementation is heavely inspired by the coroutine implementation
 * in spigot.
 *
 */
#ifndef COROUTINE_HPP
#define COROUTINE_HPP

#define CR_START_LINE (0) /**< first label in coroutine always has label 0 */
using crState = int;      /**< Type to store the coroutine state (line number) */

/**
 * @brief Start of coroutine
 *
 * Be aware that the class variable crState should be defined!
 *
 */
#define CR_BEGIN      \
  do {                \
    switch (crLine) { \
      case CR_START_LINE:

/**
 * @brief End of void function coroutines
 *
 */
#define CR_END(retval)    \
  }                       \
  crLine = CR_START_LINE; \
  return retval;          \
  }                       \
  while (0)

/**
 * @brief End of void function coroutines
 *
 */
#define CR_END_V          \
  }                       \
  crLine = CR_START_LINE; \
  return;                 \
  }                       \
  while (0)

/**
 * @brief Yield the coroutine while returning a value
 *
 */
#define CR_YIELD(retval) \
  do {                   \
    crLine = __LINE__;   \
    return (retval);     \
    case __LINE__:;      \
  } while (0)

/**
 * @brief Yield the coroutine
 *
 */
#define CR_YIELD_V     \
  do {                 \
    crLine = __LINE__; \
    return;            \
    case __LINE__:;    \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 */
#define CR_WAIT(retval, cond)         \
  do {                                \
    crLine = __LINE__;                \
    __attribute__((__fallthrough__)); \
    case __LINE__:                    \
      if (!(cond)) return retval;     \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 */
#define CR_WAIT_V(cond)               \
  do {                                \
    crLine = __LINE__;                \
    __attribute__((__fallthrough__)); \
    case __LINE__:                    \
      if (!(cond)) return;            \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning while returning a value
 *
 */
#define CR_STOP(retval)     \
  do {                      \
    crLine = CR_START_LINE; \
    return (retval);        \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning
 *
 */
#define CR_STOP_V           \
  do {                      \
    crLine = CR_START_LINE; \
    return;                 \
  } while (0)

#endif