/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA4
* FindComponents.c
* Finds components in the graph given by input file to the output file
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
        Graph G, T;
        List L, S;
        FILE *in, *out;
        int i, n, x, y;

        // make sure there are three arguments only
        if(argc!=3){
                fprintf(stderr, "USAGE: FindComponents input_file output_file\n");
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
        G = newGraph(n);

        // create arcs
        while(1){
                fscanf(in, "%d %d", &x, &y);
                if(x==0 && y==0){ // dummy line given
                        break;
                }
                if(x>n || y>n){ // out of range
                        fprintf(stderr, "Int given greater than n\n");
                        exit(EXIT_FAILURE);
                }
                addArc(G, x, y);
        }

        // print adjacency list representation of G
        fprintf(out, "Adjacency list representation of G:\n");
        printGraph(out, G);

        // fill S with the vertices
        S = newList();
        for(i = 1; i<=n; i++) append(S, i);

        // run DFS on G with S
        DFS(G, S);

        // run DFS on Gt with the new S
        T = transpose(G);
        DFS(T, S);

        // get # of strongly connected components of G
        n = 0;
        for(i=1; i<=getOrder(T); i++){
                if(getParent(T, i)<=0){
                        n++;
                }
        }

        // print the components
        // to find the strongly-connected-components, use S as a stack
        // back of List S will be popped, if vertex popped has a NIL parent, then
        // end the while loop and continue to new component
        L = newList();
        fprintf(out, "\nG contains %d strongly connected components:\n", n);
        for(i=1; i<=n; i++){
                clear(L);
                while(length(S)>0){
                        x = back(S);
                        deleteBack(S); // pop from back
                        prepend(L, x); // add to list
                        if(getParent(T, x)==NIL){
                                break; // if the vertex has NIL parent, continue to new component
                        }
                }
                fprintf(out, "Component %d: ", i);
                printList(out, L);
                fprintf(out, "\n");
        }

        fclose(in);
        fclose(out);

        freeGraph(&G);
        freeGraph(&T);
        freeList(&L);
        freeList(&S);

        return 0;
}
