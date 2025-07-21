// Include other standard libraries here
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"
#include "MST.h"

Graph
createMST(Graph* graph)
{
    Graph graphMST = createGraph();
    // Code here

    return graphMST;
}

int
totalEdgeWeight(Graph* graph)
{
    int sum = 0;
    // Code here

    return sum;
} 

void
printMST(Graph* graph) 
{
    printf("MST(G) = (V, E)\n");

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
    printf("}\n");
    
    printf("Total Edge Weight: %d\n", totalEdgeWeight(graph));
}