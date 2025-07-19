#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedListGraph.h"

void 
freeEdgeList(EdgeList* listHead)
{
    EdgeNode* pTemp;
    while (*listHead != NULL) {
        pTemp = *listHead;
        *listHead = (*listHead)->next;
        freeNode(pTemp);
    }
}

Edge
createEdge(Vertex* vertex1, Vertex* vertex2, int weight)
{
    Edge temp;
    temp.vertex_a = vertex1;
    temp.vertex_b = vertex2;
    temp.weight = weight;

    return temp;
}

EdgeNode* 
createEdgeNode(Vertex* adjVertex, int weight)
{
    EdgeNode* pNew;
    pNew = (EdgeNode*) malloc (sizeof(EdgeNode));
    pNew->adjVertex = adjVertex;
    pNew->next = NULL; 

    return pNew;
}

void 
insertEdgeAtStart(EdgeList* listHead, EdgeNode* pNew)
{
    pNew->next = *listHead;
    *listHead = pNew;
}

void 
deleteEdgeFromStart(EdgeList* listHead)
{
    EdgeNode* pTemp = (*listHead)->next;

    if (pTemp->next != NULL)
        *listHead = pTemp->next;
    else
        *listHead = NULL;
}

// EdgeNode* 
// searchEdge(EdgeList listHead, String256 key)
// {
    
// }

// void freeEdgeNode(EdgeNode* node);
