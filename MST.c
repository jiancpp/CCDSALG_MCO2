// Include other standard libraries here
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"
#include "MST.h"

/**
 * Performs prim's algorithm to create the minimum spanning tree (MST).
 * 
 * @param graph basis of the minimum spanning tree
 * @return the minimum spanning tree graph
 */
Graph
createMST(Graph* graph)
{
    Graph graphMST = createGraph();
    Heap heap;

    int i, idxA, idxB, vertexIdx = 0;
    String256 a, b; // Temporary variables for vertex a and b names
    Edge tempEdge, minEdge;
    EdgeNode *curEdgeNode;
    Vertex *curVertex;
    bool isVisited[graph->numVertices]; // Stores whether a vertex has been visited or not

    // Initializes
    for (i = 0; i < graph->numVertices; i++)
        isVisited[i] = false;

    initializeHeap(&heap);
    curVertex = &graph->vertexList[vertexIdx];
    addVertex(&graphMST, curVertex->vertex); // Adds first vertex
    isVisited[vertexIdx] = true;

    // Repeats while the vertices are not complete
    while (graphMST.numVertices < graph->numVertices) {
        curEdgeNode = curVertex->edgeListHead;

        // Repeats for all edge nodes
        while (curEdgeNode != NULL) {
            if (!isVisited[getVertexIdx(graph, curEdgeNode->adjVertex->vertex)]) {
                tempEdge = createEdge(curVertex, curEdgeNode->adjVertex, curEdgeNode->weight);
                HeapInsert(&heap, tempEdge);
            }
            curEdgeNode = curEdgeNode->next;
        }

        do {
            if (heap.heapSize == 0) // Returns MST once heap is empty
                return graphMST;

            minEdge = HeapExtractMinimum(&heap);

            idxA = getVertexIdx(graph, minEdge.vertex_a->vertex);
            idxB = getVertexIdx(graph, minEdge.vertex_b->vertex);

        } while (isVisited[idxB]);

        if (!isVisited[idxB]) {
            addVertex(&graphMST, minEdge.vertex_b->vertex); // Adds vertex to MST graph
            curVertex = &graph->vertexList[idxB];
            isVisited[idxB] = true;
        }

        idxA = getVertexIdx(&graphMST, minEdge.vertex_a->vertex);
        idxB = getVertexIdx(&graphMST, minEdge.vertex_b->vertex);
        strcpy(a, graphMST.vertexList[idxA].vertex);
        strcpy(b, graphMST.vertexList[idxB].vertex);

        addEdge(&graphMST, a, b, minEdge.weight); // Adds minimum edge to MST graph
    }

    return graphMST;
}

/**
 * Calculates the total weight of all edges in the graph.
 * 
 * @param graph graph whose all edge weights will be summed
 * @return the resulting sum
 */
int
totalEdgeWeight(Graph* graph)
{
    int i, sum = 0;
    for (i = 0; i < graph->numEdges; i++) {
        sum += graph->edgeList[i].weight; // Adds to sum
    }

    return sum;
} 

/**
 * Displays the minimum spanning tree based on the prescribed format
 * 
 * @param graph graph that will be displayed
 */
void
printMST(Graph* graph) 
{
    String256 vertices[graph->numVertices];

    // Stores vertex names in array
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