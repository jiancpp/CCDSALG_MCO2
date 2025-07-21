#ifndef LINKEDLISTGRAPH_H

#define LINKEDLISTGRAPH_H

#include "shared.h"

typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct EdgeNode EdgeNode;
typedef struct EdgeNode* EdgeList;

struct Vertex {
    String256 vertex;
    EdgeNode* edgeListHead; // Linked list of EdgeNode structs
};

struct Edge {
    Vertex* vertex_a;
    Vertex* vertex_b;
    int weight;
};

struct EdgeNode {
    Vertex* adjVertex;
    int weight;
    EdgeNode* next;
};
 
// Edge Linked List Operations
void freeEdgeList(EdgeList* listHead);
Edge createEdge(Vertex* vertex1, Vertex* vertex2, int weight);
EdgeNode* createEdgeNode(Vertex* adjVertex, int weight);
void insertEdgeAtStart(EdgeList* listHead, EdgeNode* pNew);
void deleteEdgeFromStart(EdgeList* list);
EdgeNode* searchEdge(EdgeList listHead, String256 key);
void freeEdgeNode(EdgeNode* node);


#endif