/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA3
* Graph.h
* Header file for Graph ADT
*******************************************************************************/
#include "List.h"
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define INF -1
#define NIL -2

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
int getSource(Graph G);         // returns source vertex most recently used, or
                                // NIL if BFS() has not yet been called
int getParent(Graph G, int u);  // returns parent of vertex u in Breadth-First
                                // tree created by BFS(), or NIL if BFS() has
                                // not yet been called
                                // PRE: 1<=u<=getOrder(G)
int getDist(Graph G, int u);    // returns distance from most recent BFS source
                                // to vertex u, or INF if BFS() has not yet
                                // been called
                                // PRE: 1<=u<=getOrder(G)
void getPath(List L, Graph G, int u);   // appends to List L vertices of shortest
                                        // path in G from source to u or appends
                                        // to L the value NIL if no such path
                                        // exists
                                        // PRE: getSource(G)!=NIL
                                        // PRE: 1<=u<=getOrder(G)

// Manipulation procedures ----------------------------------------------------
void makeNull(Graph G); // deletes all edges of G, restoring to original (no edge)
                        // state
void addEdge(Graph G, int u, int v);    // inserts a new edge joining u to v
                                        // i.e. u is added to adjacency List of v,
                                        // and vice versa
                                        // PRE: 1<=u&&v<=getOrder(G)
void addArc(Graph G, int u, int v);     // inserts new directed edge from u to v
                                        // PRE: 1<=u&&v<=getOrder(G)
void BFS(Graph G, int s);// BFS algorithm on G with source s, setting color,
                         // distance, parent, and source fields of G accordingly


// Other operations -----------------------------------------------------------
void printGraph(FILE* out, Graph G);    // prints adjacency list representation
                                        // of G to the file pointed by out

#endif
