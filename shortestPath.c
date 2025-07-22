// Include other standard libraries here
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"
#include "shortestPath.h"

void
getMinPaths(Path pathList[], Graph* graph, char* src)
{
    int numVertices = graph->numVertices;
    int i, curIdx, adjIdx, weight;
    Edge curEdge, tempEdge;
    EdgeNode* adjNode;
    Heap minHeap;
    bool isVisited[numVertices];

    // Initialize
    initValues(isVisited, numVertices);
    initializeHeap(&minHeap);
    for (i = 0; i < numVertices; i++) {
        pathList[i].cost = INT_MAX;
        pathList[i].prev = NULL;
    }

    curIdx = getVertexIdx(graph, src);

    tempEdge.vertex_a = &graph->vertexList[curIdx];
    tempEdge.vertex_b = &graph->vertexList[curIdx];
    tempEdge.weight = 0;

    // Add source heap and path list
    HeapInsert(&minHeap, tempEdge);
    pathList[curIdx].cost = 0;
    pathList[curIdx].prev = &graph->vertexList[curIdx];

    while (minHeap.heapSize != 0) {
        curEdge = HeapExtractMinimum(&minHeap);
        curIdx = getVertexIdx(graph, curEdge.vertex_b->vertex);

        if (isVisited[curIdx])
            continue;
        else 
            isVisited[curIdx] = true;

        adjNode = graph->vertexList[curIdx].edgeListHead;

        while (adjNode != NULL) {
            adjIdx = getVertexIdx(graph, adjNode->adjVertex->vertex);
            weight = adjNode->weight;

            if (!isVisited[adjIdx] && pathList[curIdx].cost + weight < pathList[adjIdx].cost) {
                pathList[adjIdx].cost = pathList[curIdx].cost + weight;
                pathList[adjIdx].prev = curEdge.vertex_b;

                tempEdge.vertex_a = curEdge.vertex_b;
                tempEdge.vertex_b = &graph->vertexList[adjIdx];
                HeapInsert(&minHeap, tempEdge);
            }

            adjNode = adjNode->next;
        }
    }
}

Stack
createShortestPath(Graph* graph, char* src, char* dest, int* cost) 
{
    int idx;
    Stack path;
    Path pathList[graph->numVertices];

    // Initialize
    clearStack(&path);
    getMinPaths(pathList, graph, src);
    
    idx = getVertexIdx(graph, dest);

    if (pathList[idx].cost == -1)
        return path;
    
    *cost = pathList[idx].cost;

    while (!isFullStack(&path) &&
          pathList[idx].prev != NULL &&
          strcmp(graph->vertexList[idx].vertex, src) != 0) {

        pushStack(&path, graph->vertexList[idx]);
        idx = getVertexIdx(graph, pathList[idx].prev->vertex);
    } 

    pushStack(&path, graph->vertexList[idx]);

    return path;
}

void
printShortestPath(Stack path, int totalCost)
{
    printf("%s", popStack(&path).vertex);
    while (!isEmptyStack(&path)) {
        printf(" -> %s", popStack(&path).vertex);
    }
    printf("; Total edge cost: %d\n", totalCost);
}