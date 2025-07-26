// Include other standard libraries here
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "graph.h"
#include "traversal.h"

/**
 * Initializes a boolean array by setting all elements to false.
 *
 * @param array the boolean array to initialize
 * @param size the number of elements in the array
 */
void
initValues(bool array[], int size)
{
    int i;

    for (i = 0; i < size; i++)
        array[i] = false;
}

/**
 * Performs a Breadth-First Search (BFS) traversal starting from a given vertex
 * and returns the order of visited vertices in a queue. 
 *
 * @param graph pointer to the graph structure
 * @param start the starting vertex for the traversal
 * @return a queue containing vertices in BFS order
 */
Queue
BFS(Graph* graph, char* start) 
{
    int numVertices = graph->numVertices;
    int vertexIdx = getVertexIdx(graph, start);
    Queue vertexQueue, bfsOrder;
    EdgeNode *curEdgeNode;
    Vertex curVertex, *adjVertex;
    bool isVisited[numVertices];

    // Initialize
    clearQueue(&vertexQueue);
    clearQueue(&bfsOrder);
    initValues(isVisited, numVertices);
    
    // Enqueue start vertex 
    enqueue(&vertexQueue, graph->vertexList[vertexIdx]);
    isVisited[vertexIdx] = true;

    // Traverse through all vertices until the queue is empty
    while (!isEmptyQueue(&vertexQueue)) {
        // Move a vertex from the queue to the BFS order
        curVertex = dequeue(&vertexQueue);
        enqueue(&bfsOrder, curVertex);

        // Get the first lexicographically adjacent vertex
        curEdgeNode = curVertex.edgeListHead;

        // Go through all adjacent vertices
        while (curEdgeNode != NULL) {
            adjVertex = curEdgeNode->adjVertex;
            vertexIdx = getVertexIdx(graph, adjVertex->vertex);

            // Enqueue the unvisited adjacent vertex
            if (!isVisited[vertexIdx]) {
                isVisited[vertexIdx] = true;
                enqueue(&vertexQueue, *adjVertex);
            }

            // Move to the next adjacent node
            curEdgeNode = curEdgeNode->next;
        }
    }

    // Return the BFS order stored through a queue
    return bfsOrder;
}

/**
 * Performs a Depth-First Search (DFS) traversal starting from a given vertex
 * and returns the order of visited vertices in a queue. 
 *
 * @param graph pointer to the graph structure
 * @param start the starting vertex for the traversal
 * @return a queue containing vertices in DFS order
 */
Queue
DFS(Graph* graph, char* start) 
{
    int numVertices = graph->numVertices;
    int vertexIdx = getVertexIdx(graph, start);
    Stack vertexStack;
    Queue dfsOrder;
    EdgeNode *curEdgeNode;
    Vertex curVertex, *adjVertex;
    bool isVisited[numVertices];
    bool hasSuccessor;

    // Initialize
    clearStack(&vertexStack);
    clearQueue(&dfsOrder);
    initValues(isVisited, numVertices);
    
    // Push start vertex
    pushStack(&vertexStack, graph->vertexList[vertexIdx]);
    isVisited[vertexIdx] = true;
    enqueue(&dfsOrder, graph->vertexList[vertexIdx]);

    // Traverse through all vertices until the stack is empty
    while (!isEmptyStack(&vertexStack)) {

        curVertex = peekStack(&vertexStack);
        curEdgeNode = curVertex.edgeListHead;

        hasSuccessor = false;

        // Go through each adjacent vertex until an unvisited one is found
        while (curEdgeNode != NULL && !hasSuccessor) {
            adjVertex = curEdgeNode->adjVertex;
            vertexIdx = getVertexIdx(graph, adjVertex->vertex);

            // Push and enqueue unvisited vertex
            if (!isVisited[vertexIdx]) {
                isVisited[vertexIdx] = true;
                pushStack(&vertexStack, *adjVertex);
                enqueue(&dfsOrder, *adjVertex);

                hasSuccessor = true;
            }
            // Move to the next adjacent node
            curEdgeNode = curEdgeNode->next;
        }

        if (!hasSuccessor) {
            popStack(&vertexStack);
        }
    }

    return dfsOrder;
}
/*
This function computes the bfs order and bfs tree of a graph starting at a 
specific vertex.

Parameters:

G     : a graph (V,E) where V is the set of vertices and E is the set of edges
start : a vertex in V

Returns the bfs order and/or the bfs tree

function bfs(G,start) {
   // initialize queue for exploration frontier 
   Q = CreateQueue()

   // add start node to queue 
   enqueue(Q,start)

   // initialize the bfs order and tree 
   bfs_order = {}

   // all vertices V in the original graph are in the bfs tree but the 
   // edges are initially empty                                        
   bfs_tree = (V,E = {})

   // track the source or "parent" of each vertex 
   set source(v) = NULL for all v in V

   while not QueueEmpty(Q) {
       cur_node = dequeue(Q)
       add cur_node to end of bfs_order

       // if not root/initial node 
       if source(cur_node) is not NULL {
           add (cur_node,source(cur_node)) to bfs_tree.E
       }

       for all vertices v that are adjacent to cur_node in lexicographical 
           order {

           // if not explored yet 
          if v not in bfs_order and v not in Q {
              enqueue(Q,v)

              // cur_node is now the source or "parent" of v 
              set source(v) to cur_node
          }
       }
   }

   return bfs_order and/or bfs_tree
}


This function computes the dfs order and dfs tree of a graph starting at a 
specific vertex.

Parameters:

G     : a graph (V,E) where V is the set of vertices and E is the set of edges
start : a vertex in V

Returns the dfs order and/or the dfs tree

function dfs(G,start) {
   // initialize queue for exploration frontier 
   S = CreateStack()

   // add start node to queue 
   push(S,start)

   // initialize the dfs order and tree 
   dfs_order = {start}

   // all vertices V in the original graph are in the dfs tree but the 
   // edges are initially empty                                        
   dfs_tree = (V,E = {})

   while not StackEmpty(Q) {
       cur_node = top(Q)

       has_successor = false

       for all vertices v that are adjacent to cur_node in lexicographical 
           order {

           // if not explored yet 
          if v not in dfs_order and v not in S {
              push(S,v)

              add v to dfs_order

              // cur_node is now the source or "parent" of v 
              add (cur_node,v) to dfs_tree.E

              has_successor = true
          }
       }

       // if dead end 
       if not has_successor {
           pop(Q)
       }
   }

   return dfs_order and/or dfs_tree
}
*/