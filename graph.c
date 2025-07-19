// Include other standard libraries here
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graph.h"

Graph 
createGraph()
{
    Graph temp;
    temp.numVertices = 0;
    temp.numEdges = 0;

    return temp;
}

void 
addVertex(Graph* graph, String256 vertex)
{
    int numVertices;

    Vertex temp;
    strcpy(temp.vertex, vertex);
    temp.edgeListHead = NULL;

    numVertices = graph->numVertices;

    if (numVertices < MAX_CAPACITY - 1) {
        graph->vertexList[numVertices] = temp;
        (graph->numVertices)++;
    }
}

int
getVertexIdx(Graph* graph, String256 vertex) 
{
    for (int i = 0; i < graph->numVertices; i++) 
        if (strcmp(vertex, graph->vertexList[i].vertex) == 0)
            return i;
    return -1;
}

void 
addEdge(Graph* graph, String256 vertex1, String256 vertex2, int weight)
{
    if (graph->numEdges < MAX_CAPACITY - 1)
        return;

    int idxVertex1 = getVertexIdx(graph, vertex1);
    int idxVertex2 = getVertexIdx(graph, vertex2);

    if (idxVertex1 == -1 || idxVertex2 == -1)
        return;

    Vertex* tempVertex1 = &graph->vertexList[idxVertex1];
    Vertex* tempVertex2 = &graph->vertexList[idxVertex2];

    EdgeNode* tempEdge1 = createEdgeNode(tempVertex2, weight);
    EdgeNode* tempEdge2 = createEdgeNode(tempVertex1, weight);

    insertEdgeAtStart(tempVertex1->edgeListHead, tempEdge1);    
    insertEdgeAtStart(tempVertex2->edgeListHead, tempEdge1);    

    graph->edgeList[graph->numEdges] = createEdge(tempVertex1, tempVertex2, weight);
    (graph->numEdges)++;
}

int 
getDegree(Graph* graph, String256 vertex)
{
    int vertexIdx = getVertexIdx(graph, vertex);
    int degree = 0;

    EdgeNode* pTemp = graph->vertexList[vertexIdx].edgeListHead;

    while (pTemp != NULL) {
        pTemp = pTemp->next;
        degree++;
    }

    return degree;
}

bool 
edgeExists(Graph* graph, String256 src, String256 dest)
{
    int srcIdx = getVertexIdx(graph, src);

    if (srcIdx == -1)
        return false;

    EdgeNode* pTemp = graph->vertexList[srcIdx].edgeListHead;

    while (pTemp != NULL) {
        if (strcmp(dest, pTemp->adjVertex->vertex) == 0)
            return true;

        pTemp = pTemp->next;
    }

    return false;
}

void printGraph(Graph* graph);