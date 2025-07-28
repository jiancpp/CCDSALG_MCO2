// Include other standard libraries here
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"
#include "shortestPath.h"

/**
 * Computes the shortest paths from a source vertex to all other vertices 
 * in the graph using Dijkstra's algorithm.
 *
 * @param pathList - an array of Path structs to store the shortest paths
 * @param graph - pointer to the graph
 * @param src - the starting vertex name
 */
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

    // Set default path values
    for (i = 0; i < numVertices; i++) {
        pathList[i].cost = INT_MAX;
        pathList[i].prev = NULL;
    }

    // Get the index of the source vertex
    curIdx = getVertexIdx(graph, src);

    // Start from the source vertex
    tempEdge = createEdge(&graph->vertexList[curIdx], &graph->vertexList[curIdx], 0);
    HeapInsert(&minHeap, tempEdge);
    pathList[curIdx].cost = 0;
    pathList[curIdx].prev = &graph->vertexList[curIdx];

    while (minHeap.heapSize != 0) {
        // Extract vertex with the minimum cost
        curEdge = HeapExtractMinimum(&minHeap);
        curIdx = getVertexIdx(graph, curEdge.vertex_b->vertex);

        // Skip visited vertices
        if (isVisited[curIdx])
            continue;
        else 
            isVisited[curIdx] = true;

        // Traverse adjacency list of the current vertex
        adjNode = graph->vertexList[curIdx].edgeListHead;

        while (adjNode != NULL) {
            adjIdx = getVertexIdx(graph, adjNode->adjVertex->vertex);
            weight = adjNode->weight;

            // Update the path if a shorter route to the adjacent vertex is found
            if (!isVisited[adjIdx] && pathList[curIdx].cost + weight < pathList[adjIdx].cost) {
                pathList[adjIdx].cost = pathList[curIdx].cost + weight;
                pathList[adjIdx].prev = curEdge.vertex_b;

                // Push the updated path into the heap
                tempEdge = createEdge(curEdge.vertex_b, &graph->vertexList[adjIdx], pathList[adjIdx].cost);
                HeapInsert(&minHeap, tempEdge);
            }

            adjNode = adjNode->next;
        }
    }
}

/**
 * Constructs the shortest path from a source vertex to a destination vertex.
 * The resulting path is returned as a stack.
 *
 * @param graph - pointer to the graph
 * @param src - name of the source vertex
 * @param dest - name of the destination vertex
 * @param cost - pointer to an integer where the total path cost will be stored
 * @return a stack of vertices representing the shortest path from src to dest
 */
Stack
createShortestPath(Graph* graph, char* src, char* dest, int* cost) 
{
    int idx;
    Stack path;
    Path pathList[graph->numVertices];

    // Initialize
    clearStack(&path);

    // Compute shortest paths from the source vertex
    getMinPaths(pathList, graph, src);
    
    // Get the index of the destination vertex
    idx = getVertexIdx(graph, dest);

    // If destination is unreachable, return an empty path with cost 0
    if (pathList[idx].cost == INT_MAX) {
        *cost = 0;
        return path;
    }
    
    // Store the total cost of the shortest path
    *cost = pathList[idx].cost;

    // Backtrack from destination to source
    while (!isFullStack(&path) &&
          pathList[idx].prev != NULL &&
          strcmp(graph->vertexList[idx].vertex, src) != 0) {

        pushStack(&path, graph->vertexList[idx]);
        idx = getVertexIdx(graph, pathList[idx].prev->vertex);
    } 

    // Push the source node
    pushStack(&path, graph->vertexList[idx]);

    return path;
}

/**
 * Prints the shortest path stored in a stack, from source to destination,
 * along with the total cost of the path.
 *
 * @param path - stack containing the vertices in the shortest path
 * @param totalCost - total cost of all edges in the path
 */
void
printShortestPath(Stack path, int totalCost)
{
    printf("\n");
    
    if (!isEmptyStack(&path)) {
        printf("%s", popStack(&path).vertex);
        while (!isEmptyStack(&path)) {
            printf(" -> %s", popStack(&path).vertex);
        }
        printf("; Total edge cost: %d\n", totalCost);
    } else
        printf("0\n");
}