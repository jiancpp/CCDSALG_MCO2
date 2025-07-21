#include <stdio.h>
#include <stdbool.h>

#include "traversal.h"
#include "graph.h"

int main()
{
    Graph graph = createGraph();

    addVertex(&graph, "Pikachu");
    addVertex(&graph, "Charmander");
    addVertex(&graph, "Eevee");
    addVertex(&graph, "Mew");
    addVertex(&graph, "Pichu");

    addEdge(&graph, "Pikachu", "Mew", 5);
    addEdge(&graph, "Charmander", "Pikachu", 5);
    addEdge(&graph, "Charmander", "Pichu", 5);
    //addEdge(&graph, "Eevee", "Pichu", 5);
    addEdge(&graph, "Eevee", "Charmander", 5);
    addEdge(&graph, "Charmander", "Mew", 5);

    printf("deg(Pikachu) 2 = %d\n\n", getDegree(graph, "Pikachu"));
    printf("deg(Charmander) 3 = %d\n\n", getDegree(graph, "Charmander"));
    printf("deg(Pichu) 2 = %d\n\n", getDegree(graph, "Pichu"));
    printf("deg(Eevee) 2 = %d\n\n", getDegree(graph, "Eevee"));
    printf("deg(Mew) 1 = %d\n\n", getDegree(graph, "Mew"));
    
    printGraph(&graph);
    printf("\n\n");

    EdgeNode* temp = graph.vertexList[0].edgeListHead;

    for (int i = 0; temp != NULL; i++) {
        printf("%s--%s\n", graph.vertexList[0].vertex, temp->adjVertex->vertex);
        temp = temp->next;
    }

    Queue bfs = BFS(&graph, "Charmander");
    printf("\n\n");

    printf("BFS\n");
    while (!isEmptyQueue(&bfs)) {
        printf("%s\n", dequeue(&bfs).vertex);
    }

    printf("\n\n");
    printf("Path Check\n");
    printf("Charmander-Pichu: %d\n", checkPath(&graph, "Charmander", "Pichu"));
}