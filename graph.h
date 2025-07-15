#ifndef GRAPH_H
#define GRAPH_H

#include "shared.h"
#include "linkedListGraph.h"
struct Graph {
    int numVertices;
    Vertex* vertexList; // Dynamic Array of vertices
    Edge* edgeList; // Dynamic Array of Edge structs
};

typedef struct Graph Graph;

// Basic Graph Instantiation
Graph* createGraph();
void addVertex(Graph* graph, String256 vertex);
void addEdge(Graph* graph, String256 vertex1, String256 vertex2);
int getDegree(Graph* graph, String256 vertex);
bool edgeExists(Graph* graph, String256 src, String256 dest);
void printGraph(Graph* graph);

#endif
