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

    sortVertices(graph);
}

int
getVertexIdx(Graph* graph, char* vertex) 
{
    for (int i = 0; i < graph->numVertices; i++) 
        if (strcmp(vertex, graph->vertexList[i].vertex) == 0)
            return i;
    return -1;
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

    sortEdges(graph);
    sortEdgeList(graph->vertexList[idxVertex1].edgeListHead);
    sortEdgeList(graph->vertexList[idxVertex2].edgeListHead);
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
sortVertices(Graph* graph) {
    int i, j, size;
    Vertex temp;

    size = graph->numVertices;

    for (i = 0; i < size - 1; i++) 
        for (j = i + 1; j < size; j++) 
            if (strcmp(graph->vertexList[i].vertex, graph->vertexList[j].vertex) > 0) {
                // Swap 
                temp = graph->vertexList[i];
                graph->vertexList[i] = graph->vertexList[j];
                graph->vertexList[j] = temp;
            }
}

void 
sortEdges(Graph* graph) {
    int i, j, size;
    char *a1, *a2, *b1, *b2, *temp;
    Edge tempEdge;

    size = graph->numEdges;

    for (i = 0; i < size - 1; i++) 
        for (j = i + 1; j < size; j++) {
            a1 = graph->edgeList[i].vertex_a->vertex;
            b1 = graph->edgeList[i].vertex_b->vertex;
            a2 = graph->edgeList[j].vertex_a->vertex;
            b2 = graph->edgeList[j].vertex_b->vertex;

            // Sort vertices within an edge
            if (strcmp(a1, b1) > 0) { 
                temp = a1; 
                a1 = b1; 
                b1 = temp; 
            }

            if (strcmp(a2, b2) > 0) { 
                temp = a2; 
                a2 = b2; 
                b2 = temp; 
            }

            if (strcmp(a1, a2) > 0 || 
               (strcmp(a1, a2) == 0 && strcmp(b1, b2) > 0)) {
                // Swap edges
                tempEdge = graph->edgeList[i];
                graph->edgeList[i] = graph->edgeList[j];
                graph->edgeList[j] = tempEdge;
            }
        }
}

void 
sortEdgeList(EdgeNode* head) {
    EdgeNode* node;
    Vertex* tempVertex;
    int swapped, tempWeight;

    if (head == NULL) 
        return;

    do {
        swapped = 0;
        node = head;

        while (node->next != NULL) {
            if (strcmp(node->adjVertex->vertex, node->next->adjVertex->vertex) > 0) {
                // Swap adjVertex
                tempVertex = node->adjVertex;
                node->adjVertex = node->next->adjVertex;
                node->next->adjVertex = tempVertex;

                // Swap weight
                tempWeight = node->weight;
                node->weight = node->next->weight;
                node->next->weight = tempWeight;

                swapped = 1;
            }
            node = node->next;
        }
    } while (swapped);
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
    printf("\n");
}