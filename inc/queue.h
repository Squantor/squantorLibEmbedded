/*
MIT License

Copyright (c) 2019 Bart Bilos

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
#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <results.h>
#include <stdint.h>

/* 
we differentiate between full and empty by the conditions:
tail == head : empty,
tail+1 == head : full
due to this, we always have one element unused.
Head and tail are always bounded by max
*/

typedef struct {
    const int max;
    int head;
    int tail;
    char * const buf;
} queueChar_t;

typedef struct {
    const int max;
    int head;
    int tail;
    uint8_t * const buf;
} queueUint8_t;

#define queueInit(queue) _Generic((queue), \
    queueChar_t *: queueCharInit, \
    queueUint8_t *: queueUint8Init \
    )(queue)

#define queueState(queue) _Generic((queue), \
    queueChar_t *: queueCharState, \
    queueUint8_t *: queueUint8State \
    )(queue)

#define queueEnqueue(queue, element) _Generic((queue), \
    queueChar_t *: queueCharEnqueue, \
    queueUint8_t *: queueUint8Enqueue \
    )(queue, element)

#define queueDequeue(queue, element) _Generic((queue), \
    queueChar_t *: queueCharDequeue, \
    queueUint8_t *: queueUint8Dequeue \
    )(queue, element)

void queueCharInit(queueChar_t *__restrict__ queue);
result queueCharState(const queueChar_t *__restrict__ queue);
result queueCharEnqueue(queueChar_t *__restrict__ queue, const char p);
result queueCharDequeue(queueChar_t *__restrict__ queue, char *__restrict__ p);

void queueUint8Init(queueUint8_t *__restrict__ queue);
result queueUint8State(const queueUint8_t *__restrict__ queue);
result queueUint8Enqueue(queueUint8_t *__restrict__ queue, const uint8_t p);
result queueUint8Dequeue(queueUint8_t *__restrict__ queue, uint8_t *p);

#ifdef __cplusplus
}
#endif

#endif