/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA7
* Shuffle.cpp
* Using List ADT, makes perfect shuffles for a deck of size n given
*******************************************************************************/
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include"List.h"
using namespace std;

void shuffle(List& D);
bool inOrder(List O);

int main(int argc, char** argv){
        int c, i, j, n;
        List L;

        // check for two arguments only
        if(argc!=2){
                cout << "USAGE: $ Shuffle n" << endl;
                exit(EXIT_FAILURE);
        }

        // grab n and make list
        sscanf(argv[1], "%d", &n);

        // print first prompt
        cout << "deck size       shuffle count" << endl;
        cout << "------------------------------" << endl;

        // shuffle each list until arriving to n
        for(i=1; i<=n; i++){
                L.clear();
                for(j=0;j<i;j++){
                        L.insertBefore(j);
                }
                c = 1;
                shuffle(L);
                while(!inOrder(L)){
                        shuffle(L);
                        c++;
                }
                cout << " " << i << "               " << c << endl;
        }

        return EXIT_SUCCESS;
}

void shuffle(List& D){
        int i;
        int odd, split;
        List C;
        odd = (D.size() % 2);
        if(odd){
                split = (D.size() - 1) / 2;
        }else{
                split = D.size() / 2;
        }
        for(i=1; i<=split; i++){
                D.moveFront();
                C.insertBefore(D.moveNext());
                D.eraseBefore();
        }
        C.moveFront();
        D.moveFront();
        while(!C.isEmpty()){
                D.moveNext();
                D.insertBefore(C.moveNext());
                C.eraseBefore();
        }
}

bool inOrder(List O){
        int i = 0;
        O.moveFront();
        while(O.moveNext()==i){
                i++;
        }
        return (i==O.size());
}
