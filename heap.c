// Include other standard libraries here

#include "heap.h"

/**
 * This function initializes a heap by setting the last (last index) to -1.
 * @param heap the heap to be initialized
 */
void initializeHeap(Heap* heap) 
{
    heap->capacity = MAX_CAPACITY;
    heap->last = -1;
}

/**
 * This function swaps two elements in the heap
 * @param a an element within a heap
 * @param b an element within a heap
 */
void swap(int* a, int* b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Insert

// Extract Min/Max

// Peek


// Delete

// Increase/Decrease Key

// Build Heap


/*
References:
https://www.tutorialspoint.com/data_structures_algorithms/heap_data_structure.htm

*/