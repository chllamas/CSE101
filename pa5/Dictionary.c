/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA5
* Dictionary.c
* Implementation file for Dictionary ADT
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 256

// Exported type --------------------------------------------------------------
// private type Node
typedef struct NodeObj* Node;

// private type NodeObj
typedef struct NodeObj{
        KEY_TYPE key;
        VAL_TYPE value;
        Node parent;
        Node left;
        Node right;
} NodeObj;

// private type DictionaryObj
typedef struct DictionaryObj{
        int unique;
        int size;
        int iteration; // 1==forward, -1==reverse, 0==notStarted
        Node cursor;
        Node root;
} DictionaryObj;

// newNode()
// returns reference to a new node with given (k,v) pair, and NULL Nodes pointed to
Node newNode(KEY_TYPE k, VAL_TYPE v){
        Node N = (Node)malloc(sizeof(NodeObj));
        N->key = k;
        N->value = v;
        N->parent = NULL;
        N->left = NULL;
        N->right = NULL;
        return N;
}

// freeNode()
// frees all heap memory associated with given node and all children if there are any
void freeNode(Node* pN){
        if(*pN!=NULL && pN!=NULL){
                if((*pN)->left!=NULL){
                        freeNode(&((*pN)->left));
                }
                if((*pN)->right!=NULL){
                        freeNode(&((*pN)->right));
                }
                free(*pN);
                *pN = NULL;
        }
}

// printNode()
// prints nodes given in INORDER TRAVERSAL
void printNode(FILE* out, Node N){
        if(N!=NULL){
                printNode(out, N->left);
                fprintf(out, KEY_FORMAT, N->key);
                fprintf(out, " ");
                fprintf(out, VAL_FORMAT, N->value);
                fprintf(out, "\n");
                printNode(out, N->right);
        }
}

// getNode()
// returns pointer to node with the given key; make sure key exists in Dictionary
// before running
Node getNode(Dictionary D, KEY_TYPE k){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling getNode() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        Node N = D->root;
        int c;
        while((c=KEY_CMP(k, N->key))!=0){
                if(c>0){
                        N = N->right;
                }else{
                        N = N->left;
                }
        }
        return N;
}

// Constructors-Destructors ---------------------------------------------------
// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary
// will accept duplicate keys, i.e. distinct pairs with identical keys. If
// unique==true (1 or any non-zero value), then duplicate keys will not be
// accepted.
Dictionary newDictionary(int unique){
        Dictionary D = (Dictionary)malloc(sizeof(DictionaryObj));
        D->size = 0;
        D->iteration = 0;
        D->cursor = NULL;
        D->root = NULL;
        if(unique==0){
                D->unique = 0;
        }else{
                D->unique = 1;
        }
        return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
        if(*pD!=NULL && pD!=NULL){
                makeEmpty(*pD);
                free(*pD);
                *pD = NULL;
        }
}

// Access functions -----------------------------------------------------------
// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling size() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling getUnique() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        return D->unique;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling lookup() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        Node N = D->root;
        int c;
        VAL_TYPE r = VAL_UNDEF;
        while(N!=NULL){
                c = KEY_CMP(k, N->key);
                if(c==0){
                        r = N->value;
                        break;
                }else if(c<0){
                        N = N->left;
                }else{
                        N = N->right;
                }
        }
        return r;
}

