/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 *\file moving_average.h
 * 
 * Macro based moving average implementation, instantiate in the file you want to use 
 * the three macros:
 * MOVING_AVERAGE_VARS(name, type, size)
 * MOVING_AVERAGE_PROTO(name, type) // generates prototype definitions
 * MOVING_AVERAGE_FUNCTIONS(name, type, size) // generates the actual code
 * 
 * Using C style template metaprogramming to create type agnostic moving average filter
 * 
 */ 
#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#ifdef __cplusplus
extern "C" {
#endif



#endif