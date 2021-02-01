/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/** 
 * \file ringbuf_macro.c
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

#define TEMPLATE_RINGBUF_VARS(name, type, size)                                   \
                                                                                \
    struct                                                                      \
    {                                                                           \
        int    head;                                                       \
        int    tail;                                                       \
        type        name[size];                                                 \
    }ringbuffer##name;                                                               \

#define TEMPLATE_RINGBUF_PROTO(name, type)                                        \
                                                                                \
static void name##Reset(void);                                                  \
static bool name##Full(void);                                                   \
static bool name##Empty(void);                                                  \
static bool name##PushBack(type* p);                                          \
static bool name##PushFront(type* p);                                         \
static bool name##PopBack(type* p);                                           \
static bool name##PopFront(type* p);                                          \


#define TEMPLATE_RINGBUF_FUNCTIONS(name, type, size)                            \
                                                                                \
void name##Reset(void)                                                   \
{                                                                               \
    ringbuffer##name.head = ringbuffer##name.tail = 0;                                    \
}                                                                               \
                                                                                \
static bool name##Full(void)                                                    \
{                                                                               \
    if(ringbuffer##name.head == (ringbuffer##name.tail+1 % size))                         \
        return true;                                                            \
    else                                                                        \
        return false;                                                           \
}                                                                               \
                                                                                \
static bool name##Empty(void)                                                   \
{                                                                               \
    if(ringbuffer##name.head == ringbuffer##name.tail)                                    \
        return true;                                                            \
    else                                                                        \
        return false;                                                           \
}                                                                               \
                                                                            \
static bool name##PushBack(type* p)                                          \
{\
}\
static bool name##PushFront(type* p)                                         \
{\
}\
static bool name##PopBack(type* p)                                           \
{\
}\
static bool name##PopFront(type* p)                                          \
{\
}\

             
#ifdef __cplusplus
}
#endif
                                                                   
#endif
