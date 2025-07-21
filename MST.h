#ifndef MST_H
#define MST_H

#include "shared.h"
#include "queue.h"
#include "heap.h"
#include "linkedListGraph.h"

struct Graph;
typedef struct Graph Graph;

Graph createMST(Graph* graph);
int totalEdgeWeight(Graph* graph);
void printMST(Graph* graph);

#endif