// Manipulation procedures ----------------------------------------------------
// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling insert() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        int c;
        Node N, C;
        if(getUnique(D)==1 && lookup(D,k)!=VAL_UNDEF){
                return; // enforcement checked, everything else runs the same
        }
        N = newNode(k, v);
        if(size(D)==0){
                D->root = N;
        }else{
                C = D->root;
                while(1){
                        c = KEY_CMP(k, C->key);
                        if(c>=0){
                                if(C->right==NULL){
                                        N->parent = C;
                                        C->right = N;
                                        break;
                                }else{
                                        C = C->right;
                                }
                        }else{
                                if(C->left==NULL){
                                        N->parent = C;
                                        C->left = N;
                                        break;
                                }else{
                                        C = C->left;
                                }
                        }
                }
        }
        D->size++;
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling delete() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        Node N, M, P;
        if(lookup(D, k)!=VAL_UNDEF){
                if(size(D)==1){
                        makeEmpty(D);
                }else{
                        N = getNode(D, k); // N is node to be deleted
                        if(D->cursor==N) {
                                D->cursor = NULL;
                                D->iteration = 0;
                        };
                        while(1){
                                M = NULL;
                                // grab the "next" Node and place it into M
                                if(N->right!=NULL){
                                        M = N->right;
                                        while(M->left!=NULL){
                                                M = M->left;
                                        }
                                }else if (N->left!=NULL){
                                        M = N->left;
                                        while(M->right!=NULL){
                                                M = M->right;
                                        }
                                }
                                // place M contents into N, and loop deleting M
                                // otherwise just free N
                                if(M!=NULL){
                                        N->key = M->key;
                                        N->value = M->value;
                                        N = M;
                                }else{
                                        P = N->parent;
                                        if(P->right==N) P->right = NULL;
                                        if(P->left==N) P->left = NULL;
                                        freeNode(&N);
                                        D->size--;
                                        break;
                                }
                        }
                }
        }
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling makeEmpty() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        freeNode(&(D->root));
        D->cursor = NULL;
        D->root = NULL;
        D->size = 0;
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling beginForward() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        Node N;
        if(size(D)>0){
                N = D->root;
                while(N->left!=NULL) N = N->left;
                D->cursor = N;
                D->iteration = 1;
                return N->value;
        }
        return VAL_UNDEF;
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling beginReverse() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        Node N;
        if(size(D)>0){
                N = D->root;
                while(N->right!=NULL) N = N->right;
                D->cursor = N;
                D->iteration = -1;
                return N->value;
        }
        return VAL_UNDEF;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling currentKey() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        if(D->cursor!=NULL){
                return D->cursor->key;
        }
        return KEY_UNDEF;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling currentVal() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        if(D->cursor!=NULL){
                return D->cursor->value;
        }
        return VAL_UNDEF;
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
// REMOVE COMMENTS IF FORWARD/REVERSE set a direction bias to next/prev
VAL_TYPE next(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling next() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        Node N;
        if(D->cursor!=NULL){
//                if(D->iteration==1){            //forward
                        if(D->cursor->right!=NULL){
                                N = D->cursor->right;
                                while(N->left!=NULL){
                                        N = N->left;
                                }
                                D->cursor = N;
                                return currentVal(D);
                        }
                        while(D->cursor->parent!=NULL){
                                if(KEY_CMP(D->cursor->parent->key, D->cursor->key) >= 0){
                                        D->cursor = D->cursor->parent;
                                        return currentVal(D);
                                }
                                D->cursor = D->cursor->parent;
                        }
                        D->cursor = NULL;
                        D->iteration = 0;
/*
                }else if(D->iteration==-1){     // reverse
                        if(D->cursor->left!=NULL){
                                N = D->cursor->left;
                                while(N->right!=NULL){
                                        N = N->right;
                                }
                                D->cursor = N;
                                return currentVal(D);
                        }
                        while(D->cursor->parent!=NULL){
                                if(KEY_CMP(D->cursor->parent->key, D->cursor->key) <= 0){
                                        D->cursor = D->cursor->parent;
                                        return currentVal(D);
                                }
                                D->cursor = D->cursor->parent;
                        }
                        D->cursor = NULL;
                        D->iteration = 0;
                }
*/
        }
        return VAL_UNDEF;
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
// REMOVE COMMENTS IF FORWARD/REVERSE set a direction bias to next/prev
VAL_TYPE prev(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling prev() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        Node N;
        if(D->cursor!=NULL){
//                if(D->iteration==1){            //forward
                        if(D->cursor->left!=NULL){
                                N = D->cursor->left;
                                while(N->right!=NULL){
                                        N = N->right;
                                }
                                D->cursor = N;
                                return currentVal(D);
                        }
                        while(D->cursor->parent!=NULL){
                                if(KEY_CMP(D->cursor->parent->key, D->cursor->key) <= 0){
                                        D->cursor = D->cursor->parent;
                                        return currentVal(D);
                                }
                                D->cursor = D->cursor->parent;
                        }
                        D->cursor = NULL;
                        D->iteration = 0;
/*
                }else if(D->iteration==-1){     // reverse
                        if(D->cursor->right!=NULL){
                                N = D->cursor->right;
                                while(N->left!=NULL){
                                        N = N->left;
                                }
                                D->cursor = N;
                                return currentVal(D);
                        }
                        while(D->cursor->parent!=NULL){
                                if(KEY_CMP(D->cursor->parent->key, D->cursor->key) >= 0){
                                        D->cursor = D->cursor->parent;
                                        return currentVal(D);
                                }
                                D->cursor = D->cursor->parent;
                        }
                        D->cursor = NULL;
                        D->iteration = 0;
                }
*/
        }
        return VAL_UNDEF;
}

// Other operations -----------------------------------------------------------
// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling printDictionary() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        // will print the BST using INORDER TRAVERSAL
        printNode(out, D->root);
}
