/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file sq_coro_common.h
 *
 * contains common macros for coroutines
 *
 */
#ifndef SQ_CORO_COMMON_H
#define SQ_CORO_COMMON_H

#include "sq_tokenconcat.h"

/**
 * @brief Generates an unique coroutine label with the __LINE__ macro
 */
#define CR_LABEL TOKENCONCAT(CR_, __LINE__)

#define CR_START cr_start /**< standard coroutine start */

#endif