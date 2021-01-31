/*
The MIT License (MIT)

Copyright (c) 2015 Anton Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
queue instantiation macro's used by the primary user of the queue.
Restrictions:
only use direct types that can be copied by assignment.
*/

#ifndef __QUEUE_TEMPLATE_H__
#define __QUEUE_TEMPLATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <results.h>

#define TEMPLATE_QUEUE_VARS(name, type, size)                                   \
                                                                                \
    struct                                                                      \
    {                                                                           \
        uint32_t    head;                                                       \
        uint32_t    tail;                                                       \
        type        name[size];                                                 \
    }queue##name;                                                               \

#define TEMPLATE_QUEUE_PROTO(name, type )                                       \
                                                                                \
static void name##Init(void);                                                   \
static result name##State(void);                                                \
static result name##Enqueue(type* p);                                           \
static result name##Dequeue(type* p);                                           \

#define TEMPLATE_QUEUE_FUNCTIONS(name, type, size, mask)                        \
                                                                                \
static void name##Init(void)                                                    \
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
