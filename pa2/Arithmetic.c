/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA2
* BigInteger.c
* Implementation file for BigInteger ADT
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

int main(int argc, char* argv[]){
        BigInteger A,B,C,D;
        FILE *in, *out; //handles for the files we will be reading/writing
        char ch;
	char* str;
        int n, idx;
	size_t size = 256;
        if(argc!=3){
                fprintf(stderr, "Usage: Arithmetic <input_file> <output_file>\n");
                exit(EXIT_FAILURE);
        }

        // open file for reading
        if((in=fopen(argv[1], "r"))==NULL){
                fprintf(stderr, "Read Error: Could not open file %s\n", argv[1]);
                exit(EXIT_FAILURE);
        }

        // open file for writing
        if((out=fopen(argv[2], "w"))==NULL){
                fprintf(stderr, "Write Error: Could not open file %s\n", argv[2]);
                exit(EXIT_FAILURE);
        }

        // check that there are four lines
        n = 0;
        ch = getc(in);
        while(ch!=EOF){
                if(ch=='\n'){
                        n++;
                }
                ch = getc(in);
        }
        if(n!=4){
                fprintf(stderr, "Read error: Incorrect input file formatting\n");
                exit(EXIT_FAILURE);
        }

        // reset file
        rewind(in);

        // place second line of input file into str
        str = (char*) malloc(size);
	fgets(str, size, in);
        n = atoi(str); // n is the amount of chars in first input
        free(str);
        str = (char*)malloc(n+3);
        fgets(str, n+3, in); // str still contains a \n at the end
        idx = 0;
        while(str[idx]!='\n' && str[idx]!='\0'){
                idx++;
        }
        str[idx] = '\0';

        // create A
        A = stringToBigInteger(str);

        // place fourth line of input file into str
        free(str);
        str = (char*) malloc(size);
	fgets(str, size, in);
        n = atoi(str); // n is the amount of chars in second input
        free(str);
        str = (char*)malloc(n+3);
        fgets(str, n+3, in); // str still contains a \n at the end
        idx = 0;
        while(str[idx]!='\n' && str[idx]!='\0'){
                idx++;
        }
        str[idx] = '\0';

        // create B
        B = stringToBigInteger(str);

        // done with str
        free(str);

        // print following quantities
	// A
	printBigInteger(out, A);
	fprintf(out, "\n\n");

	// B
	printBigInteger(out, B);
	fprintf(out, "\n\n");

	// A + B
	C = sum(A, B);
	printBigInteger(out, C);
	fprintf(out, "\n\n");
	freeBigInteger(&C);

	// A - B
	C = diff(A, B);
	printBigInteger(out, C);
	fprintf(out, "\n\n");
	freeBigInteger(&C);

	// A - A
	C = diff(A,A);
	printBigInteger(out, C);
	fprintf(out, "\n\n");
	freeBigInteger(&C);

	// 3A - 2B
        C = stringToBigInteger("3");
        D = stringToBigInteger("2");
        multiply(C, A, C);
        multiply(D, B, D);
        subtract(C, C, D);
        printBigInteger(out, C);
        fprintf(out, "\n\n");
        freeBigInteger(&C);
        freeBigInteger(&D);

	// AB
        C = prod(A, B);
        printBigInteger(out, C);
        fprintf(out, "\n\n");
        freeBigInteger(&C);

	// A^2
        C = prod(A, A);
        printBigInteger(out, C);
        fprintf(out, "\n\n");
        freeBigInteger(&C);

	// B^2
        C = prod(B,B);
        printBigInteger(out, C);
        fprintf(out, "\n\n");
        freeBigInteger(&C);

	// 9A^4 + 16B^5
        C = prod(A, A);
        multiply(C, C, A);
        multiply(C, C, A); // C = A^4
        D = prod(B, B);
        multiply(D, D, B);
        multiply(D, D, B);
        multiply(D, D, B); // D = A^5
        freeBigInteger(&A);
        freeBigInteger(&B);
        A = stringToBigInteger("9");
        B = stringToBigInteger("16");
        multiply(A, A, C); // A = 9A^4
        multiply(B, B, D); // B = 16B^5
        add(A, A, B); // A = A + B
        printBigInteger(out, A);
        fprintf(out, "\n");

        // close the filestreams
        fclose(in);
        fclose(out);

        // done with BigInteger ADTs
        freeBigInteger(&A);
        freeBigInteger(&B);
        freeBigInteger(&C);
        freeBigInteger(&D);
}
