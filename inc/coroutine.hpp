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

/**
 * @brief Token concatenation detail
 */

#define TOKENCONCAT_DETAIL(x, y) x##y
/**
 * @brief Concatenates two tokens
 */

#define TOKENCONCAT(x, y) TOKENCONCAT_DETAIL(x, y)
/**
 * @brief Generates an unique coroutine label with the __LINE__ macro
 */
#define CR_LABEL TOKENCONCAT(CR_, __LINE__)

/**
 * @brief Coroutine state structure to be defined in class
 *
 */
struct crState {
  void* label;
  bool initialized;
};

/**
 * @brief Start of coroutine
 *
 * Be aware that the class member crCurrent should be declared and its initialized
 * should be set to false. This way the start coroutine can properly initialize.
 */
#define CR_BEGIN                          \
  do {                                    \
    if (crCurrent.initialized == false) { \
      crCurrent.label = &&CR_START;       \
      crCurrent.initialized = true;       \
    }                                     \
    goto* crCurrent.label;                \
  CR_START:;

/**
 * @brief End of void function coroutines
 *
 */
#define CR_END(retval)          \
  crCurrent.label = &&CR_START; \
  return retval;                \
  }                             \
  while (0)

/**
 * @brief End of void function coroutines
 *
 */
#define CR_END_V                \
  crCurrent.label = &&CR_START; \
  return;                       \
  }                             \
  while (0)

/**
 * @brief Yield the coroutine while returning a value
 *
 */
#define CR_YIELD(retval)          \
  do {                            \
    crCurrent.label = &&CR_LABEL; \
    return (retval);              \
  CR_LABEL:;                      \
  } while (0)

/**
 * @brief Yield the coroutine
 *
 */
#define CR_YIELD_V                \
  do {                            \
    crCurrent.label = &&CR_LABEL; \
    return;                       \
  CR_LABEL:;                      \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 */
#define CR_WAIT(retval, cond)     \
  do {                            \
    crCurrent.label = &&CR_LABEL; \
  CR_LABEL:;                      \
    if (!(cond)) return retval;   \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 */
#define CR_WAIT_V(cond)           \
  do {                            \
    crCurrent.label = &&CR_LABEL; \
  CR_LABEL:;                      \
    if (!(cond)) return;          \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning while returning a value
 *
 */
#define CR_STOP(retval)           \
  do {                            \
    crCurrent.label = &&CR_START; \
    return (retval);              \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning
 *
 */
#define CR_STOP_V                 \
  do {                            \
    crCurrent.label = &&CR_START; \
    return;                       \
  } while (0)

#endif