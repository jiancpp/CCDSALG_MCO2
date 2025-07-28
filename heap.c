// Include other standard libraries here
#include <stdbool.h>

#include "heap.h"
#include "linkedListGraph.h"

/**
 * Initializes a heap by setting its size to 0.
 * 
 * @param heap - pointer to the heap to be initialized
 */
void initializeHeap(Heap* heap) 
{
    heap->heapSize = 0;
}

/**
 * This function swaps two elements in the heap
 * 
 * @param a - pointer to the first Edge
 * @param b - pointer to the second Edge
 */
void 
swap(Edge* a, Edge* b) 
{
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Gets the parent index of a node in the heap.
 *
 * @param idx - index of the node
 * @return index of the parent node
 */
int 
Parent(int idx) 
{
    return idx / 2;
}

/**
 * Gets the left child index of a node in the heap.
 *
 * @param idx - index of the node
 * @return index of the left child node
 */
int
Left(int idx)
{
    return idx * 2;
}

/**
 * Gets the right child index of a node in the heap.
 *
 * @param idx - index of the node
 * @return index of the right child node
 */
int
Right(int idx)
{
    return idx * 2 + 1;
}

/**
 * Inserts an Edge into the heap while maintaining the min-heap property.
 *
 * @param heap - pointer to the heap
 * @param edge - Edge to insert
 */
void 
HeapInsert(Heap* heap, Edge edge) {
    int idx;
    
    if (heap->heapSize >= MAX_CAPACITY - 1)
        return;

    // Insert at the end
    heap->heapSize++;
    idx = heap->heapSize;
    heap->array[idx] = edge;

    // Bubble up
    while (idx > 1 && heap->array[Parent(idx)].weight > heap->array[idx].weight) {
        swap(&heap->array[idx], &heap->array[Parent(idx)]);
        idx = Parent(idx);
    }
}

/**
 * Maintains the min-heap property by moving the element at index idx down
 * to its correct position.
 *
 * @param heap - pointer to the heap
 * @param idx - index of the element to heapify
 */
void 
MinHeapify(Heap* heap, int idx)
{
    int low = idx;
    int left = Left(idx);
    int right = Right(idx);

    if (left <= heap->heapSize && heap->array[left].weight < heap->array[idx].weight) {
        // Will swap low with the left child
        low = left;
    }

    if (right <= heap->heapSize && heap->array[right].weight < heap->array[low].weight) {
        // Will swap low with the right child
        low = right;
    }

    if (low != idx) {
        swap(&heap->array[low], &heap->array[idx]);
        // Recursion to maintain min-heap property within the new subtree
        MinHeapify(heap, low);  
    }
}

/**
 * Builds a min-heap from an unordered array of edges.
 *
 * @param heap - pointer to the heap
 * @param heapSize - number of elements to include in the heap
 */
void 
BuildMinHeap(Heap* heap, int heapSize)
{
    heap->heapSize = heapSize;

    for (int j = heapSize / 2; j >= 1; j--) {
        MinHeapify(heap, j);
    }
}

/**
 * Checks whether the heap is empty.
 *
 * @param heap - pointer to the heap
 * @return true if the heap is empty, false otherwise
 */
bool
isHeapEmpty(Heap* heap)
{
    return heap->heapSize == 0;
}

/**
 * Retrieves the minimum element in the heap without removing it.
 *
 * @param heap - pointer to the heap
 * @return Edge with the smallest weight
 */
Edge 
HeapMinimum(Heap* heap)
{
    MinHeapify(heap, 1);
    return heap->array[1];
}

/**
 * Extracts and removes the minimum element (root) from the heap.
 *
 * @param heap - pointer to the heap
 * @return Edge with the smallest weight that was removed
 */
Edge 
HeapExtractMinimum(Heap* heap)
{
    int first, last;
    Edge minWeight;

    first = 1;
    last = heap->heapSize;
    minWeight = heap->array[first];

    swap(&heap->array[first], &heap->array[last]);
    heap->heapSize--;

    MinHeapify(heap, 1);
    return minWeight;
}