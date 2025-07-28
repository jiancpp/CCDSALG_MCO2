// Include other standard libraries here
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graph.h"

/**
 * This function creates an initialized Graph struct
 * 
 * @return Graph struct
 */
Graph 
createGraph()
{
    Graph temp;
    temp.numVertices = 0;
    temp.numEdges = 0;

    return temp;
}

/**
 * This function add a new vertex to the graph
 * 
 * @param graph - pointer to the graph struct
 * @param vertex - name of the vertex to be added
 */
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

/**
 * This function searches a vertex through the graph's array of vertices and
 * returns its index.
 * 
 * @param graph - pointer to the graph struct
 * @param vertex - name of vertex being searched
 * @return index of the vertex; -1 if not found
 */
int
getVertexIdx(Graph* graph, char* vertex) 
{
    for (int i = 0; i < graph->numVertices; i++) 
        if (strcmp(vertex, graph->vertexList[i].vertex) == 0)
            return i;
    return -1;
}

/**
 * This function add a new edge connecting two different
 * vertices in the graph
 * 
 * @param graph - pointer to the graph struct
 * @param vertex1 - name of the first vertex
 * @param vertex2 - name of the second vertex
 * @param weight - weight of the edge
 */
void 
addEdge(Graph* graph, char* vertex1, char* vertex2, int weight)
{
    // Check whether inputs are valid
    if (graph->numEdges == MAX_CAPACITY - 1 ||
        edgeExists(graph, vertex1, vertex2) ||
        strcmp(vertex1, vertex2) == 0)
        return;

    int idxVertex1 = getVertexIdx(graph, vertex1);
    int idxVertex2 = getVertexIdx(graph, vertex2);

    // Check whether both vertices were found
    if (idxVertex1 == -1 || idxVertex2 == -1)
        return;

    // Add edge nodes both vertices' edge list
    Vertex* tempVertex1 = &graph->vertexList[idxVertex1];
    Vertex* tempVertex2 = &graph->vertexList[idxVertex2];

    EdgeNode* tempEdge1 = createEdgeNode(tempVertex2, weight);
    EdgeNode* tempEdge2 = createEdgeNode(tempVertex1, weight);

    insertEdgeAtStart(&tempVertex1->edgeListHead, tempEdge1);    
    insertEdgeAtStart(&tempVertex2->edgeListHead, tempEdge2);    

    // Add edge to graph's edge list (Arrange lexicographically)
    if (strcmp(tempVertex1->vertex, tempVertex2->vertex) < 0) {
        graph->edgeList[graph->numEdges] = createEdge(tempVertex1, tempVertex2, weight);
    }
    else {
        graph->edgeList[graph->numEdges] = createEdge(tempVertex2, tempVertex1, weight);

    }
    (graph->numEdges)++;

    sortEdges(graph);
    sortEdgeList(graph->vertexList[idxVertex1].edgeListHead);
    sortEdgeList(graph->vertexList[idxVertex2].edgeListHead);
}

/**
 * Computes the degree (number of adjacent edges) of a given vertex.
 * 
 * @param graph - Graph by value
 * @param vertex - name of the vertex
 * @return Degree of the vertex; 0 if not found
 */
int 
getDegree(Graph graph, char* vertex)
{
    int vertexIdx = getVertexIdx(&graph, vertex);
    int degree = 0;

    if (vertexIdx == -1)
        return 0;

    EdgeNode* pTemp = graph.vertexList[vertexIdx].edgeListHead;

    while (pTemp != NULL) {
        pTemp = pTemp->next;
        degree++;
    }

    return degree;
}

/**
 * Checks if an edge exists between two vertices.
 * 
 * @param graph - pointer to the Graph struct
 * @param src - source vertex
 * @param dest - destination vertex
 * @return true if the edge exists; false otherwise
 */
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

/**
 * Checks if a path exists between two vertices in a graph using BFS.
 *
 * @param graph - pointer to the graph structure
 * @param src - the source vertex 
 * @param dest - the destination vertex
 * @return true if a path exists from src to dest, false otherwise
 */
bool 
checkPath(Graph* graph, char* src, char* dest) {
    Queue path;

    // Get index of the source vertex
    int srcIdx = getVertexIdx(graph, src);

    if (srcIdx == -1)
        return false;

    // Perform BFS starting from the source vertex
    path = BFS(graph, src);

    // Check if destination vertex appears in the BFS traversal
    while (!isEmptyQueue(&path)) {
        if (strcmp(dequeue(&path).vertex, dest) == 0)
            return true;
    }        

    // Destination not found in the path
    return false;
}

/**
 * Sorts an array of vertex names lexicographically.
 * 
 * @param vertices - array of vertex names
 * @param size - number of vertices
 */

void 
sortVertices(String256 vertices[], int size) {
    int i, j;
    String256 temp;

    for (i = 0; i < size - 1; i++) 
        for (j = i + 1; j < size; j++) 
            if (strcmp(vertices[i], vertices[j]) > 0) {
                // Swap 
                strcpy(temp, vertices[i]);
                strcpy(vertices[i], vertices[j]);
                strcpy(vertices[j], temp);
            }
}


/**
 * Sorts the graph's edge list in lexicographic order by vertex names.
 * 
 * @param graph - pointer to the Graph struct
 */
void 
sortEdges(Graph* graph) {
    int i, j, numEdges;
    char *a1, *a2, *b1, *b2;
    Edge tempEdge;

    numEdges = graph->numEdges;

    // Sort edges
    for (i = 0; i < numEdges - 1; i++) {
        for (j = i + 1; j < graph->numEdges; j++) {
            a1 = graph->edgeList[i].vertex_a->vertex;
            b1 = graph->edgeList[i].vertex_b->vertex;
            a2 = graph->edgeList[j].vertex_a->vertex;
            b2 = graph->edgeList[j].vertex_b->vertex;

            if (strcmp(a1, a2) > 0 || 
               (strcmp(a1, a2) == 0 && strcmp(b1, b2) > 0)) {
                // Swap edges
                tempEdge = graph->edgeList[i];
                graph->edgeList[i] = graph->edgeList[j];
                graph->edgeList[j] = tempEdge;
            }
        }
    }
}


/**
 * Sorts an edge list alphabetically by adjacent vertex name.
 * 
 * @param head - pointer to the head of the edge list
 */
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


/**
 * Prints the graph in adjacency list and edge list format.
 * 
 * @param graph - pointer to the Graph struct
 */
void 
printGraph(Graph* graph)
{
    String256 vertices[MAX_CAPACITY];

    for (int i = 0; i < graph->numVertices; i++) {
        strcpy(vertices[i], graph->vertexList[i].vertex);
    }

    sortVertices(vertices, graph->numVertices);

    printf("G = (V, E)\n");

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
    printf("}");
    printf("\n");
}