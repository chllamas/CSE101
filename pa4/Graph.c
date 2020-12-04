/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA3
* Graph.c
* Implementation file for Graph ADT
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

static int time;

// private GraphObj type
typedef struct GraphObj{
        int order;      // # of vertices
        int size;       // # of edges
        List* adj;      // ith element contains the adjs of vertex i
        int* color;     // ith element is the color (white, gray, black) of vertex i
                        // or (0,-1,1) respectively
        int* parent;    // ith element is the parent of vertex i
        int* discover;  // ith elemnt is discover time of vertex i
        int* finish;    // ith element is finish time of vertex i
} GraphObj;

// Private Functions ----------------------------------------------------------
// addDescending()
// adds int x to List L, in decreasing finish time of the vertex that x represents
void addDescending(Graph G, List L, int x){
        if(G==NULL){
                printf("Graph Error: calling addDescending() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }
        if(L==NULL){
                printf("List Error: calling addDescending() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }

        moveFront(L);
        while(index(L)!=-1){
                if(G->finish[get(L)] < G->finish[x]){
                        break;
                }else{
                        moveNext(L);
                }
        }
        if(index(L)==-1){
                append(L, x);
        }else{
                insertBefore(L, x);
        }
}

// addOrdered()
// adds int x to List L, keeping L in order from lowest to highest, front to
// back, allowing duplicates
void addOrdered(List L, int x){
        if(L==NULL){
                printf("List Error: calling addOrdered() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }

        moveFront(L);
        while(index(L)!=-1){
                if(get(L)==x){
                        break; // allow duplicates, end this function
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

// Visit()
// helper funcion for DFS()
void Visit(Graph G, int x){
        if(G==NULL){
                printf("Graph Error: calling Visit() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        int y;
        G->discover[x] = (++time);
        G->color[x] = -1;
        moveFront(G->adj[x]);
        while(index(G->adj[x])!=-1){
                y = get(G->adj[x]);
                if(G->color[y]==0){
                        G->parent[y] = x;
                        Visit(G, y);
                }
                moveNext(G->adj[x]);
        }
        G->color[x] = 1;
        G->finish[x] = (++time);
}

// Constructors-Destructors ---------------------------------------------------
// newGraph()
// Creates and returns a new Graph with n vertices and no edges
Graph newGraph(int n){
        int i;
        Graph G = (Graph)malloc(sizeof(GraphObj));
        G->order = n;
        G->size = 0;
        G->adj = (List*)calloc(n+1, sizeof(List));
        G->color = (int*)calloc(n+1, sizeof(int));
        G->parent = (int*)calloc(n+1, sizeof(int));
        G->discover = (int*)calloc(n+1, sizeof(int));
        G->finish = (int*)calloc(n+1, sizeof(int));

        // initialize all values
        for(i=1; i<=n; i++){
                G->adj[i] = newList();
                G->parent[i] = NIL;
                G->discover[i] = UNDEF;
                G->finish[i] = UNDEF;
        }
        return G;
}

// freeGraph()
// Frees all heap memory associated with *pG, and sets *pG to NULL
void freeGraph(Graph* pG){
        int i;
        if(*pG!=NULL && pG!=NULL){
                for(i=1; i<=getOrder(*pG); i++){
                        freeList(&((*pG)->adj[i]));
                }
                free((*pG)->parent);
                free((*pG)->discover);
                free((*pG)->finish);
                free((*pG)->color);
                free((*pG)->adj);
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

// getParent()
// returns parent of vertex u in DFS
int getParent(Graph G, int u){
        if(G==NULL){
                printf("Graph Error: calling getParent() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        // PRE: 1<=u<=getOrder(G)
        if(u>=1 && u<=getOrder(G)){
                if(G->parent[u]<1 || G->parent[u]>getOrder(G)){
                        return NIL;
                }
                return G->parent[u];
        }
        return NIL;
}

// getDiscover()
// returns discover of vertex u in DFS
int getDiscover(Graph G, int u){
        if(G==NULL){
                printf("Graph Error: calling getDiscover() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        // PRE: 1<=u<=n=getOrder(G)
        if(u>=1 && u<=getOrder(G)){
                return G->discover[u];
        }
        return 0;
}

// getFinish()
// returns finish of vertex u in DFS
int getFinish(Graph G, int u){
        if(G==NULL){
                printf("Graph Error: calling getFinish() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        // PRE: 1<=u<=n=getOrder(G)
        if(u>=1 && u<=getOrder(G)){
                return G->finish[u];
        }
        return 0;
}
// Manipulation procedures ----------------------------------------------------
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
                addOrdered(G->adj[u], v);
                addOrdered(G->adj[v], u);
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
                addOrdered(G->adj[u], v);
                G->size++;
        }
}

// DFS()
// Performs DFS on Graph G
void DFS(Graph G, List S){
        if(G==NULL){
                printf("Graph Error: calling DFS() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }
        if(S==NULL){
                printf("List Error: calling DFS() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }

        int x;
        // PRE: length(S)==getOrder(G)
        if(length(S)==getOrder(G)){
                for(x=1; x<=getOrder(G); x++){
                        G->color[x] = 0;
                        G->parent[x] = NIL;
                }
                time = 0;
                moveFront(S);
                while(index(S)!=-1){
                        if(G->color[get(S)] == 0){
                                Visit(G, get(S));
                        }
                        moveNext(S);
                }
                // order S by descending finish times
                clear(S);
                for(x=1; x<=getOrder(G); x++){
                        addDescending(G, S, x);
                }
        }
}
// Other operations -----------------------------------------------------------
// transpose()
// returns a reference to a Graph representing the transpose of G
Graph transpose(Graph G){
        if(G==NULL){
                printf("Graph Error: calling transpose() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        int i;
        Graph C = copyGraph(G);
        // clear all lists
        for(i=1; i<=getOrder(C); i++){
                clear(C->adj[i]);
        }
        // move all points from G
        for(i=1; i<=getOrder(G); i++){
                moveFront(G->adj[i]);
                while(index(G->adj[i])!=-1){
                        addOrdered(C->adj[get(G->adj[i])], i);
                        moveNext(G->adj[i]);
                }
        }
        return C;
}

// copyGraph()
// returns a reference to a Graph that is a copy of G
Graph copyGraph(Graph G){
        if(G==NULL){
                printf("Graph Error: calling copyGraph() on "\
                        "NULL Graph reference\n");
                exit(EXIT_FAILURE);
        }

        int i;
        Graph C = newGraph(getOrder(G));
        for(i=1; i<=getOrder(G); i++){
                moveFront(G->adj[i]);
                while(index(G->adj[i])!=-1){
                        append(C->adj[i], get(G->adj[i]));
                        moveNext(G->adj[i]);
                }
                //C->color[i] = G->color[i];
                //C->parent[i] = G->parent[i];
                //C->discover[i] = G->discover[i];
                //C->finish[i] = G->finish[i];
        }
        return C;
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
                moveFront(G->adj[x]);
                while(index(G->adj[x])!=-1){
                        fprintf(out, "%d ", get(G->adj[x]));
                        moveNext(G->adj[x]);
                }
                fprintf(out, "\n");
        }
}
