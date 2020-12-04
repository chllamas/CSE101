/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA2
* BigInteger.c
* Implementation file for BigInteger ADT
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"
#include "List.h"

// when turning in...
// BASE = 1000000000
// POWER = 9
#define BASE 1000000000
#define POWER 9

// Exported types -------------------------------------------------------------

// private BigIntegerObj type
typedef struct BigIntegerObj{
        int sign; // -1=negative, 0=zero-state, 1=positive
        List list; // ∀x∊L [0 <= x < BASE]
} BigIntegerObj;

// Private functions ----------------------------------------------------------

// POW()
// Simulates the exponential power function
long POW(long base, long power){
        int i;
        if(power==0) return(1);
        if(power==1) return(base);
        for(i=2; i<=power; i++){
                base = base * 10;
        }
        return(base);
}

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state
BigInteger newBigInteger(){
        BigInteger P = (BigInteger)malloc(sizeof(BigIntegerObj));
        List L = newList();
        P->sign = 0;
        P->list = L;
        return P;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
        if(*pN!=NULL && pN!=NULL){
                List L = (*pN)->list;
                freeList(&L);
                free(*pN);
                *pN = NULL;
        }
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
        if(N==NULL){
                printf("BigInteger Error: calling sign() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        return(N->sign);
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
        int sA, sB;
        //List M, N;
        if(A==NULL || B==NULL){
                printf("BigInteger Error: calling compare() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        //M = A->list;
        //N = B->list;
        sA = sign(A);
        sB = sign(B);
        // A is positive while B is zero or negative || A is zero while B is negative
        if(((sA==1)&&(sB==0 || sB==-1)) || ((sA==0)&&(sB==-1))){
                return(1); // A>B
        }
        // A is negative while B is zero or positive || A is zero while B is positive
        if(((sA==-1)&&(sB==0 || sB==1)) || ((sA==0)&&(sB==1))){
                return(-1); // A<B
        }
        // both are zero
        if((A->sign==0)&&(B->sign==0)){
                return 0;
        }

        if(length(A->list)<length(B->list)){
                return(-1);
        }else if(length(A->list)==length(B->list)){
                moveFront(A->list);
                moveFront(B->list);
                while(get(A->list)==get(B->list) && index(A->list)!=-1){
                        moveNext(A->list);
                        moveNext(B->list);
                }
                if(index(A->list)!=-1){
                        if(get(A->list)<get(B->list) && sign(A)==1){
                                return(-1);
                        }else if(get(A->list)>get(B->list) && sign(A)==-1){
                                return(-1);
                        }
                }
        }

        return(1);
}

// equals()
// Returns true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
        int t;
        if(A==NULL || B==NULL){
                printf("BigInteger Error: calling equals() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        // the lists must be equal, and the signs as well
        t = (listEquals(A->list, B->list) && (A->sign==B->sign));
        return(t);
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
        if(N==NULL){
                printf("BigInteger Error: calling makeZero() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        clear(N->list);
        N->sign = 0;
}

// negate()
// Reverses the sign of N: positive <--> negative.  Does nothign if N is in the
// zero state.
void negate(BigInteger N){
        if(N==NULL){
                printf("BigInteger Error: calling negate() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        if(N->sign==1)
                N->sign = -1;
        else if(N->sign==-1)
                N->sign = 1;
}

// BigInteger Arithmetic Operations -------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
        long data = 0;          // handle for data to be added to BigInt
        int num = 0;            // current digit being looked at
        int idx = 0;          // char index
        int powCount = 0;       // marker for counting 0<=x<=POWER
        BigInteger N = newBigInteger();
        while(s[idx]!='\0'){
                num = (int)(s[idx]) - 48; // offset for ascii values
                if( !((num>=0 && num<=9) || (s[0]=='+') || (s[0]=='-')) ){
                        printf("Invalid string to stringToBigInteger()\n");
                        exit(EXIT_FAILURE);
                }
                idx++;
        }
        while(--idx!=-1){
                if(s[idx]=='+'){
                        N->sign = 1;
                }else if(s[idx]=='-'){
                        N->sign = -1;
                }else{
                        num = (int)s[idx] - 48;
                        data = data + ((long)num * POW(10, powCount++));
                        if(powCount==POWER){
                                prepend(N->list, data);
                                data = 0;
                                powCount = 0;
                        }
                }
        }
        if(data>0){
                prepend(N->list, data);
        }
        moveFront(N->list);
        while(index(N->list)!=-1){
                if(get(N->list)==0){
                        delete(N->list);
                        moveNext(N->list);
                }else{
                        break;
                }
        }
        if(length(N->list)==0){
                N->sign = 0;
        }else{
                if(N->sign!=-1){
                        N->sign = 1;
                }
        }
        return N;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
        if(N==NULL){
                printf("BigInteger Error: calling copy() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        BigInteger C = newBigInteger();
        C->sign = N->sign;
        C->list = copyList(N->list);
        return(C);
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
        long data;
        long carry = 0;
        if(S==NULL || A==NULL || B==NULL){
                printf("BigInteger Error: calling add() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        if(A==B){
                BigInteger C = copy(A);
                add(S, A, C);
                freeBigInteger(&C);
                return;
        }
        if(S==A){
                BigInteger C = copy(A);
                add(S, C, B);
                freeBigInteger(&C);
                return;
        }
        if(S==B){
                BigInteger C = copy(B);
                add(S, A, C);
                freeBigInteger(&C);
                return;
        }
        // a==0 & b==0
        if(sign(A)==0 && sign(B)==0){
                makeZero(S);
                return;
        }
        // -a + b = -(a - b)
        if(sign(A)==-1 && sign(B)==1){
                BigInteger C = copy(A);
                C->sign = 1;
                subtract(S, B, C);
                freeBigInteger(&C);
                return;
        }
        // a + -b --> c = -(-b) --> s = a - c
        if(sign(A)==1 && sign(B)==-1){
                BigInteger C = copy(B);
                C->sign = 1;
                subtract(S, A, C);
                freeBigInteger(&C);
                return;
        }
        // -a + -b --> c = -(-a) --> d = -(-b) --> s = -(a+b)
        if(sign(A)==-1 && sign(B)==-1){
                BigInteger C = copy(A);
                BigInteger D = copy(B);
                C->sign = 1;
                D->sign = 1;
                add(S, C, D);
                S->sign = -1;
                freeBigInteger(&C);
                freeBigInteger(&D);
                return;
        }
        if((sign(A)==-1 && sign(B)==0) || (sign(A)==0 && sign(B)==-1)){
                S->sign = -1;
        }else{
                S->sign = 1;
        }
        moveBack(A->list);
        moveBack(B->list);
        clear(S->list);
        while(index(A->list)!=-1 || index(B->list)!=-1 || carry>0){
                data = carry;
                carry = 0;
                if(index(A->list)!=-1){
                        data = data + get(A->list);
                }
                if(index(B->list)!=-1){
                        data = data + get(B->list);
                }
                if(data>=BASE){
                        data = data - BASE;
                        carry++;
                }
                prepend(S->list, data);
                movePrev(A->list);
                movePrev(B->list);
        }
        // clean up the nasty 0's at the front
        moveFront(S->list);
        while(get(S->list)==0){
                delete(S->list);
                moveFront(S->list);
        }
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
        if(A==NULL || B==NULL){
                printf("BigInteger Error: calling add() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        BigInteger S = newBigInteger();
        add(S, A, B);
        return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
        long data;
        long carry = 0;
        if(D==NULL || A==NULL || B==NULL){
                printf("BigInteger Error: calling subtract() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        if(A==B){
                makeZero(D);
                return;
        }
        if(D==A){
                BigInteger C = copy(A);
                subtract(D, C, B);
                freeBigInteger(&C);
                return;
        }
        if(D==B){
                BigInteger C = copy(B);
                subtract(D, A, C);
                freeBigInteger(&C);
                return;
        }
        // A==B
        if(equals(A, B)){
                makeZero(D);
                return;
        }
        // A==0 && B==0
        if(sign(A)==0 && sign(B)==0){
                makeZero(D);
                return;
        }
        // A<0 && B>0
        if(sign(A)==-1 && sign(B)==1){
                BigInteger C = copy(A);
                C->sign = 1;
                add(D, C, B);
                D->sign = -1;
                freeBigInteger(&C);
                return;
        }
        // A>0 && B<0
        if(sign(A)==1 && sign(B)==-1){
                BigInteger C = copy(B);
                C->sign = 1;
                add(D, A, C);
                freeBigInteger(&C);
                return;
        }
        // A<0 && B<0
        // -x - -y = -(x-y)
        if(sign(A)==-1 && sign(B)==-1){
                BigInteger M = copy(A);
                BigInteger N = copy(B);
                M->sign = 1;
                N->sign = 1;
                subtract(D, M, N);
                D->sign = D->sign * -1;
                freeBigInteger(&M);
                freeBigInteger(&N);
                return;
        }
        // make sure A > B, otherwise recurse this function
        if(compare(A,B)==-1){
                subtract(D, B, A);
                D->sign = -1;
                return;
        }
        // A>B>=0 but A,B are NOT both zero, A > B
        D->sign = 1;
        moveBack(A->list);
        moveBack(B->list);
        clear(D->list);
        while(index(A->list)!=-1 || index(B->list)!=-1 || carry>0){
                data = carry;
                carry = 0;
                if(index(A->list)!=-1){
                        data = data + get(A->list);
                }
                if(index(B->list)!=-1){
                        data = data - get(B->list);
                }
                if(data<0){
                        data = data + BASE;
                        carry--;
                }
                prepend(D->list, data);
                movePrev(A->list);
                movePrev(B->list);
        }
        // clean up the nasty 0's at the front
        moveFront(D->list);
        while(get(D->list)==0){
                delete(D->list);
                moveFront(D->list);
        }
}

// diff()
// Returns a reference to a new BigInteger object representing A - B
BigInteger diff(BigInteger A, BigInteger B){
        if(A==NULL || B==NULL){
                printf("BigInteger Error: calling diff() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        BigInteger D = newBigInteger();
        subtract(D, A, B);
        return D;
}

// multiply()
// Places the product of A and B in the existing BigIntger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
        long data = 0;
        long carry = 0;
        long r;
        int zeroidx = 0;
        int i;
        BigInteger T;
        if(P==NULL || A==NULL || B==NULL){
                printf("BigInteger Error: calling multiply() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        if(A==B){
                BigInteger C = copy(B);
                multiply(P,A,C);
                freeBigInteger(&C);
                return;
        }
        if(P==A){
                BigInteger C = copy(A);
                multiply(P,C,B);
                freeBigInteger(&C);
                return;
        }
        if(P==B){
                BigInteger C = copy(B);
                multiply(P,A,C);
                freeBigInteger(&C);
                return;
        }
        if(sign(A)==0 || sign(B)==0){
                makeZero(P);
                return;
        }
        T = newBigInteger();
        moveBack(B->list);
        makeZero(P);
        while(index(B->list)!=-1){
                moveBack(A->list);
                makeZero(T);
                for(i = 0; i<zeroidx; i++){
                        append(T->list, 0);
                }
                while(index(A->list)!=-1){
                        data = get(A->list) * get(B->list);
                        prepend(T->list, data);
                        movePrev(A->list);
                }
                zeroidx++;
                movePrev(B->list);
                // normalize T
                moveBack(T->list);
                while(index(T->list)!=-1){
                        T->sign = 1;
                        data = get(T->list) + carry;
                        carry = 0;
                        if(data>=BASE){
                                printf("==============\ndata = %li\n", data);
                                r = data % BASE;
                                printf("remainder = %li\n", r);
                                carry = (data - r)/BASE;
                                printf("carry = %li\n", carry);
                                data = r;
                                printf("data is now = %li\n==============\n", data);
                        }
                        set(T->list, data);
                        movePrev(T->list);
                }
                if(carry>0){
                        prepend(T->list, carry);
                        carry = 0;
                }
                // add to P
                add(P, P, T);
        }
        if((sign(A)==-1&&sign(B)==1) || (sign(A)==1&&sign(B)==-1)){
                P->sign = -1;
        }
        if(sign(A)==-1&&sign(B)==-1){
                P->sign = 1;
        }
        freeBigInteger(&T);
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
        if(A==NULL || B==NULL){
                printf("BigInteger Error: calling prod() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        BigInteger P = newBigInteger();
        multiply(P,A,B);
        return P;
}

// Other Operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
        int i;
        if(N==NULL){
                printf("BigInteger Error: calling printBigInteger() on "\
                        "NULL BigInteger reference\n");
                exit(EXIT_FAILURE);
        }
        if(N->sign==-1){
                fprintf(out, "-");
        }else if(N->sign==0){
                fprintf(out, "0");
                return;
        }
        moveFront(N->list);
        while(index(N->list)!=-1){
                for(i=POWER - 1; i>0; i--){
                        if(get(N->list) < POW(10, i) && index(N->list)!=0){
                                fprintf(out, "0");
                        }
                }
                fprintf(out, "%li", get(N->list));
                moveNext(N->list);
        }
}
