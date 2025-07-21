// Include other standard libraries here
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "traversal.h"

void
initValues(bool array[], int size)
{
    int i;

    for (i = 0; i < size; i++)
        array[i] = false;
}

Queue
BFS(Graph graph, char* start) 
{
    int numVertices = graph.numVertices;
    int vertexIdx = getVertexIdx(&graph, start);
    Queue vertexQueue, bfsOrder;
    EdgeNode *curEdgeNode;
    Vertex curVertex, *adjVertex;
    bool isVisited[numVertices];

    // Initialize
    clearQueue(&vertexQueue);
    clearQueue(&bfsOrder);
    initValues(isVisited, numVertices);
    
    // add start vertex
    enqueue(&vertexQueue, graph.vertexList[vertexIdx]);
    isVisited[vertexIdx] = true;

    while (!isEmptyQueue(&vertexQueue)) {
        curVertex = dequeue(&vertexQueue);
        enqueue(&bfsOrder, curVertex);
        curEdgeNode = curVertex.edgeListHead;

        while (curEdgeNode != NULL) {
            adjVertex = curEdgeNode->adjVertex;
            vertexIdx = getVertexIdx(&graph, adjVertex->vertex);

            if (!isVisited[vertexIdx]) {
                isVisited[vertexIdx] = true;
                enqueue(&vertexQueue, *adjVertex);
            }

            curEdgeNode = curEdgeNode->next;
        }
    }

    return bfsOrder;
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

/*
Getting MST
- Connecting everything with everything else with Minimum weight

Sort edges by weight before doing prim's algo

while no. of edges is less than n minus one

union find disjoint set for crosscalsssssss cycle checking
*/