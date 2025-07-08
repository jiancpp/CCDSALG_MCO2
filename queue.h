#ifndef QUEUE_H
#define QUEUE_H

#include "shared.h"

typedef struct {
    String256 collection[256];
    int tail; // index of last added element
    int head; // index of first added element
} Queue;

void        clearQueue      (Queue *queue);
bool        isFullQueue     (Queue *queue);
bool        isEmptyQueue    (Queue *queue);
void        enqueue         (Queue *queue, char* item);
const char* dequeue         (Queue *queue);
char*       peekQueue       (Queue *queue);

#endif
