#ifndef LINKEDLISTGRAPH_H

#define LINKEDLISTGRAPH_H

#include "shared.h"

typedef struct EdgeNode EdgeNode;
typedef struct Vertex {
    String256 vertex;
    EdgeNode* edgeListHead; // Linked list of EdgeNode structs
} Vertex;

typedef struct Edge {
    Vertex* vertex_a;
    Vertex* vertex_b;
    int weight;
} Edge;

typedef struct EdgeNode {
    Vertex* adjVertex;
    int weight;
    EdgeNode* next;
} EdgeNode;

typedef struct EdgeNode* EdgeList;
 
// Edge Linked List Operations
void freeEdgeList(EdgeList* listHead);
Edge createEdge(Vertex* vertex1, Vertex* vertex2, int weight);
EdgeNode* createEdgeNode(Vertex* adjVertex, int weight);
void insertEdgeAtStart(EdgeList* listHead, EdgeNode* pNew);
void deleteEdgeFromStart(EdgeList* list);
EdgeNode* searchEdge(EdgeList listHead, String256 key);
void freeEdgeNode(EdgeNode* node);


#endif