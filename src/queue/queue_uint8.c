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

#include <queue.h>

void queueUint8Init(queueUint8_t *restrict queue)
{
    queue->head = 0;
    queue->tail = 0;
}

result queueUint8State(const queueUint8_t *restrict queue)
{
    if(queue->head == queue->tail)
        return queueEmpty;
    else if(((queue->head+1) % queue->max) == queue->tail)
        return queueFull;
    else
        return queueNotEmpty;    
}

result queueUint8Enqueue(queueUint8_t *restrict queue, const uint8_t p)
{
    int newHead = (queue->head+1) % queue->max;
    if(newHead == queue->tail)
        return queueFull;
    queue->buf[queue->head] = p;
    queue->head = newHead;
    return noError;
}

result queueUint8Dequeue(queueUint8_t *restrict queue, uint8_t *restrict p)
{
    if(queue->head == queue->tail)
        return queueEmpty;
    *p = queue->buf[queue->tail];
    queue->tail = (queue->tail+1) % queue->max;
    return noError;
}