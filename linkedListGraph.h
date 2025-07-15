#ifndef LINKEDLISTGRAPH_H

#define LINKEDLISTGRAPH_H

#include "shared.h"

struct Vertex {
    String256 vertex;
    EdgeList edgeListHead; // Linked list of EdgeNode structs
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

typedef struct Vertex Vertex;
typedef struct VertexNode VertexNode;
typedef struct Edge Edge;
typedef struct EdgeNode EdgeNode;
typedef struct EdgeNode* EdgeList;

// Edge Linked List Operations
void freeEdgeList(EdgeList* listHead);
EdgeNode* createEdgeNode(VertexNode* adjVertex, int weight);
void insertEdgeAtEnd(EdgeList* listHead, EdgeNode* pNew);
void deleteEdgeFromEnd(EdgeList* list);
EdgeNode* searchEdge(EdgeList listHead, String256 key);
void freeEdgeNode(EdgeNode* node);


#endif