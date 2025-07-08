// Include other standard libraries here
#include <stdlib.h>

#include "singlyLinkedList.h"

void freeList(List* list) {
    Node* pTemp;
    while (*list != NULL) {
        pTemp = *list;
        *list = (*list)->pNext;
        freeNode(pTemp);
    }
}

Node* createNode(String256 vertex) {
    Node* pNew;
    pNew = (Node*) malloc (sizeof(Node));
    strcpy(pNew->vertex,vertex);
    pNew->pNext = NULL; 

    return pNew;
}

void insertAtEnd(List* list, Node* pNew) {
    Node* pTemp = *list;
    pNew->pNext = NULL;

    if (*list == NULL) {
        *list = pNew;
        return;
    }
        
    while (pTemp->pNext != NULL)
        pTemp = pTemp->pNext;
    
    pTemp->pNext = pNew;
}

void deleteFromEnd(List* list) {
    Node* pTemp = *list;

    if ((*list) == NULL) 
        return;
    
    if (pTemp->pNext == NULL) {
        freeNode(pTemp);
        *list = NULL;
        return;
    }

    while (pTemp->pNext->pNext != NULL)
        pTemp = pTemp->pNext;

    freeNode(pTemp->pNext);
}

Node* search(List list, String256 vertex) {
    Node* pCur = list;

    while (pCur != NULL) {
        if (strcmp(pCur->vertex, vertex) == 0)
            return pCur;
        pCur = pCur->pNext;    
    }

    return NULL;
}

void freeNode(Node* node) {
    free(node);
    node = NULL;
}