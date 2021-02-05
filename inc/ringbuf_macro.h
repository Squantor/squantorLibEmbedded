/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 *\file ringbuf_macro.h
 * 
 * Macro based ringbuffer implementation, instantiate in the file you want to use 
 * the three macros:
 * RINGBUF_VARS(name, type, size)
 * RINGBUF_PROTO(name, type) // generates prototype definitions
 * RINGBUF_FUNCTIONS(name, type, size) // generates the actual code
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

#define RINGBUF_VARS(name, type, bufsize)\
\
    struct\
    {\
        unsigned int    front;\
        unsigned int    back;\
        type            name[bufsize+1];\
    }ringbuffer##name;\

#define RINGBUF_PROTO(name, type)\
\
void name##Reset(void);\
bool name##Full(void);\
bool name##Empty(void);\
bool name##PushBack(type* p);\
bool name##PushFront(type* p);\
bool name##PopBack(type* p);\
bool name##PopFront(type* p);\


#define RINGBUF_FUNCTIONS(name, type, bufsize)\
\
void name##Reset(void)\
{\
    ringbuffer##name.front = ringbuffer##name.back = 0;\
}\
\
bool name##Full(void)\
{\
    if(ringbuffer##name.back == ((ringbuffer##name.front + 1) % (bufsize + 1)))\
        return true;\
    else\
        return false;\
}\
\
bool name##Empty(void)\
{\
    if(ringbuffer##name.front == ringbuffer##name.back)\
        return true;\
    else\
        return false;\
}\
\
bool name##PushBack(type* p)\
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
bool name##PushFront(type* p)\
{\
    unsigned int temp =(ringbuffer##name.front + 1) % (bufsize + 1);\
    if(ringbuffer##name.back == temp)\
        return false;\
    ringbuffer##name.name[ringbuffer##name.front] = *p;\
    ringbuffer##name.front = temp;\
    return true;\
}\
\
bool name##PopBack(type* p)\
{\
    if(ringbuffer##name.back == ringbuffer##name.front)\
        return false;\
    unsigned int temp = (ringbuffer##name.back + 1) % (bufsize + 1);\
    *p = ringbuffer##name.name[ringbuffer##name.back];\
    ringbuffer##name.back = temp;\
    return true;\
}\
\
bool name##PopFront(type* p)\
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
