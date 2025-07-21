#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "shared.h"
#include "stack.h"
#include "queue.h"
#include "linkedListGraph.h"
#include "graph.h"

void initValues(bool array[], int size);
Queue BFS(Graph graph, Vertex start); 

#endif