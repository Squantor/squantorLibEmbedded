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
 * @brief
 *
 * @param context context of the coroutine
 *
 */
#define CR_BEGIN(context)                \
  util::coroState& localState = context; \
  do {                                   \
    if (localState.label == nullptr) {   \
      localState.label = &&CR_START;     \
    }                                    \
    goto* localState.label;              \
  CR_START:;

/**
 * @brief End of non void function coroutines
 *
 * @param retval return value to pass
 *
 */
#define CR_END(retval)           \
  localState.label = &&CR_START; \
  return retval;                 \
  }                              \
  while (0)

/**
 * @brief End of void function coroutines
 *
 */
#define CR_END_V()               \
  localState.label = &&CR_START; \
  return;                        \
  }                              \
  while (0)

/**
 * @brief Yield the coroutine while returning a value
 *
 * @param retval return value to pass
 *
 */
#define CR_YIELD(retval)           \
  do {                             \
    localState.label = &&CR_LABEL; \
    return (retval);               \
  CR_LABEL:;                       \
  } while (0)

/**
 * @brief Yield the coroutine
 *
 */
#define CR_YIELD_V()               \
  do {                             \
    localState.label = &&CR_LABEL; \
    return;                        \
  CR_LABEL:;                       \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 * @param retval return value to pass
 * @param cond condition to wait for
 *
 */
#define CR_WAIT(retval, cond)      \
  do {                             \
    localState.label = &&CR_LABEL; \
  CR_LABEL:;                       \
    if (!(cond)) return retval;    \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 * @param cond condition to wait for
 *
 */
#define CR_WAIT_V(cond)            \
  do {                             \
    localState.label = &&CR_LABEL; \
  CR_LABEL:;                       \
    if (!(cond)) return;           \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning while returning a value
 *
 * @param retval return value to pass
 *
 */
#define CR_STOP(retval)            \
  do {                             \
    localState.label = &&CR_START; \
    return (retval);               \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning
 *
 */
#define CR_STOP_V(context)         \
  do {                             \
    localState.label = &&CR_START; \
    return;                        \
  } while (0)

#endif