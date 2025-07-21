// Include other standard libraries here
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"
#include "shortestPath.h"

Queue
createShortestPath(Graph* graph, char* src, char* dest) 
{
    Queue path;
    clearQueue(&path);
    // Code here

    return path;
}

int
totalEdgeCost(Queue path) 
{
    int sum = 0;
    // Code here

    return sum;
}

void
printShortestPath(Queue path)
{
    printf("%s", dequeue(&path).vertex);
    while (!isEmptyQueue(&path)) {
        printf(" -> %s", dequeue(&path).vertex);
    }
    printf("; Total edge cost: %d\n", totalEdgeCost(path));
}