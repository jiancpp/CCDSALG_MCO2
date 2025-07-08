#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "shared.h"
#include "graph.h"

struct singlyNodeTag {
    String256 vertex;
    Node* pNext;
};

typedef struct singlyNodeTag Node;
typedef struct singlyNodeTag* List;

void freeList(List* list);
Node* createNode(String256 vertex);
void insertAtEnd(List* list, Node* pNew);
void deleteFromEnd(List* list);
Node* search(List list, String256 vertex);
void freeNode(Node* node);

#endif