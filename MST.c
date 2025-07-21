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
    printf("MST");
    printGraph(graph);
    printf("Total Edge Weight: %d\n", totalEdgeWeight(graph));
}