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
        type            name[bufsize];\
    }movingAverage##name;\

#define MOVING_AVERAGE_PROTO(name, type)\
\
void name##Reset(void);\
void name##Add(type value);\
type name##Get(void);\


#define MOVING_AVERAGE_FUNCTIONS(name, type, bufsize)\
\
void name##Reset(void)\
{\
    movingAverage##name.front = 0;\
    movingAverage##name.movingAverage = 0;\
    for(int i = 0; i < bufsize; i++)\
        movingAverage##name.name[i] = 0;\
}\
void name##Add(type value)\
{\
    movingAverage##name.movingAverage -= movingAverage##name.name[movingAverage##name.front];\
    movingAverage##name.name[movingAverage##name.front] = value;\
    movingAverage##name.movingAverage += value;\
    unsigned int temp = movingAverage##name.front + 1;\
    if(temp == bufsize)\
        movingAverage##name.front = 0;\
    else\
        movingAverage##name.front = temp;\
}\
type name##Get(void)\
{\
    return movingAverage##name.movingAverage / bufsize;\
}\


#endif