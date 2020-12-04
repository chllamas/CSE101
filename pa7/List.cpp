/*******************************************************************************
* Christopher Llamas, chllamas
* 2020 Spring CSE101 PA7
* List.cpp
* Implementation file for List ADT
*******************************************************************************/
#include<iostream>
#include"List.h"

// Class Constructors & Destructors ----------------------------------------

List::Node::Node(int x) : data(x) {}

// Creates new List in the empty state
List::List(){
        frontDummy = new Node(-1);
        backDummy = new Node(-1);
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        beforeCursor = frontDummy;
        afterCursor = backDummy;
        pos_cursor = 0;
        num_elements = 0;
}

// Copy constructor
List::List(const List& L){
        // make an empty List
        frontDummy = new Node(-1);
        backDummy = new Node(-1);
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        beforeCursor = frontDummy;
        afterCursor = backDummy;
        pos_cursor = 0;
        num_elements = 0;

        // now insert all elements of L into here
        Node* N;
        for(N=L.frontDummy->next; N!=L.backDummy; N=N->next){
                moveBack();
                insertAfter(N->data);
        }
        moveFront();
}

// Destructor
List::~List(){
        clear();
        delete frontDummy;
        delete backDummy;
}

// Access functions --------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise
bool List::isEmpty(){
        if(size()==0){
                return true;
        }else{
                return false;
        }
}

// size()
// Returns the size of this List
int List::size(){
        return num_elements;
}

// position()
// Returns the position of the cursor in this List.  The value returned will be
// in the range 0 to size()
int List::position(){
        return pos_cursor;
}

// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List
void List::moveFront(){
        pos_cursor = 0;
        beforeCursor = frontDummy;
        afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position size() in this List
void List::moveBack(){
        pos_cursor = size();
        beforeCursor = backDummy->prev;
        afterCursor = backDummy;
}

// peekNext()
// Returns the element after the cursor
// pre: position()<size()
int List::peekNext(){
        if(position()<size()){
                return afterCursor->data;
        }
        return -1;
}

// peekPrev()
// Returns the element before the cursor
// pre: position()>0
int List::peekPrev(){
        if(position()>0){
                return beforeCursor->data;
        }
        return -1;
}

// moveNext()
// Advances cursor to next higher position.  Returns the List element that was
// passed over.
// pre: position()<size()
int List::moveNext(){
        if(position()<size()){
                pos_cursor++;
                beforeCursor = afterCursor;
                afterCursor = afterCursor->next;
                return beforeCursor->data;
        }
        return -1;
}

// movePrev()
// Advances cursor to next lower position.  Returns the List element that was
// passed over.
// pre: position()>0
int List::movePrev(){
        if(position()>0){
                pos_cursor--;
                afterCursor = beforeCursor;
                beforeCursor = beforeCursor->prev;
                return afterCursor->data;
        }
        return -1;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(int x){
        Node* N = new Node(x);
        N->next = afterCursor;
        N->prev = beforeCursor;
        beforeCursor->next = N;
        afterCursor->prev = N;
        afterCursor = N;
        num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(int x){
        Node* N = new Node(x);
        N->next = afterCursor;
        N->prev = beforeCursor;
        beforeCursor->next = N;
        afterCursor->prev = N;
        beforeCursor = N;
        pos_cursor++;
        num_elements++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter(){
        if(position()<size()){
                Node* N = afterCursor;
                afterCursor = afterCursor->next;
                afterCursor->prev = beforeCursor;
                beforeCursor->next = afterCursor;
                num_elements--;
                delete N;
        }
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
        if(position()>0){
                Node* N = beforeCursor;
                beforeCursor = beforeCursor->prev;
                beforeCursor->next = afterCursor;
                afterCursor->prev = beforeCursor;
                num_elements--;
                pos_cursor--;
                delete N;
        }
}

// findNext()
// Starting from the current cursor position, performs a linear search (in the
// direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final cursor
// position.  If x is not found, places the cursor at position size(),
// and returns -1
int List::findNext(int x){
        while(afterCursor!=backDummy){
                if(moveNext()==x){
                        return position();
                }
        }
        return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position 0, and
// returns -1.
int List::findPrev(int x){
        while(beforeCursor!=frontDummy){
                if(movePrev()==x){
                        return pos_cursor;
                }
        }
        return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. The cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void List::cleanup(){
        int a, i, j, k;
        int arr[size()];
        Node *N, *M;
        N = frontDummy->next;
        j = 0;
        k = 0;
        while(N!=backDummy){
                a = 0; // handle if existing value was found
                for(i=0; i<j; i++){
                        if(arr[i]==N->data){
                                a = 1; // existing value was found
                                break;
                        }
                }
                if(a==1){
                        M = N->next;
                        if(afterCursor==N){
                                eraseAfter();
                        }else if(beforeCursor==N){
                                eraseBefore();
                        }else{
                                N->next->prev = N->prev;
                                N->prev->next = N->next;
                                num_elements--;
                                delete N;
                                if(k<=pos_cursor){
                                        pos_cursor--;
                                }
                        }
                        N = M;
                }else{
                        arr[j] = N->data;
                        j++;
                        N = N->next;
                }
                k++;
        }
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
        Node *N, *M;
        M = frontDummy->next;
        num_elements = 0;
        pos_cursor = 0;
        afterCursor = backDummy;
        beforeCursor = frontDummy;
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        while(M!=backDummy){
                N = M;
                M = M->next;
                delete N;
        }
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L){
        List M;
        Node *N;
        for(N=frontDummy->next; N!=backDummy; N=N->next){
                M.moveBack();
                M.insertAfter(N->data);
        }
        for(N=L.frontDummy->next; N!=L.backDummy; N=N->next){
                M.moveBack();
                M.insertAfter(N->data);
        }
        M.moveFront();
        return M;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string(){
        Node *N;
        std::string str("");
        for(N=frontDummy->next; N!=backDummy; N=N->next){
                if(N->prev!=frontDummy){
                        str.append(", ");
                }
                str.append(std::to_string(N->data));
        }
        return str;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R){
        bool eq = false;
        Node* N = frontDummy->next;
        Node* M = R.frontDummy->next;
        eq = (size()==R.num_elements);
        while(eq && N!=backDummy){
                eq = (N->data == M->data);
                N = N->next;
                M = M->next;
        }
        return eq;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, List& L ){
        return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged are unchanged.
bool operator==( List& A, const List& B ){
        return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
        if(this!=&L){
                List t = L;
                std::swap(frontDummy, t.frontDummy);
                std::swap(backDummy, t.backDummy);
                std::swap(beforeCursor, t.beforeCursor);
                std::swap(afterCursor, t.afterCursor);
                std::swap(pos_cursor, t.pos_cursor);
                std::swap(num_elements, t.num_elements);
        }

        return *this;
}
