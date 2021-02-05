/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 *\file ringbuf_macro.c
 * 
 * Macro based ringbuffer implementation, instantiate in the file you want to use 
 * the three macros:
 * TEMPLATE_RINGBUF_VARS(name, type, size)
 * TEMPLATE_RINGBUF_PROTO(name, type) // generates prototype definitions
 * TEMPLATE_RINGBUF_FUNCTIONS(name, type, size) // generates the actual code
 * 
 * Using C style template metaprogramming to create type agnostic ringbuffer
 * 
 */ 
#ifndef RINGBUFFER_MACRO_H
#define RINGBUFFER_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define TEMPLATE_RINGBUF_VARS(name, type, bufsize)\
\
    struct\
    {\
        unsigned int    front;\
        unsigned int    back;\
        type            name[bufsize+1];\
    }ringbuffer##name;\

#define TEMPLATE_RINGBUF_PROTO(name, type)\
\
static void name##Reset(void);\
static bool name##Full(void);\
static bool name##Empty(void);\
static bool name##PushBack(type* p);\
static bool name##PushFront(type* p);\
static bool name##PopBack(type* p);\
static bool name##PopFront(type* p);\


#define TEMPLATE_RINGBUF_FUNCTIONS(name, type, bufsize)\
\
void name##Reset(void)\
{\
    ringbuffer##name.front = ringbuffer##name.back = 0;\
}\
\
static bool name##Full(void)\
{\
    if(ringbuffer##name.back == ((ringbuffer##name.front + 1) % (bufsize + 1)))\
        return true;\
    else\
        return false;\
}\
\
static bool name##Empty(void)\
{\
    if(ringbuffer##name.front == ringbuffer##name.back)\
        return true;\
    else\
        return false;\
}\
\
static bool name##PushBack(type* p)\
{\
    unsigned int temp;\
    if(ringbuffer##name.back == 0)\
        temp = bufsize;\
    else\
        temp = ringbuffer##name.back - 1;\
    if(ringbuffer##name.front == temp)\
        return false;\
    ringbuffer##name.back = temp;\
    ringbuffer##name.name[ringbuffer##name.back] = *p;\
    return true;\
}\
\
static bool name##PushFront(type* p)\
{\
    unsigned int temp =(ringbuffer##name.front + 1) % (bufsize + 1);\
    if(ringbuffer##name.back == temp)\
        return false;\
    ringbuffer##name.name[ringbuffer##name.front] = *p;\
    ringbuffer##name.front = temp;\
    return true;\
}\
\
static bool name##PopBack(type* p)\
{\
    if(ringbuffer##name.back == ringbuffer##name.front)\
        return false;\
    unsigned int temp = (ringbuffer##name.back + 1) % (bufsize + 1);\
    *p = ringbuffer##name.name[ringbuffer##name.back];\
    ringbuffer##name.back = temp;\
    return true;\
}\
\
static bool name##PopFront(type* p)\
{\
    if(ringbuffer##name.back == ringbuffer##name.front)\
        return false;\
    unsigned int temp;\
    if(ringbuffer##name.front == 0)\
        temp = bufsize;\
    else\
        temp = ringbuffer##name.front - 1;\
    *p = ringbuffer##name.name[temp];\
    ringbuffer##name.front = temp;\
    return true;\
}\
\

             
#ifdef __cplusplus
}
#endif
                                                                   
#endif
