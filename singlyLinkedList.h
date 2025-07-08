#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "graph.h"

struct singlyNodeTag {
    Vertex data;
    Node* pNext;
};

typedef struct singlyNodeTag Node;
typedef struct singlyNodeTag* List;

void freeList(List* list);
void insertAtEnd(List* list, Node* pNew);
void deleteFromEnd(List* list);
Node* search(List list, Vertex data);

#endif