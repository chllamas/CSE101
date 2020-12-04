/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA3
* GraphTest.c
* Test client for Graph ADT
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(){
        FILE* out;
        Graph G  = newGraph(10);
        List L = newList();

        // open output file for writing
        if((out=fopen("GraphTest_Output", "w"))==NULL){
                fprintf(stderr, "Could not open file GraphTest_output "\
                                "for writing\n");
                exit(EXIT_FAILURE);
        }

        // create some directed paths between elements
        addEdge(G, 1, 6);
        addEdge(G, 1, 2);
        addEdge(G, 2, 6);
        addEdge(G, 2, 8);
        addEdge(G, 3, 8);
        addEdge(G, 3, 10);
        addEdge(G, 4, 9);
        addEdge(G, 5, 9);
        addEdge(G, 5, 10);
        addEdge(G, 7, 8);
        addEdge(G, 8, 9);

        // print out size to file
        fprintf(out, "================\nGraph #1\nUndirect\n================\n");
        printGraph(out, G);
        fprintf(out, "Order = %d\nSize = %d\n", getOrder(G), getSize(G));

        // run BFS with source 7
        BFS(G, 7);
        fprintf(out, "--\nBFS with source %d\n", getSource(G));

        // print short routes
        getPath(L, G, 10);
        fprintf(out, "Shortest route from source to 10 is: ");
        printList(out, L);
        fprintf(out, "\n");
        fprintf(out, "The distance is %d\n", getDist(G, 10));

        // run BFS with source 7
        clear(L);
        BFS(G, 4);
        fprintf(out, "--\nBFS with source %d\n", getSource(G));

        // print short routes
        getPath(L, G, 1);
        fprintf(out, "Shortest route from source to 1 is: ");
        printList(out, L);
        fprintf(out, "\n");
        fprintf(out, "The distance is %d\n", getDist(G, 1));

        makeNull(G);
        clear(L);

        // make a direct graph
        addArc(G, 1, 6);
        addArc(G, 2, 7);
        addArc(G, 3, 2);
        addArc(G, 4, 3);
        addArc(G, 4, 1);
        addArc(G, 5, 4);
        addArc(G, 6, 7);
        addArc(G, 7, 8);
        addArc(G, 8, 9);
        addArc(G, 9, 10);
        addArc(G, 9, 3);
        addArc(G, 10, 5);

        // print out size to file
        fprintf(out, "\n================\nGraph #2\nDirect\n================\n");
        printGraph(out, G);
        fprintf(out, "Order = %d\nSize = %d\n", getOrder(G), getSize(G));

        // run BFS with source 6
        BFS(G, 6);
        fprintf(out, "--\nBFS with source %d\n", getSource(G));

        // print short routes
        getPath(L, G, 1);
        fprintf(out, "Shortest route from source to 1 is: ");
        printList(out, L);
        fprintf(out, "\n");
        fprintf(out, "The distance is %d\n", getDist(G, 1));

        // run BFS with source 2
        clear(L);
        BFS(G, 2);
        fprintf(out, "--\nBFS with source %d\n", getSource(G));

        // print short routes
        getPath(L, G, 3);
        fprintf(out, "Shortest route from source to 3 is: ");
        printList(out, L);
        fprintf(out, "\n");
        fprintf(out, "The distance is %d\n", getDist(G, 3));

        // end program
        fclose(out);
        freeGraph(&G);
        freeList(&L);
}
