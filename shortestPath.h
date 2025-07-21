#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "shared.h"
#include "heap.h"
#include "queue.h"
#include "linkedListGraph.h"

struct Graph;
typedef struct Graph Graph;

Queue createShortestPath(Graph* graph, char* src, char* dest);
int totalEdgeCost(Queue path);
void printShortestPath(Queue path);

#endif