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
 * TEMPLATE_QUEUE_VARS(name, type, size)
 * TEMPLATE_QUEUE_PROTO(name, type) // generates prototype definitions
 * TEMPLATE_QUEUE_FUNCTIONS(name, type, size) // generates the actual code
 * 
 * Using C style template metaprogramming to create type agnostic ringbuffer
 * 
 */ 
#ifndef RINGBUFFER_MACRO_H
#define RINGBUFFER_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <results.h>
#include <stdbool.h>

#define TEMPLATE_QUEUE_VARS(name, type, size)                                   \
                                                                                \
    struct                                                                      \
    {                                                                           \
        uint32_t    head;                                                       \
        uint32_t    tail;                                                       \
        type        name[size];                                                 \
    }queue##name;                                                               \

#define TEMPLATE_QUEUE_PROTO(name, type)                                        \
                                                                                \
static void name##Reset(void);                                                  \
static bool name##Full(void);                                                   \
static bool name##Empty(void);                                                  \
static result name##PushBack(type* p);                                          \
static result name##PushFront(type* p);                                         \
static result name##PopBack(type* p);                                           \
static result name##PopFront(type* p);                                          \


#define TEMPLATE_QUEUE_FUNCTIONS(name, type, size)                              \
                                                                                \
static void name##Reset(void)                                                   \
{                                                                               \
    queue##name.head = queue##name.tail = 0;                                    \
}                                                                               \
                                                                                \
static result name##State(void)                                                 \
{                                                                               \
    if(queue##name.head == queue##name.tail)                                    \
        return queueEmpty;                                                      \
    else if(((queue##name.head+1) & mask) == queue##name.tail)                  \
        return queueFull;                                                       \
    else                                                                        \
        return queueNotEmpty;                                                   \
}                                                                               \
                                                                                \
static result name##Enqueue(type* p)                                            \
{                                                                               \
    uint32_t newHead = (queue##name.head+1) & mask;                             \
    if(newHead == queue##name.tail)                                             \
        return queueFull;                                                       \
    queue##name.name[queue##name.head] = *p;                                    \
    queue##name.head = newHead;                                                 \
    return noError;                                                             \
}                                                                               \
                                                                                \
static result name##Dequeue(type* p)                                            \
{                                                                               \
    if(queue##name.head == queue##name.tail)                                    \
        return queueEmpty;                                                      \
    *p = queue##name.name[queue##name.tail];                                    \
    queue##name.tail = (queue##name.tail+1) & mask;                             \
    return noError;                                                             \
}                                                                               \
             
#ifdef __cplusplus
}
#endif
                                                                   
#endif
