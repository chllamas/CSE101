/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA6
* DictionaryTest.c
* Testing client for Dictionary ADT
*******************************************************************************/
#include <stdio.h>
#include "Dictionary.h"

int main(){
	int i;
	int arr[] = {1, 5, 2};
	Dictionary D = newDictionary(1);
	char* alphabet[] = {
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
		"n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
	};

	for(i=0; i<26; i++){
		insert(D, alphabet[i], arr);
	}

	printDictionary(stdout, D, "in");
	printf("Size: %d\n", size(D));

	// printDictionary using beginforward and moving next
	printf("--\n");
	beginForward(D);
	printf(KEY_FORMAT, currentKey(D));
	printf("\n");
	while(next(D)!=VAL_UNDEF){
		printf(KEY_FORMAT, currentKey(D));
		printf("\n");
	}
	printf("Size: %d\n", size(D));

	// delete some items and print
	printf("--\n");
	delete(D, "i");
	delete(D, "a");
	delete(D, "z");
	delete(D, "m");
	printDictionary(stdout, D, "in");
	printf("Size: %d\n", size(D));

	// insert back some items and print
	printf("--\n");
	insert(D, "z", arr);
	insert(D, "i", arr);
	printDictionary(stdout, D, "in");
	printf("Size: %d\n", size(D));

	// print an empty list
	printf("--\n");
	makeEmpty(D);
	printDictionary(stdout, D, "in");
	printf("Size: %d\n", size(D));

	// printDictionary using beginReverse and moving prev
	printf("--\n");
	for(i=25; i>=0; i--){
		insert(D, alphabet[i], arr);
	}
	beginReverse(D);
	printf(KEY_FORMAT, currentKey(D));
	printf("\n");
	while(prev(D)!=VAL_UNDEF){
		printf(KEY_FORMAT, currentKey(D));
		printf("\n");
	}
	printf("Size: %d\n", size(D));

	freeDictionary(&D);
}
