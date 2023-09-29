/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file sq_tokenconcat.h
 *
 * Contains standard preprocessor token concatenation idiom
 *
 */
#ifndef SQ_TOKENCONCAT_H
#define SQ_TOKENCONCAT_H

/**
 * @brief Token concatenation detail
 */
#define TOKENCONCAT_DETAIL(x, y) x##y

/**
 * @brief Concatenates two tokens
 */
#define TOKENCONCAT(x, y) TOKENCONCAT_DETAIL(x, y)

#endif