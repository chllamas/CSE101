/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA7
* ListTest.cpp
* Test file for List ADT
*******************************************************************************/
#include<iostream>
#include"List.h"
using namespace std;

int main(){
        int i;
        List A;

        // Testing simple insertions
        A.insertAfter(5);
        A.insertAfter(4);
        A.insertBefore(3);
        cout << "A[" << A.size() << "] = {" << A << "}" << endl;

        // Testing copy
        List B(A);
        cout << "B[" << B.size() << "] = {" << B << "}" << endl;

        // Testing equals operator (==)
        cout << "A==B : " << (A==B) << endl;
        A.clear();
        cout << "A==B : " << (A==B) << endl;
        A.insertAfter(5);
        A.insertAfter(4);
        A.insertBefore(2);
        cout << "A==B : " << (A==B) << endl;

        // Testing equal operator (=)
        A = B;
        cout << "A[" << A.size() << "] = {" << A << "}" << endl;
        cout << "B[" << B.size() << "] = {" << B << "}" << endl;

        // Testing concat
        A.clear();
        B.clear();
        for(i=1; i<=5; i++){
                A.insertBefore(i);
        }
        for(i=6; i<=10; i++){
                B.insertBefore(i);
        }
        cout<< "CursorA: " << A.position() << " | CursorB: " << B.position() << endl;
        List C = A.concat(B);
        cout << "A[" << A.size() << "] = {" << A << "}" << endl;
        cout << "B[" << B.size() << "] = {" << B << "}" << endl;
        cout << "C[" << C.size() << "] = {" << C << "}" << endl;

        // print list A using cursor only (forwardss, and backwards)
        A.clear();
        for(i=1; i<=15; i++){
                A.insertBefore(i);
        }
        A.moveFront();
        cout << "==========" << endl;
        while(A.peekNext()!=-1){
                cout << A.moveNext() << endl;
        }
        cout << "==========" << endl;
        while(A.peekPrev()!=-1){
                cout << A.movePrev()<< endl;
        }
        cout << "==========" << endl;

        // testing findNext and findPrev
        A.clear();
        A. insertAfter(10);
        A. insertAfter(10);
        A. insertAfter(9);
        A. insertAfter(10);
        A. insertAfter(4);
        A. insertAfter(2);
        A. insertAfter(3);
        A. insertAfter(4);
        A. insertAfter(10);
        A. insertAfter(1);
        cout << "A[" << A.size() << "] = {" << A << "}" << endl;
        A.moveFront();
        cout << "A(10) @";
        while(A.findNext(10)!=-1){
                cout << " " << A.position();
        }
        cout << endl;
        cout << "A(10) @";
        while(A.findPrev(10)!=-1){
                cout << " " << A.position();
        }
        cout << endl;

        // testing cleanup
        int cleanupArr[13] = {4, 3, 2, 3, 4, 4, 3, 2, 5, 5, 6, 2, 4};
        A.clear();
        for(i=0; i<13; i++){
                A.insertBefore(cleanupArr[i]);
        }
        while(A.position()!=7){
                A.movePrev();
        }
        cout << "==========" << endl;
        cout << "A[" << A.size() << "] = {" << A << "}" << endl;
        A.cleanup();
        cout << "A[" << A.size() << "] = {" << A << "}" << endl;
        cout << "Cursor @ " << A.position() << " between " << A.peekPrev() << " and " << A.peekNext() << endl;

        // we are done
        cout << "All tests worked as expected!" << endl;

        return 0;
}
