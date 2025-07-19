// Include other standard libraries here
#include <stdbool.h>

#include "heap.h"
#include "linkedListGraph.h"

/**
 * This function initializes a heap by setting the last (last index) to -1.
 * @param heap the heap to be initialized
 */
void initializeHeap(Heap* heap) 
{
    heap->heapSize = 0;
}

/**
 * This function swaps two elements in the heap
 * @param a an element within a heap
 * @param b an element within a heap
 */
void 
swap(Edge* a, Edge* b) 
{
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

int 
Parent(int idx) 
{
    return idx / 2;
}

int
Left(int idx)
{
    return idx * 2;
}

int
Right(int idx)
{
    return idx * 2 + 1;
}

void 
MinHeapify(Heap* heap, int idx)
{
    int low = idx;
    int left = Left(idx);
    int right = Right(idx);

    if (left <= heap->heapSize && heap->array[left] < heap->array[idx]) {
        low = left;
    }

    if (right <= heap->heapSize && heap->array[right] < heap->array[low]) {
        low = right;
    }

    if (low != idx) {
        swap(heap->array[low], heap->array[idx]);
        MinHeapify(heap, low); // Recursion
    }
}

void 
BuildMinHeap(Heap* heap, int heapSize)
{
    heap->heapSize = heapSize;

    for (int j = heapSize / 2; j >= 1; j--) {
        MinHeapify(heap, j);
    }
}

bool
isHeapEmpty(Heap* heap)
{
    return heap->heapSize == 0;
}

Edge 
HeapMinimum(Heap* heap)
{
    if (isHeapEmpty(heap)) {
        return;
    }

    MinHeapify(heap, 1);
    return heap->array[1];
}

Edge 
HeapExtractMinimum(Heap* heap)
{
    int first, last;
    Edge minWeight;

    first = 1;
    last = heap->heapSize;
    minWeight = heap->array[first];

    swap(heap->array[first], heap->array[last]);
    heap->heapSize--;

    MinHeapify(heap, 1);
    return minWeight;
}