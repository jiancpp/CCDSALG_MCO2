#ifndef HEAP_H
#define HEAP_H

#include "shared.h"
typedef struct {
    int array[MAX_CAPACITY];
    int capacity;
    int last;
} Heap;

#endif

