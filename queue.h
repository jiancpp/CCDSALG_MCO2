#ifndef QUEUE_H
#define QUEUE_H

#include "shared.h"
#include "linkedListGraph.h"

typedef struct {
    Vertex collection[256];
    int tail; // index of last added element
    int head; // index of first added element
} Queue;

void        clearQueue      (Queue *queue);
bool        isFullQueue     (Queue *queue);
bool        isEmptyQueue    (Queue *queue);
void        enqueue         (Queue *queue, Vertex item);
Vertex      dequeue         (Queue *queue);
Vertex      peekQueue       (Queue *queue);

#endif
