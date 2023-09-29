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
#define CR_BEGIN(context)           \
  do {                              \
    if (context.label == nullptr) { \
      context.label = &&CR_START;   \
    }                               \
    goto* context.label;            \
  CR_START:;

/**
 * @brief End of non void function coroutines
 *
 * @param context context of the coroutine
 * @param retval return value to pass
 *
 */
#define CR_END(context, retval) \
  context.label = &&CR_START;   \
  return retval;                \
  }                             \
  while (0)

/**
 * @brief End of void function coroutines
 *
 * @param context context of the coroutine
 *
 */
#define CR_END_V(context)     \
  context.label = &&CR_START; \
  return;                     \
  }                           \
  while (0)

/**
 * @brief Yield the coroutine while returning a value
 *
 * @param context context of the coroutine
 * @param retval return value to pass
 *
 */
#define CR_YIELD(context, retval) \
  do {                            \
    context.label = &&CR_LABEL;   \
    return (retval);              \
  CR_LABEL:;                      \
  } while (0)

/**
 * @brief Yield the coroutine
 *
 * @param context context of the coroutine
 *
 */
#define CR_YIELD_V(context)     \
  do {                          \
    context.label = &&CR_LABEL; \
    return;                     \
  CR_LABEL:;                    \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 * @param context context of the coroutine
 * @param retval return value to pass
 * @param cond condition to wait for
 *
 */
#define CR_WAIT(context, retval, cond) \
  do {                                 \
    context.label = &&CR_LABEL;        \
  CR_LABEL:;                           \
    if (!(cond)) return retval;        \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 * @param context context of the coroutine
 * @param cond condition to wait for
 *
 */
#define CR_WAIT_V(context, cond) \
  do {                           \
    context.label = &&CR_LABEL;  \
  CR_LABEL:;                     \
    if (!(cond)) return;         \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning while returning a value
 *
 * @param context context of the coroutine
 * @param retval return value to pass
 *
 */
#define CR_STOP(context, retval) \
  do {                           \
    context.label = &&CR_START;  \
    return (retval);             \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning
 *
 * @param context context of the coroutine
 *
 */
#define CR_STOP_V(context)      \
  do {                          \
    context.label = &&CR_START; \
    return;                     \
  } while (0)

#endif