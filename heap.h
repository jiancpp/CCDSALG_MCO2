#ifndef HEAP_H
#define HEAP_H

#include "shared.h"
typedef struct {
    Edge array[MAX_CAPACITY]; // Indexing will start at 1
    int heapSize;
} Heap;

void initializeHeap(Heap* heap);
int Parent(int idx);
int Left(int idx);
int Right(int idx);
void MinHeapify(Heap* heap, int idx);
void swap(Edge *a, Edge *b);
void BuildMinHeap(Heap* heap, int heapSize);
Edge HeapMinimum(Heap* heap);
Edge HeapExtractMinimum(Heap* heap);

#endif

