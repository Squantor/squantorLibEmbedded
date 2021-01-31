/*
The MIT License (MIT)

Copyright (c) 2018 Anton Bilos

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

#include <results.h>
#include <queue_string.h>
#include <string.h>

#define WRAP(value, len) ((value) & (len))

// helper functions
// search forward for seperator
static uint16_t SeekForwardSep(const t_queueString *restrict queue, uint16_t idx)
{
    while(queue->data[idx] != 0)
        idx = WRAP(idx + 1, queue->mask);
    return idx;
}

// search forward for not seperator
static uint16_t SeekForwardNotSep(const t_queueString *restrict queue, uint16_t idx)
{
    uint16_t newIndex = idx;
    while(queue->data[newIndex] == 0)
    {
        newIndex = WRAP(newIndex + 1, queue->mask);
        // if we are equal to tail, then we are empty, return
        if(newIndex == queue->head)
            return newIndex;
    }
    return newIndex;
}

// search backward for seperator
static uint16_t SeekBackSep(const t_queueString *restrict queue, uint16_t idx)
{
    uint16_t newIndex = WRAP(idx - 1, queue->mask);
    // first scan backwards for one or more NUL chars while checking the tail
    while(queue->data[newIndex] == 0)
    {
        newIndex = WRAP(newIndex - 1, queue->mask);
        // reached end, new index is old index
        if(newIndex == queue->tail)
            return idx;
    }
    // then scan backwards for one or more non NUL characters while checking the tail
    while(queue->data[newIndex] != 0)
    {
        newIndex = WRAP(newIndex - 1, queue->mask);
        // we dont check for tail, tail always should end on a NUL char
        // this way we prevent not losing the last string
    }
    // return the new index
    return WRAP(newIndex + 1, queue->mask);
}

result queueStringEnqueue(t_queueString *restrict queue, char *restrict s)
{
    if((queue == NULL) || (s == NULL))
        return invalidArg;
        
    uint16_t stringSize = strlen(s);
    if(!(stringSize > 0) || !(stringSize < queue->mask))
        return dataInvalid;
    
    // now also add the zero terminator
    stringSize++;
    // do we have enough space to add at the head?
    uint16_t newHead;
    if((stringSize) > (queue->mask - queue->head))
    {
        // no, clear the end so we do not find strings later on there
        memset(&(queue->data[queue->head]), 0, queue->mask - queue->head);
        // reset head to 0
        newHead = 0;
        // did we overtake the tail? (also take into account tail is zero)
        if(queue->head < queue->tail || queue->tail == newHead)
            // put tail beyond so overtake will detect it
            queue->tail = stringSize;
    }
    else
    {
        // yes, append to head
        newHead = queue->head;
    }
    
    // will the new head overtake the tail?
    if((newHead < queue->tail) && (queue->tail <= (newHead + stringSize)))
    {
        // yes, search new place for tail
        uint16_t newtail = newHead + stringSize;
        newtail = SeekForwardSep(queue, newtail);
        queue->tail = SeekForwardNotSep(queue, newtail);
    }
    // we made some space at newHead, overwrite
    strcpy(&(queue->data[newHead]), s);
    // point to next space
    queue->head = newHead + stringSize;
    return noError;
}

result queueStringDequeue(t_queueString *restrict queue, char *restrict s)
{
    if((queue == NULL) || (s == NULL))
        return invalidArg;
    if(queue->head == queue->tail)
        return queueEmpty;
    
    uint16_t newtail = queue->tail;
    // dequeue into s until size or zero
    // no refactor as it would need strlen, strcpy combo
    while(queue->data[newtail] != 0)
    {
        *s = queue->data[newtail];
        newtail++; s++;
    }
    *s = 0; 
    newtail++;
    newtail = SeekForwardNotSep(queue, newtail);
    queue->tail = newtail;
    return noError;
}

result queueStringPrev(const t_queueString *restrict queue, uint16_t *restrict i, char *restrict s)
{
    if((queue == NULL) || (i == NULL) || (s == NULL))
        return invalidArg;
    if((queue->head == queue->tail) || (queue->tail == *i))
        return queueEmpty;
    // search backwards from current index index
    uint16_t indexNew = SeekBackSep(queue, *i);
    if(indexNew == *i)
        return queueEmpty;
    // copy over string to s
    strcpy(s, &(queue->data[indexNew]));
    *i = indexNew;
    return noError;
}

result queueStringNext(const t_queueString *restrict queue, uint16_t *restrict i, char *restrict s)
{
    if((queue == NULL) || (i == NULL) || (s == NULL))
        return invalidArg;
    if((queue->head == queue->tail) || (queue->head == *i))
        return queueEmpty;
    // we are sure that something is at *i, return it
    strcpy(s, &(queue->data[*i]));
    // now that we copied it, find new index
    uint16_t indexNew = *i;
    indexNew = SeekForwardSep(queue, indexNew);
    // point to begin of string
    indexNew = SeekForwardNotSep(queue, indexNew);
    *i = indexNew;
    return noError;
}