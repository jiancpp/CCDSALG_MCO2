#ifndef GRAPHLINKEDLIST_H

#define GRAPHLINKEDLIST_H

#include "shared.h"

struct EdgeNode {
    VertexNode* dest;
    int weight;
    EdgeNode* next;
};

struct VertexNode {
    String256 vertex;
    EdgeList edgeListHead;
    VertexNode* next;
};

typedef struct EdgeNode EdgeNode;
typedef struct EdgeNode* EdgeList;
typedef struct VertexNode VertexNode;
typedef struct VertexNode* VertexList;

// Vertex Linked List Operations
void freeVertexList(VertexList* listHead);
VertexNode* createVertexNode(String256 vertex);
void insertVertexAtEnd(VertexList* listHead, VertexNode* pNew);
void deleteVertexFromEnd(VertexList* listHead);
VertexNode* searchVertex(VertexList listHead, String256 key);
void freeVertexNode(VertexNode* node);

// Edge Linked List Operations
void freeEdgeList(EdgeList* listHead);
EdgeNode* createEdgeNode(VertexNode* dest, int weight);
void insertEdgeAtEnd(EdgeList* listHead, EdgeNode* pNew);
void deleteEdgeFromEnd(EdgeList* list);
EdgeNode* searchEdge(EdgeList listHead, String256 key);
void freeEdgeNode(EdgeNode* node);


#endif