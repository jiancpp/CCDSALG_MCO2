#include <stdbool.h>
#include <string.h>
#include "queue.h"

/**
 * This function clears a queue by resetting the indices
 * head (start) to 0, and tail (end) to -1.
 * @param queue the stack to be cleared
 */
void
clearQueue (Queue *queue)
{
    queue->head = 0;
    queue->tail = -1;
}

/**
 * This function checks if the queue is full based on the maximum capacity.
 * @param queue the stack to be checked if full
 * @return (a) true if queue is full;
 *         (b) false if queue is not full.
 */
bool
isFullQueue (Queue *queue)
{
    if (queue->tail == MAX_CAPACITY - 2) {
        return true;
    } else return false;
}

/**
 * This function checks if the queue is empty.
 * @param queue the queue to be checked if empty
 * @return (a) true if queue is empty;
 *         (b) false if queue has at least one element.
 */
bool
isEmptyQueue (Queue *queue)
{
    if (queue->head > queue->tail) {
        return true;
    } else return false;
}

/**
 * This function dequeues (removes) the last element of the queue and returns it.
 * @param queue the queue to be dequeued
 * @return dequeued element 
 */
const char*
dequeue (Queue *queue)
{
    const char *temp = queue->collection[queue->head];
    (queue->head)++;

    return temp;
}

/**
 * This function enqueues (inserts) an item to the queue.
 * @param queue queue to be added on
 * @param item element to be enqueued to the queue
 */
void
enqueue (Queue *queue, char* item)
{
    // Note: Tail points to index of last added element
    (queue->tail)++; // incrementing to avoid overwriting previous element
    strcpy (queue->collection[queue->tail], item);
}

/**
 * This function returns the element at the tail (end) of the queue.
 * @param queue queue to be peeked
 * @return element at the tail of the queue
 */
char*
peekQueue (Queue *queue)
{
    return queue->collection[queue->tail];
}