/*********************************************************************************
 * Raymond Huang, rhuang43
 * 2022 Spring CSE101 PA6
 * ListTest.cpp
 * Test file for List ADT
 *********************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"
using namespace std;
int main()
{
    List A, B;
    for (int i = 1; i < 10; i++)
    {
        A.insertAfter(i);
        B.insertAfter(11 - i);
    }
    A.moveBack();
    B.moveBack();
    A.movePrev();
    B.movePrev();
    A.moveFront();
    B.moveFront();
    A.moveNext();
    B.moveNext();
    A.eraseBefore();
    A.eraseAfter();
    B.eraseBefore();
    B.eraseAfter();
    A.setAfter(5);
    B.setBefore(1);
    A.peekPrev();
    B.peekPrev();
    A.peekNext();
    B.peekNext();
    A.front();
    B.front();
    cout << "position: " << A.position() << endl;
    cout << "length: " << A.length() << endl;
    cout << "position: " << B.position() << endl;
    cout << "length: " << B.length() << endl;
    List AB = A.concat(B);
    A.clear();
    B.clear();
    AB.clear();
}