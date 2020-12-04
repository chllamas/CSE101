#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

// Add tests ------------------------------------------------------------------

void addTest1(FILE* out, char* str1, char* str2);
void addTest2(FILE* out);	// A + A
void addTest3(FILE* out);	// A = A + A

void subtractTest1(FILE* out, char* str1, char* str2);
void subtractTest2(FILE* out);	// A - A
void subtractTest3(FILE* out);	// A = A - A

void multiplyTest1(FILE* out, char* str1, char* str2);
void multiplyTest2(FILE* out);	// A * A
void multiplyTest3(FILE* out);	// A = A * A

int main(){
	FILE* out = fopen("output", "w");

	fprintf(out, "ADDITION TESTS\n");
	addTest1(out, "10", "15");		// no carry
	addTest1(out, "2295120", "8979998");	// w/ carry
	addTest1(out, "0", "0");
	addTest1(out, "52612", "-5152955");	// A + -B
	addTest1(out, "-934680", "8032451");	// -A + B
	addTest1(out, "-81475", "-893114");	// -A + -B
	addTest2(out);
	addTest3(out);

	fprintf(out, "\n");
	fprintf(out, "SUBTRACT TESTS\n");
	subtractTest1(out, "15", "10");	// no carry
	subtractTest1(out, "30", "58");	// carry
	subtractTest1(out, "8502982", "8502982");
	subtractTest1(out, "1", "0845012850538906");
	subtractTest1(out, "582014", "80809809");
	subtractTest1(out, "80158043895", "127342");
	subtractTest1(out, "0", "0");
	subtractTest1(out, "-8591275", "9182");
	subtractTest1(out, "798219", "-891759");
	subtractTest1(out, "-852180", "-21415953");
	subtractTest2(out);
	subtractTest3(out);

	fprintf(out, "\n");
	fprintf(out, "MULTIPLY TESTS\n");
	multiplyTest1(out, "5", "3");
	multiplyTest1(out, "-98", "523");
	multiplyTest1(out, "2456", "-8");
	multiplyTest1(out, "0", "0");
	multiplyTest1(out, "-6243", "0");
	multiplyTest1(out, "0", "89249804515820457210472109510248204");
	multiplyTest1(out, "-8925", "-24");
	multiplyTest2(out);
	multiplyTest3(out);

	fclose(out);
	return(0);
}

void multiplyTest1(FILE* out, char* str1, char* str2){
	BigInteger A = stringToBigInteger(str1);
	BigInteger B = stringToBigInteger(str2);
	BigInteger S = prod(A,B);

	printBigInteger(out, A);
	fprintf(out, " * ");
	printBigInteger(out, B);
	fprintf(out, " = ");
	printBigInteger(out, S);
	fprintf(out, "\n");

	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&S);
}

void multiplyTest2(FILE* out){
	BigInteger A = stringToBigInteger("532");
	BigInteger S = prod(A,A);

	printBigInteger(out, A);
	fprintf(out, " * ");
	printBigInteger(out, A);
	fprintf(out, " = ");
	printBigInteger(out, S);
	fprintf(out, "\n");

	freeBigInteger(&A);
	freeBigInteger(&S);
}

void multiplyTest3(FILE* out){
	BigInteger A = stringToBigInteger("-985");

	printBigInteger(out, A);
	fprintf(out, " * ");
	printBigInteger(out, A);
	fprintf(out, " = ");

	multiply(A,A,A);

	printBigInteger(out, A);
	fprintf(out, "\n");

	freeBigInteger(&A);
}

void subtractTest1(FILE* out, char* str1, char* str2){
	BigInteger A = stringToBigInteger(str1);
	BigInteger B = stringToBigInteger(str2);
	BigInteger S = diff(A,B);

	printBigInteger(out, A);
	fprintf(out, " - ");
	printBigInteger(out, B);
	fprintf(out, " = ");
	printBigInteger(out, S);
	fprintf(out, "\n");

	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&S);
}

void subtractTest2(FILE* out){
	BigInteger A = stringToBigInteger("5810258");
	BigInteger S = diff(A,A);

	printBigInteger(out, A);
	fprintf(out, " - ");
	printBigInteger(out, A);
	fprintf(out, " = ");
	printBigInteger(out, S);
	fprintf(out, "\n");

	freeBigInteger(&A);
	freeBigInteger(&S);
}

void subtractTest3(FILE* out){
	BigInteger A = stringToBigInteger("-129581");

	printBigInteger(out, A);
	fprintf(out, " - ");
	printBigInteger(out, A);
	fprintf(out, " = ");

	subtract(A,A,A);

	printBigInteger(out, A);
	fprintf(out, "\n");

	freeBigInteger(&A);
}

void addTest1(FILE* out, char* str1, char* str2){
	BigInteger A = stringToBigInteger(str1);
	BigInteger B = stringToBigInteger(str2);
	BigInteger S = sum(A,B);

	printBigInteger(out, A);
	fprintf(out, " + ");
	printBigInteger(out, B);
	fprintf(out, " = ");
	printBigInteger(out, S);
	fprintf(out, "\n");

	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&S);
}

void addTest2(FILE* out){
	BigInteger A = stringToBigInteger("+982345");
	BigInteger S = sum(A,A);

	printBigInteger(out, A);
	fprintf(out, " + ");
	printBigInteger(out, A);
	fprintf(out, " = ");
	printBigInteger(out, S);
	fprintf(out, "\n");

	freeBigInteger(&A);
	freeBigInteger(&S);
}

void addTest3(FILE* out){
	BigInteger A = stringToBigInteger("-792581");

	printBigInteger(out, A);
	fprintf(out, " + ");
	printBigInteger(out, A);
	fprintf(out, " = ");

	add(A,A,A);

	printBigInteger(out, A);
	fprintf(out, "\n");

	freeBigInteger(&A);
}
