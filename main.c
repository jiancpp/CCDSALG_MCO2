#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"

void
tokenizeInput(String256 input, String256 tokens[])
{
    int i = 0;
    char* token;

    token = strtok(input, " \n");

    while (token != NULL && i < MAX_TOKENS) {
        strcpy(tokens[i++], token);
        token = strtok(NULL, " \n");
    }
}

void
clearTokens(String256 tokens[]) 
{
    int i;
    for (i = 0; i < MAX_TOKENS; i++)
        strcpy(tokens[i], "\0");
}

int main() 
{
    String256 input;
    String256 tokens[MAX_TOKENS];
    Queue traversal, path;
    Graph graph = createGraph();
    Graph graphMST = createGraph();

    while (fgets(input, sizeof(input), stdin) != NULL 
           && strcmp(input, "11\n") != 0) {
        
        // Initialize
        clearQueue(&traversal);
        clearTokens(tokens);

        tokenizeInput(input, tokens);

        // Execute inputted command
        switch (atoi(tokens[0])) {
            case 1:
                addVertex(&graph, tokens[1]);
                break;
            case 2:
                addEdge(&graph, tokens[1], tokens[2], atoi(tokens[3]));
                break;
            case 3:
                printf("%d\n", getDegree(graph, tokens[1]));
                break;
            case 4:
                printf("%d\n", edgeExists(&graph, tokens[1], tokens[2]));
                break;
            case 5:
                traversal = BFS(&graph, tokens[1]);
                while (!isEmptyQueue(&traversal)) {
                    printf("%s\n", dequeue(&traversal).vertex);
                }
                break;
            case 6:
                // traversal = DFS(&graph, tokens[1]);
                // while (!isEmptyQueue(&traversal)) {
                //     printf("%s\n", dequeue(&traversal).vertex);
                // }
                break;
            case 7:
                printf("%d\n", checkPath(&graph, tokens[1], tokens[2]));
                break;
            case 8:
                graphMST = createMST(&graph);
                printMST(&graphMST);
                break;
            case 9:
                path = createShortestPath(&graph, tokens[1], tokens[2]);
                printShortestPath(path);
                break;
            case 10:
                printGraph(&graph);
                break;
            default:
                break;
        }
    }

    return 0;
}