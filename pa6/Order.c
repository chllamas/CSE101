/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA6
* Order.c
* Client that outputs preorder, inorder, and postorder variations of Dictionary
* from input given to output addressed
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"

#define MAX_LEN 255

int main(int argc, char* argv[]){
        int i, j, n;
        char ch;
        int arr[] = {1};
        Dictionary D;
        FILE *in, *out;

        // check for correct number of arguments
        if(argc!=3){
                fprintf(stderr, "USAGE: Order <input file> <output file>\n");
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
        while((ch=getc(in))!=EOF){
                if(ch=='\n') n++;
        }
        rewind(in); // rewind to reread entire file

        // read each line and place into file
        D = newDictionary(0);
        char* str[n];
        for(i = 0; i<n; i++){
                str[i] = (char*)calloc(MAX_LEN+1, sizeof(char));
                fgets(str[i], MAX_LEN, in);
                for(j=0; j<=MAX_LEN; j++){
                        if(str[i][j]=='\n'){
                                str[i][j] = '\0';
                                break;
                        }
                }
                insert(D, str[i], arr);
        }

        // print dictionary in Pre-Order
        fprintf(out, "******************************************************\n"\
                "PRE-ORDER:\n"\
                "******************************************************\n");
        printDictionary(out, D, "pre");
        fprintf(out, "\n\n");

        // print dictionary in In-Order
        fprintf(out, "******************************************************\n"\
                "IN-ORDER:\n"\
                "******************************************************\n");
        printDictionary(out, D, "in");
        fprintf(out, "\n\n");

        // print dictionary in Post-Order
        fprintf(out, "******************************************************\n"\
                "POST-ORDER:\n"\
                "******************************************************\n");
        printDictionary(out, D, "post");

        // free everything, program is finished
        freeDictionary(&D);
        for(i=0; i<n; i++){
                free(str[i]);
        }
        fclose(in);
        fclose(out);

        return 0;
}
