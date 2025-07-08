#ifndef GRAPH_H
#define GRAPH_H

#include "shared.h"

#define MAX_VERTICES 128
#define MAX_EDGES 256
struct VertexTag{
    String256 name;
    int degree;
};

struct EdgeTag{
    Vertex* initial;
    Vertex* terminal;
    int weight;
};

struct GraphTag
{
    String256 name;
    Vertex vertices[MAX_VERTICES];
    Edge edges[MAX_EDGES];
    int verticesSize;
    int edgesSize;
};

typedef struct VertexTag Vertex;
typedef struct EdgeTag Edge;
typedef struct GraphTag Graph;

#endif
