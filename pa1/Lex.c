/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA1
* Lex.c
* Main client using List ADT
*******************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define MAX_LEN 255
#define INDEXFUNC index

int main(int argc, char* argv[]){
        int i, n, comparison;
        char ch;
        char** string_array;
        List L;
        FILE *in, *out;

        // check for correct number of arguments
        if(argc!=3){
                fprintf(stderr, "USAGE: Lex <input file> <output file>\n");
                exit(EXIT_FAILURE);
        }

        // open input file for reading
        if((in=fopen(argv[1], "r"))==NULL){
                fprintf(stderr, "Unable to open file %s for reading.\n", argv[1]);
                exit(EXIT_FAILURE);
        }

        // open output file for writing
        if((out=fopen(argv[2], "w"))==NULL){
                fprintf(stderr, "Unable to open file %s for writing.\n", argv[2]);
                exit(EXIT_FAILURE);
        }

        // get number of lines in the input file and set that to n
        n = 0;
        ch = getc(in);
        while(ch!=EOF){
                if(ch=='\n'){
                        n++;
                }
                ch = getc(in);
        }

        string_array = (char**)calloc(n, sizeof(char*)); // dynamically allocated array of size n

        // read each line of the file and place into string_array
        rewind(in);
        for(i = 0; i<n; i++){
                string_array[i] = (char*)malloc(MAX_LEN+1); // allocated a string of size MAX_LEN + 1 for NULL character
                fgets(string_array[i], MAX_LEN, in);
        }

        // algorithm to correctly index the array into a new List
        L = newList();
        prepend(L, 0);
        moveFront(L);
        for(i = 1; i<n; i++){
                moveFront(L);
                comparison = strcmp(string_array[get(L)], string_array[i]);
                if(comparison > 0){
                        insertBefore(L, i);
                }else{
                        while(INDEXFUNC(L)!=-1 && strcmp(string_array[get(L)], string_array[i])<0){
                                moveNext(L);
                        }
                        if(INDEXFUNC(L)==-1){
                                moveBack(L);
                        }
                        comparison = strcmp(string_array[get(L)], string_array[i]);
                        if(comparison > 0){
                                insertBefore(L, i);
                        }else{
                                insertAfter(L, i);
                        }
                }
        }

        // print each element of array by order of indices in List
        moveFront(L);
        while(INDEXFUNC(L)!=-1){
                fprintf(out, "%s", string_array[get(L)]);
                moveNext(L);
        }

	freeList(&L);
        fclose(in);
        fclose(out);

        return 0;
}
