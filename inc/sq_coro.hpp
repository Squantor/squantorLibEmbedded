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
#ifndef SQ_CORO_HPP
#define SQ_CORO_HPP

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
}  // namespace util

/**
 * @brief Start of coroutine
 *
 * @param context context of the coroutine
 *
 */
#define CR_BEGIN(context)                                       \
  util::coroState& localState = context;                        \
  do {                                                          \
    if (localState.label == nullptr) {                          \
      _Pragma("GCC diagnostic ignored \"-Wdangling-pointer\""); \
      localState.label = &&CR_START;                            \
      _Pragma("GCC diagnostic pop");                            \
    }                                                           \
    goto* localState.label;                                     \
  CR_START:;

/**
 * @brief End of non void function coroutines
 *
 * @param retval return value to pass
 *
 */
#define CR_END(retval)                                      \
  _Pragma("GCC diagnostic ignored \"-Wdangling-pointer\""); \
  localState.label = &&CR_START;                            \
  _Pragma("GCC diagnostic pop");                            \
  return retval;                                            \
  }                                                         \
  while (0)

/**
 * @brief End of void function coroutines
 *
 */
#define CR_END_V()                                          \
  _Pragma("GCC diagnostic ignored \"-Wdangling-pointer\""); \
  localState.label = &&CR_START;                            \
  _Pragma("GCC diagnostic pop");                            \
  return;                                                   \
  }                                                         \
  while (0)

/**
 * @brief Yield the coroutine while returning a value
 *
 * @param retval return value to pass
 *
 */
#define CR_YIELD(retval)                                      \
  do {                                                        \
    _Pragma("GCC diagnostic ignored \"-Wdangling-pointer\""); \
    localState.label = &&CR_LABEL;                            \
    _Pragma("GCC diagnostic pop");                            \
    return (retval);                                          \
  CR_LABEL:;                                                  \
  } while (0)

/**
 * @brief Yield the coroutine
 *
 */
#define CR_YIELD_V()                                          \
  do {                                                        \
    _Pragma("GCC diagnostic ignored \"-Wdangling-pointer\""); \
    localState.label = &&CR_LABEL;                            \
    _Pragma("GCC diagnostic pop");                            \
    return;                                                   \
  CR_LABEL:;                                                  \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 * @param retval return value to pass
 * @param cond condition to wait for
 *
 */
#define CR_WAIT(retval, cond)                                 \
  do {                                                        \
    _Pragma("GCC diagnostic ignored \"-Wdangling-pointer\""); \
    localState.label = &&CR_LABEL;                            \
    _Pragma("GCC diagnostic pop");                            \
  CR_LABEL:;                                                  \
    if (!(cond))                                              \
      return retval;                                          \
  } while (0)

/**
 * @brief Wait the coroutine on condition
 *
 * @param cond condition to wait for
 *
 */
#define CR_WAIT_V(cond)                                       \
  do {                                                        \
    _Pragma("GCC diagnostic ignored \"-Wdangling-pointer\""); \
    localState.label = &&CR_LABEL;                            \
    _Pragma("GCC diagnostic pop");                            \
  CR_LABEL:;                                                  \
    if (!(cond))                                              \
      return;                                                 \
  } while (0)

/**
 * @brief redo previous code on condition
 *
 * @param cond condition to check
 * @param retval return value to return
 */
#define CR_RETRY(retval, cond) \
  do {                         \
    if (!(cond))               \
      return retval;           \
  } while (0)

/**
 * @brief redo previous code on condition
 *
 * @param cond condition to check
 */
#define CR_RETRY_V(cond) \
  do {                   \
    if (!(cond))         \
      return;            \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning while returning a value
 *
 * @param retval return value to pass
 *
 */
#define CR_STOP(retval)                                       \
  do {                                                        \
    _Pragma("GCC diagnostic ignored \"-Wdangling-pointer\""); \
    localState.label = &&CR_START;                            \
    _Pragma("GCC diagnostic pop");                            \
    return (retval);                                          \
  } while (0)

/**
 * @brief Stop coroutine and go to beginning
 *
 */
#define CR_STOP_V(context)                                    \
  do {                                                        \
    _Pragma("GCC diagnostic ignored \"-Wdangling-pointer\""); \
    localState.label = &&CR_START;                            \
    _Pragma("GCC diagnostic pop");                            \
    return;                                                   \
  } while (0)

#endif