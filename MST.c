// Include other standard libraries here
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"
#include "MST.h"

Graph
createMST(Graph* graph)
{
    Graph graphMST = createGraph();
    Heap heap;
    int i, idxA, idxB, vertexIdx = 0;
    String256 a, b;
    Edge tempEdge, minEdge;
    EdgeNode *curEdgeNode;
    Vertex *curVertex;
    bool isVisited[graph->numVertices];

    // Initializes
    for (i = 0; i < graph->numVertices; i++)
        isVisited[i] = false;

    initializeHeap(&heap);
    curVertex = &graph->vertexList[vertexIdx];
    addVertex(&graphMST, curVertex->vertex);
    isVisited[vertexIdx] = true;

    while (graphMST.numVertices < graph->numVertices) {
        curEdgeNode = curVertex->edgeListHead;

        while (curEdgeNode != NULL) {
            if (!isVisited[getVertexIdx(graph, curEdgeNode->adjVertex->vertex)]) {
                tempEdge = createEdge(curVertex, curEdgeNode->adjVertex, curEdgeNode->weight);
                HeapInsert(&heap, tempEdge);
            }
            curEdgeNode = curEdgeNode->next;
        }

        do {
            if (heap.heapSize == 0)
                return graphMST;

            minEdge = HeapExtractMinimum(&heap);

            idxA = getVertexIdx(graph, minEdge.vertex_a->vertex);
            idxB = getVertexIdx(graph, minEdge.vertex_b->vertex);

        } while (isVisited[idxB]);

        if (!isVisited[idxB]) {
            addVertex(&graphMST, minEdge.vertex_b->vertex);
            curVertex = &graph->vertexList[idxB];
            isVisited[idxB] = true;
        }

        idxA = getVertexIdx(&graphMST, minEdge.vertex_a->vertex);
        idxB = getVertexIdx(&graphMST, minEdge.vertex_b->vertex);
        strcpy(a, graphMST.vertexList[idxA].vertex);
        strcpy(b, graphMST.vertexList[idxB].vertex);

        addEdge(&graphMST, a, b, minEdge.weight);
    }

    return graphMST;
}

int
totalEdgeWeight(Graph* graph)
{
    int i, sum = 0;
    for (i = 0; i < graph->numEdges; i++) {
        sum += graph->edgeList[i].weight;
    }

    return sum;
} 

void
printMST(Graph* graph) 
{
    String256 vertices[graph->numVertices];

    for (int i = 0; i < graph->numVertices; i++) {
        strcpy(vertices[i], graph->vertexList[i].vertex);
    }

    sortVertices(vertices, graph->numVertices);

    printf("MST(G) = (V, E)\n");

    printf("V = {");
    for (int i = 0; i < graph->numVertices; i++){
        printf("%s", vertices[i]);

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
    printf("}\n");
    
    printf("Total Edge Weight: %d\n", totalEdgeWeight(graph));
}