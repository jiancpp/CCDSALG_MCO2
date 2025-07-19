#ifndef GRAPH_H
#define GRAPH_H

#include "shared.h"
#include "linkedListGraph.h"

struct Graph {
    int numVertices;
    int numEdges;
    Vertex vertexList[MAX_CAPACITY];
    Edge edgeList[MAX_CAPACITY];
};

typedef struct Graph Graph;

// Basic Graph Instantiation
Graph createGraph();
void addVertex(Graph* graph, char* vertex);
void addEdge(Graph* graph, char* vertex1, char* vertex2, int weight);
int getDegree(Graph graph, char* vertex);
bool edgeExists(Graph* graph, char* src, char* dest);
void printGraph(Graph* graph);

#endif
