/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA3
* Graph.c
* Implementation file for Graph ADT
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// private GraphObj type
typedef struct GraphObj{
        int order;      // # of vertices
        int size;       // # of edges
        int source;     // vertex recently used as source for BFS; 0 if not performed
        List* neighbor; // ith element contains the neighbors of vertex i
        int* color;     // ith element is the color (white, gray, black) of vertex i
                        // or (0,-1,1) respectively
        int* parent;    // ith element is the parent of vertex i
        int* distance;  // ith element is the distance from the (most recent)
                        // source to vertex i
} GraphObj;

// Private Functions ----------------------------------------------------------
// addOrdered()
// adds int x to List L, keeping L in order from lowest to highest, front to
// back, unallowing duplicates from happening
void addOrdered(List L, int x){
        if(L==NULL){
                printf("List Error: calling addOrdered() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }

        moveFront(L);
        while(index(L)!=-1){
                if(get(L)==x){
                        return; // don't allow duplicates, end this function
                }else if(get(L)>x){
                        break;
                }
                moveNext(L);
        }
        if(index(L)!=-1){
                insertBefore(L, x);
        }else{
                append(L, x);
        }
}

// Constructors-Destructors ---------------------------------------------------
// newGraph()
// Creates and returns a new Graph with n vertices and no edges
Graph newGraph(int n){
        int i;
        Graph G = (Graph)malloc(sizeof(GraphObj));
        G->order = n;
        G->size = 0;
        G->source = NIL;
        G->neighbor = (List*)calloc(n+1, sizeof(List));
        G->color = (int*)calloc(n+1, sizeof(int));
        G->parent = (int*)calloc(n+1, sizeof(int));
        G->distance = (int*)calloc(n+1, sizeof(int));

        // initialize all values
        for(i=1; i<=n; i++){
                G->neighbor[i] = newList();
        }
        return G;
}

// freeGraph()
// Frees all heap memory associated with *pG, and sets *pG to NULL
void freeGraph(Graph* pG){
        int i;
        if(*pG!=NULL && pG!=NULL){
                for(i=1; i<=getOrder(*pG); i++){
                        freeList(&((*pG)->neighbor[i]));
                }
                free((*pG)->distance);
                free((*pG)->parent);
                free((*pG)->color);
                free((*pG)->neighbor);
                free(*pG);
        }
}

// Access functions -----------------------------------------------------------
// getOrder()
// returns order of Graph G
int getOrder(Graph G){
        if(G==NULL){
                printf("Graph Error: calling getOrder() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }
        return G->order;
}

// getSize()
// returns size of Graph G
int getSize(Graph G){
        if(G==NULL){
                printf("Graph Error: calling getSize() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }
        return G->size;
}

// getSource()
// returns source vertex most recently used, or NIL if BFS() has not yet been
// called
int getSource(Graph G){
        if(G==NULL){
                printf("Graph Error: calling getSource() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }
        return G->source;
}

// getParent()
// returns parent of vertex u in Breadth-First tree created by BFS(), or NIL if
// BFS() has not yet been called
int getParent(Graph G, int u){
        if(G==NULL){
                printf("Graph Error: calling getParent() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        // PRE: 1<=u<=getOrder(G)
        if(u>=1 && u<=getOrder(G)){
                if(getSource(G)==NIL){
                        return NIL;
                }
                return G->parent[u];
        }
        return NIL;
}

// getDist()
// returns distance from most recent BFS source to vertex u, or INF if BFS()
// has not yet been called
int getDist(Graph G, int u){
        if(G==NULL){
                printf("Graph Error: calling getDist() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        // PRE: 1<=u<=getOrder(G)
        if(u>=1 && u<=getOrder(G)){
                if(getSource(G)==NIL){
                        return INF;
                }
                return G->distance[u];
        }
        return INF;
}

// getPath()
// appends to List L vertices of shortest path in G from source to u or appends
// to L the value NIL if no such path exists
void getPath(List L, Graph G, int u){
        if(G==NULL){
                printf("Graph Error: calling getPath() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }
        if(L==NULL){
                printf("List Error: calling getPath() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }

        // PRE: getSource(G)!=NIL and 1<=u<=getOrder(G) and distance not infinite
        if(u>=1 && u<=getOrder(G) && getSource(G)!=NIL && getDist(G, u)!=INF){
                if(u==getSource(G)){
                        append(L, getSource(G));
                }else{
                        getPath(L, G, getParent(G, u));
                        append(L, u);
                }
        }else{
                append(L, NIL);
        }
}

// Manipulation procedures ----------------------------------------------------
// makeNull()
// deletes all edges of G, restoring to original (no edge) state
void makeNull(Graph G){
        if(G==NULL){
                printf("Graph Error: calling makeNull() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }
        int i;
        G->size = 0;
        G->source = 0;
        for(i=1; i<=getOrder(G); i++){
                clear(G->neighbor[i]);
                G->color[i] = 0;
        }
}

// addEdge()
// inserts a new edge joining u to v i.e. u is added to adjacency List of v, and
// vice versa
void addEdge(Graph G, int u, int v){
        if(G==NULL){
                printf("Graph Error: calling addEdge() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        // PRE: 1<=u<=getOrder(G) and 1<=v<=getOrder(G)
        if(u>=1 && u<=getOrder(G) && v>=1 && v<=getOrder(G)){
                addOrdered(G->neighbor[u], v);
                addOrdered(G->neighbor[v], u);
                G->size++;
        }
}

// addArc()
// inserts new directed edge from u to v
void addArc(Graph G, int u, int v){
        if(G==NULL){
                printf("Graph Error: calling addArc() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        // PRE: 1<=u<=getOrder(G) and 1<=v<=getOrder(G)
        if(u>=1 && u<=getOrder(G) && v>=1 && v<=getOrder(G)){
                addOrdered(G->neighbor[u], v);
                G->size++;
        }
}

// BFS()
// BFS algorithm on G with source s, setting color, distance, parent, and source
// fields of G accordingly
void BFS(Graph G, int s){
        if(G==NULL){
                printf("Graph Error: calling addArc() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        int i, x, y;
        List L;

        // set everything else except s to default
        for(i=1; i<=getOrder(G); i++){
                if(i!=s){
                        G->color[i] = 0;
                        G->distance[i] = INF;
                        G->parent[i] = NIL;
                }
        }

        // discover s
        G->color[s] = -1;
        G->distance[s] = 0;
        G->parent[s] = NIL;

        // make a new List L with s in it
        L = newList();
        append(L, s);
        while(length(L)>0){
                x = front(L);
                deleteFront(L);
                moveFront(G->neighbor[x]);
                while(index(G->neighbor[x])!=-1){
                        y = get(G->neighbor[x]);
                        if(G->color[y] == 0){
                                G->color[y] = -1;
                                G->distance[y] = G->distance[x] + 1;
                                G->parent[y] = x;
                                append(L, y);
                        }
                        moveNext(G->neighbor[x]);
                }
                G->color[x] = 1;
        }
        freeList(&L);

        // BFS has been ran
        G->source = s;
}

// printGraph()
// prints adjacency list representation of G to file pointed by out
void printGraph(FILE* out, Graph G){
        if(G==NULL){
                printf("Graph Error: calling printGraph() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        int x;
        for(x=1; x<=getOrder(G); x++){
                fprintf(out, "%d: ", x);
                moveFront(G->neighbor[x]);
                while(index(G->neighbor[x])!=-1){
                        fprintf(out, "%d ", get(G->neighbor[x]));
                        moveNext(G->neighbor[x]);
                }
                fprintf(out, "\n");
        }
}
