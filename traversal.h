#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "shared.h"
#include "stack.h"
#include "queue.h"
#include "linkedListGraph.h"

struct Graph;
typedef struct Graph Graph;


void initValues(bool array[], int size);
Queue BFS(Graph* graph, char* start);
Queue DFS(Graph* graph, char* start);  

#endif