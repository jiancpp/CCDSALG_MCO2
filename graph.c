// Include other standard libraries here
#include <stdio.h>
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
addVertex(Graph* graph, char* vertex)
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
getVertexIdx(Graph* graph, char* vertex) 
{
    for (int i = 0; i < graph->numVertices; i++) 
        if (strcmp(vertex, graph->vertexList[i].vertex) == 0)
            return i;
    return -1;
}

void sortEdgeList(EdgeNode* head) {
    EdgeNode* node;
    Vertex* tempVertex;
    int tempWeight, swapped;

    do {
        swapped = 0;
        for (node = head; node && node->next; node = node->next) {
            if (strcmp(node->adjVertex->vertex, node->next->adjVertex->vertex) > 0) {
                // Swap adjVertex pointers
                tempVertex = node->adjVertex;
                node->adjVertex = node->next->adjVertex;
                node->next->adjVertex = tempVertex;

                // Swap weights too if needed to preserve edge meaning
                tempWeight = node->weight;
                node->weight = node->next->weight;
                node->next->weight = tempWeight;

                swapped = 1;
            }
        }
    } while (swapped);
}

void 
addEdge(Graph* graph, char* vertex1, char* vertex2, int weight)
{
    if (graph->numEdges == MAX_CAPACITY - 1 ||
        edgeExists(graph, vertex1, vertex2) ||
        strcmp(vertex1, vertex2) == 0)
        return;

    int idxVertex1 = getVertexIdx(graph, vertex1);
    int idxVertex2 = getVertexIdx(graph, vertex2);

    if (idxVertex1 == -1 || idxVertex2 == -1)
        return;

    Vertex* tempVertex1 = &graph->vertexList[idxVertex1];
    Vertex* tempVertex2 = &graph->vertexList[idxVertex2];

    EdgeNode* tempEdge1 = createEdgeNode(tempVertex2, weight);
    EdgeNode* tempEdge2 = createEdgeNode(tempVertex1, weight);

    insertEdgeAtStart(&tempVertex1->edgeListHead, tempEdge1);    
    insertEdgeAtStart(&tempVertex2->edgeListHead, tempEdge2);    

    graph->edgeList[graph->numEdges] = createEdge(tempVertex1, tempVertex2, weight);
    (graph->numEdges)++;

    sortEdgeList(graph->vertexList[idxVertex1].edgeListHead);
}

int 
getDegree(Graph graph, char* vertex)
{
    int vertexIdx = getVertexIdx(&graph, vertex);
    int degree = 0;

    EdgeNode* pTemp = graph.vertexList[vertexIdx].edgeListHead;

    while (pTemp != NULL) {
        pTemp = pTemp->next;
        degree++;
    }

    return degree;
}

bool 
edgeExists(Graph* graph, char* src, char* dest)
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

bool
checkPath (Graph* graph, char* src, char* dest) {
    Queue path;

    int srcIdx = getVertexIdx(graph, src);

    if (srcIdx == -1)
        return false;

    path = BFS(graph, src);

    while (!isEmptyQueue(&path)) {
        if (strcmp(dequeue(&path).vertex, dest) == 0)
            return true;
    }        

    return false;
}

void 
printGraph(Graph* graph)
{
    printf("G = (V, E)\n");

    printf("V = {");
    for (int i = 0; i < graph->numVertices; i++){
        printf("%s", graph->vertexList[i].vertex);

        if (i != graph->numVertices - 1)
            printf(", ");
        else
            printf("}\n");
    }

    printf("E = {\n");
    for (int i = 0; i < graph->numEdges; i++){
        Edge temp = graph->edgeList[i];
        printf("     (%s, %s, %d)\n", temp.vertex_a->vertex,
                                      temp.vertex_b->vertex,
                                      temp.weight);
    }
    printf("}");

}