#ifndef GRAPH_H
#define GRAPH_H

#include "shared.h"
#include "linkedListGraph.h"

struct Graph {
    int numVertices;
    VertexList vertexListHead; // Dapat ba may pointer?
};

typedef struct Graph Graph;

// Basic Graph Instantiation
Graph* createGraph();
void addVertex(Graph* graph, String256 vertex);
void addEdge(Graph* graph, String256 src, String256 dest);
int getDegree(Graph* graph, String256 vertex);
bool edgeExists(Graph* graph, String256 src, String256 dest);
void printGraph(Graph* graph);

#endif
