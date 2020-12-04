/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA3
* FindPath.c
* Client using Graph ADT and List ADT
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
        FILE *in, *out;
        Graph G;
        List L;
        int n, x, y;

        // make sure there are three arguments only
        if(argc!=3){
                fprintf(stderr, "USAGE: FindPath input_file output_file\n");
                exit(EXIT_FAILURE);
        }

        // open file for reading
        if((in=fopen(argv[1], "r"))==NULL){
                fprintf(stderr, "Could not open file %s "\
                                "for reading\n", argv[1]);
                exit(EXIT_FAILURE);
        }

        // open file for writing
        if((out=fopen(argv[2], "w"))==NULL){
                fprintf(stderr, "Could not open file %s "\
                                "for writing\n", argv[2]);
                exit(EXIT_FAILURE);
        }

        // grab n from input file
        fscanf(in, "%d", &n);

        // create new graph of size n and a new empty list
        G = newGraph(n);
        L = newList();

        // create edges with first part
        while(1){
                fscanf(in, "%d %d", &x, &y);
                if(x==0 && y==0){ // dummy line given
                        break;
                }
                if(x>n || y>n){ // out of range
                        fprintf(stderr, "Int given greater than n\n");
                        exit(EXIT_FAILURE);
                }
                addEdge(G, x, y);
        }

        // print out the graph
        printGraph(out, G);
        fprintf(out, "\n");

        // run BFS with source-destination pairs
        while(1){
                fscanf(in, "%d %d", &x, &y);
                if(x==0 && y==0){ // dummy line given
                        break;
                }
                if(x>n || y>n){ // out of range
                        fprintf(stderr, "Int given greater than n\n");
                        exit(EXIT_FAILURE);
                }
                BFS(G, x);
                clear(L);
                getPath(L, G, y);
                fprintf(out, "The distance from %d to %d is ", x, y);
                if(getDist(G, y)==INF){
                        fprintf(out, "infinity\n");
                        fprintf(out, "No %d-%d path exists", x, y);
                }else{
                        fprintf(out, "%d\n", getDist(G, y));
                        fprintf(out, "A shortest %d-%d path is: ", x, y);
                        printList(out, L);
                }
                fprintf(out, "\n\n");
        }

        // end program
        fclose(in);
        fclose(out);
        freeGraph(&G);
        freeList(&L);
        return 0;
}
