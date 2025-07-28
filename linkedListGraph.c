#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedListGraph.h"

/**
 * Frees all EdgeNodes in a given edge list.
 *
 * @param listHead - pointer to the head of the edge list
 */
void 
freeEdgeList(EdgeList* listHead)
{
    EdgeNode* pTemp;
    while (*listHead != NULL) {
        pTemp = *listHead;
        *listHead = (*listHead)->next;
        freeEdgeNode(pTemp);
    }
}

/**
 * Creates an Edge structure connecting two vertices with a given weight.
 *
 * @param vertex1 - pointer to the first vertex
 * @param vertex2 - pointer to the second vertex
 * @param weight - weight of the edge
 * @return Edge structure containing the vertices and weight
 */
Edge
createEdge(Vertex* vertex1, Vertex* vertex2, int weight)
{
    Edge temp;
    temp.vertex_a = vertex1;
    temp.vertex_b = vertex2;
    temp.weight = weight;

    return temp;
}

/**
 * Creates a new EdgeNode with the given adjacent vertex and weight.
 *
 * @param adjVertex - pointer to the adjacent vertex of the edge
 * @param weight - weight of the edge
 * @return pointer to the newly allocated EdgeNode
 */
EdgeNode* 
createEdgeNode(Vertex* adjVertex, int weight)
{
    EdgeNode* pNew;
    pNew = (EdgeNode*) malloc (sizeof(EdgeNode));
    pNew->adjVertex = adjVertex;
    pNew->weight = weight;
    pNew->next = NULL; 

    return pNew;
}

/**
 * Inserts an EdgeNode at the start of a vertex's edge list.
 *
 * @param listHead - pointer to the head of the edge list
 * @param pNew - pointer to the EdgeNode to be inserted
 */
void 
insertEdgeAtStart(EdgeList* listHead, EdgeNode* pNew)
{
    pNew->next = *listHead;
    *listHead = pNew;
}

/**
 * Deletes the first EdgeNode from a vertex's edge list.
 *
 * @param listHead - pointer to the head of the edge list
 */
void 
deleteEdgeFromStart(EdgeList* listHead)
{
    EdgeNode* pTemp = (*listHead)->next;

    if (pTemp->next != NULL)
        *listHead = pTemp->next;
    else
        *listHead = NULL;
}

/**
 * Frees a single EdgeNode.
 *
 * @param node - pointer to the EdgeNode to free
 */

void 
freeEdgeNode(EdgeNode* node)
{
    free(node);
    node = NULL;
}
