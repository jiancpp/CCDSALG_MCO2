#ifndef MST_H
#define MST_H

#include "shared.h"
#include "queue.h"
#include "heap.h"
#include "linkedListGraph.h"

struct Graph;
typedef struct Graph Graph;

void createMST(Graph* graph, Graph* graphMST);
int totalEdgeWeight(Graph* graph);
void printMST(Graph* graph);

#endif