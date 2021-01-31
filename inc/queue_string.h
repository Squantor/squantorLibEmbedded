#ifndef QUEUE_STRING_H
#define QUEUE_STRING_H

#include <results.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct queueString
{
    // mask be power of two!
    const uint16_t  mask;
    uint16_t        head;
    uint16_t        tail;
    char *          data;
} t_queueString;

// add string, if it does not fit, oldest gets deleted
result queueStringEnqueue(t_queueString *queue, char *__restrict__ s);
// remove last added string
result queueStringDequeue(t_queueString *queue, char *__restrict__ s);
// get first string in queue
result queueStringFirst(const t_queueString *__restrict__ queue, uint16_t *__restrict__ i, char *__restrict__ s);
// get previous string in queue from i
result queueStringPrev(const t_queueString *__restrict__ queue, uint16_t *__restrict__ i, char *__restrict__ s);
// get next string in queue from i
result queueStringNext(const t_queueString *__restrict__ queue, uint16_t *__restrict__ i, char *__restrict__ s);

#ifdef __cplusplus
}
#endif

#endif
