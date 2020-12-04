/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA1
* List.c
* Implementation file for List ADT
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define NUM_TYPE int // data type (i.e. int or long)
#define NUM_TYPE_STRING "%d " // used for printList()
#define INDEXFUNC index // switch to Index when running on local system

// private NodeObj type
typedef struct NodeObj{
        NUM_TYPE data;
        struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
        int numItems;
        Node cursor;
        Node front;
        Node back;
} ListObj;

// Constructors-Destructors ----------------------------------------------------
// newNode()
// Creates and returns a new node with the data given
Node newNode(NUM_TYPE d){
        Node N = (Node)malloc(sizeof(NodeObj));
        N->data = d;
        N->next = NULL;
        return N;
}

// freeNode()
// Frees memory from the node given
void freeNode(Node* pN){
        if(pN!=NULL && *pN!=NULL){
                free(*pN);
                *pN = NULL;
        }
}

// newList()
// Creates and returns a new empty list
List newList(){
        List L;
        L = (List)malloc(sizeof(ListObj));
        L->numItems = 0;
        L->cursor = NULL;
        L->front = NULL;
        L->back = NULL;
        return(L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL){
        if(pL!=NULL && *pL!=NULL){
                clear(*pL);
                free(*pL);
                *pL = NULL;
        }
}

// Access functions ------------------------------------------------------------
// length()
// Returns the number of elements in L.
int length(List L){
        if(L==NULL){
                printf("List Error: calling length() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        return(L->numItems);
}

// index()
// Returns index of cursor element if defined, -1 otherwise
int INDEXFUNC(List L){
        int idx;
        Node N;
        Node C;
        if(L==NULL){
                printf("List Error: calling index() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(L->cursor==NULL){
                return(-1);
        }
        N = L->front;
        C = L->cursor;
        idx = 0;
        while(N!=C && N!=NULL){
                idx++;
                N = N->next;
        }
        return(idx);
}

// front()
// Returns front element of L. Pre: length()>0
NUM_TYPE front(List L){
        if(L==NULL){
                printf("List Error: calling front() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0){
                return(L->front->data);
        }
        return(-1);
}

// back()
// Returns back element of L. Pre: length()>0
NUM_TYPE back(List L){
        if(L==NULL){
                printf("List Error: calling back() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0){
                return(L->back->data);
        }
        return(-1);
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
NUM_TYPE get(List L){
        if(L==NULL){
                printf("List Error: calling get() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0){
                if(INDEXFUNC(L)>=0){
                        return(L->cursor->data);
                }
        }
        return(-1);
}

// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0 void set(List L, long x);
void set(List L, NUM_TYPE data){
        if(L==NULL){
                printf("List Error: calling set() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0 && index(L)>=0){
                L->cursor->data = data;
        }
}

// equals()
// Returns true (1) iff Lists A and B are in same state, and returns false (0)
// otherwise
int equals(List A, List B){
        int eq;
        Node N;
        Node M;
        if(A==NULL || B==NULL){
                printf("List Error: calling equals() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        eq = (length(A) == length(B));
        N = A->front;
        M = B->front;
        while( eq && N!=NULL && M!=NULL ){
                eq = (N->data == M->data);
                N = N->next;
                M = M->next;
        }
        return eq;
}

// Manipulation procedures -----------------------------------------------------
// clear()
// Resets L to its original empty state
void clear(List L){
        if(L==NULL){
                printf("List Error: calling clear() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        while( length(L)>0 ) { deleteFront(L); }
        L->numItems = 0;
}

// moveFront()
// if L is non-empty, sets cursor under the front element, otherwise does nothing
void moveFront(List L){
        if(L==NULL){
                printf("List Error: calling moveFront() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0){
                L->cursor = L->front;
        }
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing
void moveBack(List L){
        if(L==NULL){
                printf("List Error: calling moveBack() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0){
                L->cursor = L->back;
        }
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front;
// If cursor is defined and at front, set cursor to NULL
// If cursor is undefined, do nothing
void movePrev(List L){
        Node B;
        if(L==NULL){
                printf("List Error: calling movePrev() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0){
                if(L->cursor!=NULL){
                        if(L->cursor==L->front){
                                L->cursor = NULL;
                        }else{
                                B = L->front; // B is parent of cursor
                                while(B->next!=L->cursor){
                                        B = B->next;
                                }
                                L->cursor = B;
                        }
                }
        }
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward back
// If cursor is defined and at back, set to NULL
// if cursor is undefined, do nothing
void moveNext(List L){
        if(L==NULL){
                printf("List Error: calling moveNext() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0){
                if(L->cursor!=NULL){
                        if(L->cursor==L->back){
                                L->cursor = NULL;
                        }else{
                                L->cursor = L->cursor->next;
                        }
                }
        }
}

// prepend()
// Insert new element into L.  If L is non-empty, insertion takes place before
// front element
void prepend(List L, NUM_TYPE data){
        Node N;
        if(L==NULL){
                printf("List Error: calling prepend() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        N = newNode(data);
        if (length(L)>0){
                N->next = L->front;
                L->front = N;
        }else{
                L->front = N;
                L->back = N;
        }
        L->numItems++;
}

// append()
// Insert new element into L.  If L is non-empty, Insertion takes place after
// back element
void append(List L, NUM_TYPE data){
        Node N;
        if(L==NULL){
                printf("List Error: calling append() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        N = newNode(data);
        if(length(L)>0){
                L->back->next = N;
                L->back = N;
        }else{
                L->front = N;
                L->back = N;
        }
        L->numItems++;
}

// insertBefore()
// Insert new element before cursor.  Pre: length()>0, index()>=0
void insertBefore(List L, NUM_TYPE data){
        int idx;
        Node N;
        Node P;
        if(L==NULL){
                printf("List Error: calling insertBefore() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        N = newNode(data);
        if(length(L)>0 && INDEXFUNC(L)>=0){
                if(L->cursor==L->front){
                        freeNode(&N);
                        prepend(L, data);
                }else{
                        P = L->front;
                        idx = INDEXFUNC(L);
                        while((--idx)>0){
                                P = P->next;
                        }
                        P->next = N;
                        N->next = L->cursor;
                        L->numItems++;
                }
        }
}

// insertAfter()
// Insert new element after cursor.  Pre: length()>0, index>=0
void insertAfter(List L, NUM_TYPE data){
        Node N;
        if(L==NULL){
                printf("List Error: calling insertAfter() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        N = newNode(data);
        if(length(L)>0 && INDEXFUNC(L)>=0){
                if(L->cursor==L->back){
                        freeNode(&N);
                        append(L, data);
                }else{
                        N->next = L->cursor->next;
                        L->cursor->next = N;
                        L->numItems++;
                }
        }
}

// deleteFront()
// Delete the front element.  Pre: length()>0
void deleteFront(List L){
        Node N;
        if(L==NULL){
                printf("List Error: calling deleteFront() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0){
                if(L->front==L->back){
                        L->back = NULL;
                }
                if(L->front==L->cursor){
                        L->cursor = NULL;
                }
                N = L->front;
                L->front = L->front->next;
                freeNode(&N);
                L->numItems--;
        }
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L){
        Node N = NULL;
        Node P = NULL;
        if(L==NULL){
                printf("List Error: calling deleteBack() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0){
                if(L->back==L->cursor){
                        L->cursor = NULL;
                }
                N = L->back;
                if(length(L)==1){
                        L->front = NULL;
                        L->back = NULL;
                }else{
                        P = L->front; // parent of back node
                        while(P->next!=N){
                                P = P->next;
                        }
                        P->next = NULL;
                        L->back = P;
                }
                freeNode(&N);
                L->numItems--;
        }
}

// delete()
// Delete cursor element, making cursor undefined.  Pre: length()>0, index()>=0
void delete(List L){
        Node N;
        Node P;
        if(L==NULL){
                printf("List Error: calling delete() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0 && INDEXFUNC(L)>=0){
                if(L->cursor==L->front){
                        deleteFront(L);
                }else if(L->cursor==L->back){
                        deleteBack(L);
                }else{
                        N = L->cursor;
                        L->cursor = NULL;
                        P = L->front;
                        while(P->next!=N){
                                P = P->next;
                        }
                        P->next = N->next;
                        freeNode(&N);
                        L->numItems--;
                }
        }
}

// Other operations ------------------------------------------------------------
// printList()
// Prints to file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers with front on left
void printList(FILE* out, List L){
        Node N;
        if(L==NULL){
                printf("List Error: calling printList() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        N = L->front;
        while(N!=NULL){
                fprintf(out, NUM_TYPE_STRING, N->data);
                N = N->next;
        }
}

// copyList()
// Returns a new list representing the same integer sequence as L.  The cursor in
// the new list is undefined, regardless of teh state of the cursor in L.  The state
// of L is unchanged
List copyList(List L){
        List C;
        Node N;
        if(L==NULL){
                printf("List Error: calling copyList() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        C = newList();
        N = L->front;
        while(N!=NULL){
                append(C, N->data);
                N = N->next;
        }
        return C;
}

// concatList()
// Returns a new list which is the concatenation of A and B.  Cursor in new list
// is undefined.  States of A and B are unchanged.
List concatList(List A, List B){
        List C;
        Node N;
        if(A==NULL || B==NULL){
                printf("List Error: calling concatList() on "\
                        "NULL List reference\n");
                exit(EXIT_FAILURE);
        }
        C = copyList(A);
        N = B->front;
        while(N!=NULL){
                append(C, N->data);
                N = N->next;
        }
        return C;
}
