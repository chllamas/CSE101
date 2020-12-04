/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA5
* Dictionary.c
* Test file for Dictionary ADT
*******************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){
        int i;
        Dictionary A, B;
        char* bank[] = {
                "orange", "unseen", "tomato", "mamma", "apples", "donut", "cheetos",
                "marvel", "doritos", "cod", "apricot", "joe", "aaa", "spider", "apple",
                "banana", "waffle"
        };

        A = newDictionary(1);
        B = newDictionary(0);

        for(i=0; i<17; i++) insert(A, bank[i], i);
        for(i=0; i<17; i++) insert(B, bank[i], i);

        printf("--\nList A (Size %d):\n", size(A));
        printDictionary(stdout, A);

        printf("--\nList B (Size %d):\n", size(B));
        printDictionary(stdout, A);

        printf("--\nForward Iteration of A:\nKey\tValue\n===\t=====\n");
        for(i=beginForward(A); currentKey(A)!=KEY_UNDEF; next(A)){
                printf(KEY_FORMAT"\t"VAL_FORMAT"\n", currentKey(A), currentVal(A));
        }

        printf("--\nReverse Iteration of B:\nKey\tValue\n===\t=====\n");
        for(i=beginReverse(B); currentKey(B)!=KEY_UNDEF; prev(B)){
                printf(KEY_FORMAT"\t"VAL_FORMAT"\n", currentKey(B), currentVal(B));
        }

        delete(A, "apples");
        delete(A, "spider");
        delete(A, "cheetos");
        delete(A, "apricot");
        delete(A, "unseen");

        printf("--\nList A (Size %d):\n", size(A));
        printDictionary(stdout, A);

        for(i=0; i<17; i++) insert(A, bank[i], i);
        for(i=0; i<17; i++) insert(B, bank[i], i);

        printf("--\nList A (Size %d):\n", size(A));
        printDictionary(stdout, A);

        printf("--\nList B (Size %d):\n", size(B));
        printDictionary(stdout, A);

        makeEmpty(A);
        
        printf("--\nList A (Size %d):\n", size(A));
        printDictionary(stdout, A);

        freeDictionary(&A);
        freeDictionary(&B);
}
