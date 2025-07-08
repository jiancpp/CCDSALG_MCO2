// Include other standard libraries here
#include <string.h>
#include <stdbool.h>

#include "graph.h"

void
initializeGraph(Graph* ptrGraph, char* name) 
{
    strcpy(ptrGraph->name, name);
    ptrGraph->verticesSize = 0;
    ptrGraph->edgesSize = 0;
}

bool
isVerticesFull(Graph* ptrGraph) {
    if (ptrGraph->verticesSize == MAX_VERTICES)
        return true;
    else return false;
}

bool
isEdgesFull(Graph* ptrGraph) {
    if (ptrGraph->edgesSize == MAX_EDGES)
        return true;
    else return false;
}

Vertex*
getVertexByName(Graph* ptrGraph, char* name)
{
    if (ptrGraph == NULL)
        return NULL;

    for (int i = 0; i <= ptrGraph->verticesSize; i++) {
        if (strcmp(ptrGraph->vertices[i].name, name) == 0) {
            return &ptrGraph->vertices[i];
        }
    }
    return NULL;
}

void 
addVertex(Graph* ptrGraph, char* name)
{
    Vertex newVertex;
    strcpy(newVertex.name, name);
    newVertex.degree = 0;

    if (!isVerticesFull(ptrGraph)) {
        ptrGraph->vertices[ptrGraph->verticesSize + 1] = newVertex;
        ptrGraph->verticesSize++;
    }
}

bool
addEdge(Graph* ptrGraph, char* name1, char* name2)
{
    if (!isEdgesFull(ptrGraph)) {
        Edge newEdge;
        newEdge.initial = getVertexByName(ptrGraph, name1);
        newEdge.terminal = getVertexByName(ptrGraph, name2);

        if (newEdge.initial != NULL && newEdge.terminal != NULL) {
            // Update each vertex's degree
            newEdge.initial->degree++;
            newEdge.terminal->degree++;

            // Add new edge to graph
            ptrGraph->edges[ptrGraph->edgesSize + 1] = newEdge;
            ptrGraph->edgesSize++;
        }
    }
}

void
displayGraph(Graph graph)
{
    printf("%s = (V, E)\n", graph.name);
    
    printf("V = (");
    for (int i = 0; i < graph.verticesSize; i++) {
        if (i != graph.verticesSize - 1)
            printf("%s, ", graph.vertices[i].name);
        else 
            printf("%s)\n", graph.vertices[i].name);
    }

    printf("E = {\n");
    for (int i = 0; i < graph.edgesSize; i++) {
        printf("(%s, %s, %d),\n", 
            graph.edges[i].initial->name,
            graph.edges[i].terminal->name,
            graph.edges[i].weight);
    }

    printf("}\n");


}