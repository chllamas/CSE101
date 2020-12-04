/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA4
* Graph.h
* Header file for Graph ADT
*******************************************************************************/
#include "List.h"
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define NIL -1
#define UNDEF -2

// Exported types -------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n);          // Creates and returns a new Graph with n
                                // vertices and no edges
void freeGraph(Graph* pG);      // Frees all heap memory associated with *pG, and
                                // sets *pG to NULL

// Access functions -----------------------------------------------------------
int getOrder(Graph G);          // returns order of Graph G
int getSize(Graph G);           // returns size of Graph G
int getParent(Graph G, int u);  // returns parent of vertex u in DFS
                                // PRE: 1<=u<=n<=getOrder(G)
int getDiscover(Graph G, int u);// returns discover of vertex u in DFS
                                // PRE: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);  // returns finish of vertex u in DFS
                                // PRE: 1<=u<=n=getOrder(G)


// Manipulation procedures ----------------------------------------------------
void addEdge(Graph G, int u, int v);    // inserts a new edge joining u to v
                                        // i.e. u is added to adjacency List of v,
                                        // and vice versa
                                        // PRE: 1<=u&&v<=getOrder(G)
void addArc(Graph G, int u, int v);     // inserts new directed edge from u to v
                                        // PRE: 1<=u&&v<=getOrder(G)
void DFS(Graph G, List S);  // Performs DFS on Graph G
                            // PRE: length(S)==getOrder(G)


// Other operations -----------------------------------------------------------
Graph transpose(Graph G);  // returns a reference to a Graph representing the
                           // transpose of G
Graph copyGraph(Graph G);  // returns a reference to a Graph that is a copy of G
void printGraph(FILE* out, Graph G);    // prints adjacency list representation
                                        // of G to the file pointed by out

#endif
