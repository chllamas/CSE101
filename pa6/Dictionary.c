/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA6
* Dictionary.c
* Implementation file for Dictionary ADT
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 256
#define _BLACK_NODE_ 0
#define _RED_NODE_ 1
#define true 1
#define false 0

// Exported type --------------------------------------------------------------
// private type Node
typedef struct NodeObj* Node;

// private type NodeObj
typedef struct NodeObj{
        KEY_TYPE key;
        VAL_TYPE value;
        int color;
        Node parent;
        Node left;
        Node right;
} NodeObj;

// private type DictionaryObj
typedef struct DictionaryObj{
        int unique;
        int size;
        Node nil;
        Node cursor;
        Node root;
} DictionaryObj;

// newNode()
// returns reference to a new node with given (k,v) pair, and NULL Nodes pointed to
Node newNode(KEY_TYPE k, VAL_TYPE v){
        Node N = (Node)malloc(sizeof(NodeObj));
        N->key = k;
        N->value = v;
        N->color = _RED_NODE_;
        N->parent = NULL;
        N->left = NULL;
        N->right = NULL;
        return N;
}

// printNode_INORDER()
// prints node in given traversal
void printNode(FILE* out, Dictionary D, Node N, int ord){
        if(N!=D->nil){
                if(ord==1){ // inorder
                        printNode(out, D, N->left, ord);
                        fprintf(out, KEY_FORMAT, N->key);
                        fprintf(out, "\n");
                        printNode(out, D, N->right, ord);
                }else if(ord==2){ // preorder
                        fprintf(out, KEY_FORMAT, N->key);
                        fprintf(out, "\n");
                        printNode(out, D, N->left, ord);
                        printNode(out, D, N->right, ord);
                }else if(ord==3){ //postorder
                        printNode(out, D, N->left, ord);
                        printNode(out, D, N->right, ord);
                        fprintf(out, KEY_FORMAT, N->key);
                        fprintf(out, "\n");
                }
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

        int c;
        Node N = D->root;
        while((c=KEY_CMP(k, N->key))!=0){
                if(c<0){
                        N = N->left;
                }else{
                        N = N->right;
                }
        }
        return N;
}

// deleteAllNodes()
// deletes entire tree
void deleteAllNodes(Dictionary D, Node N){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling deleteAllNodes() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        if(N!=D->nil){
                deleteAllNodes(D, N->left);
                deleteAllNodes(D, N->right);
                free(N);
        }
}

// rotateLeft()
// Red-Black Tree rotation function (left)
void rotateLeft(Dictionary D, Node X){
        Node Y = X->right;
        X->right = Y->left;
        if(Y->left!=D->nil){
                Y->left->parent = X;
        }
        Y->parent = X->parent;
        if(X->parent==D->nil){
                D->root = Y;
        }else if(X==X->parent->left){
                X->parent->left = Y;
        }else{
                X->parent->right = Y;
        }
        Y->left = X;
        X->parent = Y;
}

// rotateRight()
// Red-Black Tree rotation function (right)
void rotateRight(Dictionary D, Node X){
        Node Y = X->left;
        X->left = Y->right;
        if(Y->right!=D->nil){
                Y->right->parent = X;
        }
        Y->parent = X->parent;
        if(X->parent==D->nil){
                D->root = Y;
        }else if(X==X->parent->left){
                X->parent->left = Y;
        }else{
                X->parent->right = Y;
        }
        Y->right = X;
        X->parent = Y;
}

// transplant()
// swap out Node U with Node V
void transplant(Dictionary D, Node U, Node V){
        if(U->parent==D->nil){
                D->root = V;
        }else if(U->parent->left==U){
                U->parent->left = V;
        }else{
                U->parent->right = V;
        }
        V->parent = U->parent;
}

// fixInsert()
// maintains Red-Black tree properties after insertion of new node
void fixInsert(Dictionary D, Node Z){
        Node Y;
        while(Z->parent->color==_RED_NODE_){
                if(Z->parent==Z->parent->parent->left){
                        Y = Z->parent->parent->right;
                        if(Y->color==_RED_NODE_){
                                Z->parent->color = _BLACK_NODE_;
                                Y->color = _BLACK_NODE_;
                                Z->parent->parent->color = _RED_NODE_;
                                Z = Z->parent->parent;
                        }else{
                                if(Z==Z->parent->right){
                                        Z = Z->parent;
                                        rotateLeft(D, Z);
                                }
                                Z->parent->color = _BLACK_NODE_;
                                Z->parent->parent->color = _RED_NODE_;
                                rotateRight(D, Z->parent->parent);
                        }
                }else{
                        Y = Z->parent->parent->left;
                        if(Y->color==_RED_NODE_){
                                Z->parent->color = _BLACK_NODE_;
                                Y->color = _BLACK_NODE_;
                                Z->parent->parent->color = _RED_NODE_;
                                Z = Z->parent->parent;
                        }else{
                                if(Z==Z->parent->left){
                                        Z = Z->parent;
                                        rotateRight(D, Z);
                                }
                                Z->parent->color = _BLACK_NODE_;
                                Z->parent->parent->color = _RED_NODE_;
                                rotateLeft(D, Z->parent->parent);
                        }
                }
        }
        D->root->color = _BLACK_NODE_;
}

// fixDelete()
// maintains Red-Black tree properties after deletion of a node
void fixDelete(Dictionary D, Node X){
        Node W;
        while(X!=D->root && X->color==_BLACK_NODE_){
                if(X==X->parent->left){
                        W = X->parent->right;
                        if(W->color==_RED_NODE_){
                                W->color = _BLACK_NODE_;
                                X->parent->color = _RED_NODE_;
                                rotateLeft(D, X->parent);
                                W = X->parent->right;
                        }
                        if(W->left->color==_BLACK_NODE_ && W->right->color==_BLACK_NODE_){
                                W->color = _RED_NODE_;
                                X = X->parent;
                        }else{
                                if(W->right->color==_BLACK_NODE_){
                                        W->left->color = _BLACK_NODE_;
                                        W->color = _RED_NODE_;
                                        rotateRight(D, W);
                                        W = X->parent->right;
                                }
                                W->color = X->parent->color;
                                X->parent->color = _BLACK_NODE_;
                                W->right->color = _BLACK_NODE_;
                                rotateLeft(D, X->parent);
                                X = D->root;
                        }
                }else{
                        W = X->parent->left;
                        if(W->color==_RED_NODE_){
                                W->color = _BLACK_NODE_;
                                X->parent->color = _RED_NODE_;
                                rotateLeft(D, X->parent);
                                W = X->parent->left;
                        }
                        if(W->left->color==_BLACK_NODE_ && W->right->color==_BLACK_NODE_){
                                W->color = _RED_NODE_;
                                X = X->parent;
                        }else{
                                if(W->left->color==_BLACK_NODE_){
                                        W->right->color = _BLACK_NODE_;
                                        W->color = _RED_NODE_;
                                        rotateRight(D, W);
                                        W = X->parent->left;
                                }
                                W->color = X->parent->color;
                                X->parent->color = _BLACK_NODE_;
                                W->left->color = _BLACK_NODE_;
                                rotateRight(D, X->parent);
                                X = D->root;
                        }
                }
        }
        X->color = _BLACK_NODE_;
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
        D->nil = newNode(KEY_UNDEF, VAL_UNDEF);
        D->nil->color = _BLACK_NODE_;
        D->cursor = D->nil;
        D->root = D->nil;
        if(unique==0){
                D->unique = false;
        }else{
                D->unique = true;
        }
        return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
        if(*pD!=NULL && pD!=NULL){
                makeEmpty(*pD);
                free((*pD)->nil);
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
        while(N!=D->nil){
                if(KEY_CMP(k, N->key)==0){
                        return N->value;
                }else if(KEY_CMP(k, N->key)<0){
                        N = N->left;
                }else{
                        N = N->right;
                }
        }
        return VAL_UNDEF;
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

        Node X, Y, Z;
        if(getUnique(D)==true && lookup(D,k)!=VAL_UNDEF) return; // enforcement checked, everything else runs the same
        Z = newNode(k, v);
        Y = D->nil;
        X = D->root;
        while(X!=D->nil){
                Y = X;
                if(KEY_CMP(Z->key, X->key)<0){
                        X = X->left;
                }else{
                        X = X->right;
                }
        }
        Z->parent = Y;
        if(Y==D->nil){
                D->root = Z;
        }else if(KEY_CMP(Z->key, Y->key)<0){
                Y->left = Z;
        }else{
                Y->right = Z;
        }
        Z->left = D->nil;
        Z->right = D->nil;
        Z->color = _RED_NODE_;
        D->size++;
        fixInsert(D, Z);
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

        Node X, Y, Z;
        int origYColor;
        if(lookup(D, k)!=VAL_UNDEF){
                Z = getNode(D, k);
                if(Z==D->cursor){
                        D->cursor = D->nil;
                }
                Y = Z;
                origYColor = Y->color;
                if(Z->left==D->nil){
                        X = Z->right;
                        transplant(D, Z, Z->right);
                }else if(Z->right==D->nil){
                        X = Z->left;
                        transplant(D, Z, Z->left);
                }else{
                        Y = Z->right;
                        while(Y->left!=D->nil){
                                Y = Y->left;
                        }
                        origYColor = Y->color;
                        X = Y->right;
                        if(Y->parent==Z){
                                X->parent = Y;
                        }else{
                                transplant(D, Y, Y->right);
                                Y->right = Z->right;
                                Y->right->parent = Y;
                        }
                        transplant(D, Z, Y);
                        Y->left = Z->left;
                        Y->left->parent = Y;
                        Y->color = Z->color;
                }
                free(Z);
                Z = NULL;
                if(origYColor==_BLACK_NODE_){
                        fixDelete(D, X);
                }
                D->size--;
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

        deleteAllNodes(D, D->root);
        D->cursor = D->nil;
        D->root = D->nil;
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
                while(N->left!=D->nil){
                        N = N->left;
                }
                D->cursor = N;
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
                while(N->right!=D->nil){
                        N = N->right;
                }
                D->cursor = N;
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

        if(D->cursor!=D->nil){
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

        if(D->cursor!=D->nil){
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
VAL_TYPE next(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling next() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        if(D->cursor!=D->nil){
                if(D->cursor->right!=D->nil){
                        D->cursor = D->cursor->right;
                        while(D->cursor->left!=D->nil){
                                D->cursor = D->cursor->left;
                        }
                        return currentVal(D);
                }
                while(D->cursor->parent!=D->nil){
                        if(D->cursor->parent->left==D->cursor){
                                D->cursor = D->cursor->parent;
                                return currentVal(D);
                        }
                        D->cursor = D->cursor->parent;
                }
        }
        D->cursor = D->nil;
        return VAL_UNDEF;
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE prev(Dictionary D){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling prev() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        if(D->cursor!=D->nil){
                if(D->cursor->left!=D->nil){
                        D->cursor = D->cursor->left;
                        while(D->cursor->right!=D->nil){
                                D->cursor = D->cursor->right;
                        }
                        return currentVal(D);
                }
                while(D->cursor->parent!=D->nil){
                        if(D->cursor->parent->right==D->cursor){
                                D->cursor = D->cursor->parent;
                                return currentVal(D);
                        }
                        D->cursor = D->cursor->parent;
                }
        }
        D->cursor = D->nil;
        return VAL_UNDEF;
}

// Other operations -----------------------------------------------------------
// printDictionary()
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.
void printDictionary(FILE* out, Dictionary D, const char* ord){
        if(D==NULL){
                fprintf(stderr, "Dictionary error: calling printDictionary() on NULL "\
                                "Dictionary reference\n");
                exit(EXIT_FAILURE);
        }

        // will print the BST using given traversal
        if(strcmp(ord, "in")==0){
                printNode(out, D, D->root, 1);
        }else if(strcmp(ord, "pre")==0){
                printNode(out, D, D->root, 2);
        }else if(strcmp(ord, "post")==0){
                printNode(out, D, D->root, 3);
        }
}
