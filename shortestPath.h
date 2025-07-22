#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "shared.h"
#include "heap.h"
#include "stack.h"
#include "traversal.h"
#include "linkedListGraph.h"

struct Path {
    int cost;
    Vertex* prev;
};

struct Graph;
typedef struct Graph Graph;
typedef struct Path Path;

void getMinPaths(Path pathList[], Graph* graph, char* src);
Stack createShortestPath(Graph* graph, char* src, char* dest, int* cost);
void printShortestPath(Stack path, int totalCost);

#endif