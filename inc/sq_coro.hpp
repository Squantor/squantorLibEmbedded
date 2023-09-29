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

#include "sq_coro_common.h"

namespace util {
/**
 * @brief Coroutine state class to be defined in class
 *
 */
class coroState {
 public:
  coroState() : label{nullptr} {};
  ~coroState() = default;
  void* label;
};
}

/**
 * @brief Start of coroutine
 *
 * Be aware that the class member crCurrent should be declared and its initialized
 * should be set to false. This way the start coroutine can properly initialize.
 */
#define CR_BEGIN                      \
  do {                                \
    if (crCurrent.label == nullptr) { \
      crCurrent.label = &&CR_START;   \
    }                                 \
    goto* crCurrent.label;            \
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