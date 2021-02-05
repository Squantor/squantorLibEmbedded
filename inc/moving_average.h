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

#define MOVING_AVERAGE_VARS(name, type, bufsize)\
\
    struct\
    {\
        unsigned int    front;\
        type            movingAverage;\
        type            name[bufsize+1];\
    }ringbuffer##name;\

#define MOVING_AVERAGE_PROTO(name, type)\
\
void name##Reset(void);\
void name##Add(void);\
void name##Get(void);\


#define MOVING_AVERAGE_FUNCTIONS(name, type, bufsize)\
\
void name##Reset(void)\
{\
}\
void name##Add(void)\
{\
}\
void name##Get(void)\
{\
}\


#endif