/*********************************************************************************
 * Raymond Huang, rhuang43
 * 2022 Spring CSE101 PA7
 * List.cpp
 * Source file for List ADT
 *********************************************************************************/
#include <iostream>
#include <string>
#include "List.h"
using namespace std;
// Node constructor
List::Node::Node(long x)
{
    data = x;
    next = nullptr;
    prev = nullptr;
}
// List in empty State
List::List()
{
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    // making an empty list;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// copy constructor
List::List(const List &L)
{
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    // making an empty list;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node *N = L.frontDummy->next;
    while (N != L.backDummy)
    {
        // check if it is an empty list
        this->insertBefore(N->data);
        N = N->next;
    }
    this->moveFront();
}
// Destructor
List::~List()
{
    while (num_elements > 0)
    {
        this->clear();
    }
    delete frontDummy; // deletes something
    delete backDummy;
}

// Access functions --------------------------------------------------------

// Returns the length of this List.
int List::length() const
{
    return num_elements;
}
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const
{
    if (length() <= 0)
    {
        exit(EXIT_FAILURE);
    }
    return (frontDummy->data);
}
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const
{
    if (length() <= 0)
    {
        exit(EXIT_FAILURE);
    }
    return backDummy->data;
}
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const
{
    if (pos_cursor < 0)
    {
        exit(EXIT_FAILURE);
    }
    if (pos_cursor > num_elements)
    {
        exit(EXIT_FAILURE);
    }
    return pos_cursor;
}
// Returns the element after the cursor.
//  pre: position()<length()
ListElement List::peekNext() const
{
    if (pos_cursor >= length())
    {
        exit(EXIT_FAILURE);
    }
    return afterCursor->data;
}

// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const
{
    if (pos_cursor <= 0)
    {
        exit(EXIT_FAILURE);
    }
    return beforeCursor->data;
}
// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear()
{
    moveFront();
    while (num_elements > 0)
    {
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront()
{
    pos_cursor = 0;
    afterCursor = frontDummy->next;
    beforeCursor = frontDummy;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack()
{
    pos_cursor = num_elements;
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext()
{
    if (pos_cursor >= length())
    {
        exit(EXIT_FAILURE);
    }
    pos_cursor++;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev()
{
    if (pos_cursor <= 0)
    {
        exit(EXIT_FAILURE);
    }
    pos_cursor--;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x)
{
    Node *Holder = new Node(x);
    Holder->next = afterCursor;
    Holder->prev = beforeCursor;
    beforeCursor->next = Holder;
    afterCursor->prev = Holder;
    afterCursor = Holder;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x)
{
    Node *Holder = new Node(x);
    Holder->next = afterCursor;
    Holder->prev = beforeCursor;
    afterCursor->prev = Holder;
    beforeCursor->next = Holder;
    beforeCursor = Holder;
    num_elements++;
    pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x)
{
    if (position() >= length())
    {
        exit(EXIT_FAILURE);
    }
    afterCursor->prev->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x)
{
    if (position() <= 0)
    {
        exit(EXIT_FAILURE);
    }
    beforeCursor->next->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter()
{
    if (position() >= length())
    {
        exit(EXIT_FAILURE);
    }
    Node *Holder = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements--;
    delete Holder;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore()
{
    if (position() <= 0)
    {
        exit(EXIT_FAILURE);
    }
    Node *Holder = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    pos_cursor--;
    num_elements--;
    delete Holder;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x)
{
    while (afterCursor != backDummy)
    {
        if (afterCursor->data == x)
        {
            this->moveNext();
            return pos_cursor;
        }
        this->moveNext();
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x)
{
    while (beforeCursor != frontDummy)
    {
        if (beforeCursor->data == x)
        {
            this->movePrev();
            return pos_cursor;
        }
        this->movePrev();
    }
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup()
{
    Node *Checker = frontDummy->next;        // getting first pointer
    Node *Checking = frontDummy->next->next; // getting the second pointer
    int counter = 0;                         // how far we are into the list
    int count = 0;                          //how many times we traversed the list
    while (Checker != backDummy)
    {
        while (Checking != backDummy)
        { // checks the first pointer with the rest of the list
            if (Checker->data == Checking->data)
            {
                if(Checking == beforeCursor){
                    beforeCursor = Checking->prev;
                }
                if(Checking == afterCursor){
                    afterCursor = Checking->next;
                }
                Node *Holder;                // holds the node to be deleted if it is the same
                if (counter < pos_cursor)
                {
                    pos_cursor--;
                }
                Holder = Checking;
                Checking->prev->next = Checking->next;
                Checking->next->prev = Checking->prev;
                delete Holder;
                num_elements--;
            }
            Checking = Checking->next;
            counter++;
        }
        count++;
        counter = count;
        Checker = Checker->next;
        Checking = Checker->next;
    }
    delete Checker;
    delete Checking;
    // for (int i = 0; i < num_elements - 1;)
    // { // keeps track of how far we are in the list
    //     for (; afterCursor != backDummy; moveNext())
    //     { // moves the second pointer down the list
    //         if (Checker->data == afterCursor->data)
    //         {                 // checks if the element we are looking for is in the element
    //             if(pos_cursor < cursor){
    //                 cursor--;
    //             }
    //             eraseAfter(); // if it matches we delete it
    //         }
    //     }
    //     moveFront(); // move cursor back to the front
    //     i++;
    //     for (int j = 0; j <= i; j++)
    //     {
    //         Checker = afterCursor; // resets the element being checked to the next element in the list
    //         moveNext();            // moves the second pointer to next element being checked
    //     }
    // }
    // moveFront();
    // while(pos_cursor < cursor){
    //     moveNext();
    // }
    // delete Checker;
}
// have 2 pointers
// pointer 1 starts at 1
// pointer 2 starts at 2 (next element of pointer 1)
// pointer 1 moves through the whole list if it is equal remove
// same with pointer 2
// pointer 3 is undisclosed by the TA

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List &L) const
{
    List New_List;
    Node *tHolder = this->frontDummy->next; // gets the first element in the list
    Node *lHolder = L.frontDummy->next;
    while (tHolder != this->backDummy)
    { // loops till the last element
        New_List.insertBefore(tHolder->data);
        tHolder = tHolder->next;
    }
    while (lHolder != L.backDummy) // loops till the last element
    {
        New_List.insertBefore(lHolder->data);
        lHolder = lHolder->next;
    }
    New_List.moveFront();
    return New_List;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const
{
    // referenced the QUEUE.cpp file
    // std::string Queue::to_string() const{
    //    Node* N = nullptr;
    //    std::string s = "";

    //    for(N=front; N!=nullptr; N=N->next){
    //       s += std::to_string(N->data)+" ";
    //    }

    //    return s;
    // }
    Node *N = nullptr;
    string s = "(";
    N = frontDummy->next;
    for (N = frontDummy->next; N != backDummy->prev; N = N->next)
    {
        s += std::to_string(N->data) + ", ";
    }
    s += std::to_string(N->data) + ")";
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List &R) const
{
    // referenced QUEUE.cpp example
    // bool Queue::equals(const Queue& Q) const{
    //    bool eq = false;
    //    Node* N = nullptr;
    //    Node* M = nullptr;
    //    eq = ( this->length == Q.length );
    //    N = this->front;
    //    M = Q.front;
    //    while( eq && N!=nullptr){
    //       eq = (N->data==M->data);
    //       N = N->next;
    //       M = M->next;
    //    }
    //    return eq;
    // }
    Node *NR = nullptr;
    Node *N = nullptr;
    bool eq = false;
    eq = (this->num_elements == R.num_elements);
    NR = R.frontDummy->next;
    N = this->frontDummy->next;
    while (eq && N != this->backDummy)
    {
        eq = (N->data == NR->data);
        N = N->next;
        NR = NR->next;
    }
    return eq;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream &operator<<(std::ostream &stream, const List &L)
{
    // referenced QUEUE.cpp example
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==(const List &A, const List &B)
{
    // referenced QUEUE.cpp example
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List &List::operator=(const List &L)
{
    // referenced QUEUE.cpp example
    if (this != &L)
    {
        List Holder = L;
        std::swap(frontDummy, Holder.frontDummy);
        std::swap(backDummy, Holder.backDummy);
        std::swap(num_elements, Holder.num_elements);
    }
    return *this;
}

// put list nodes into new list in copy constructor
// friend type dont need LIST::
// cursor points to elements instead of ontop of a node
// frontdummy points to the point in memory before the front
// backdummy points to the point in memory after the last element
// this->data = L->data is wrong, data is not a node.
