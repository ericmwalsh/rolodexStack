//
//  Stack.h
//
//
//  Created by Eric Walsh on 4/3/14.
//
//
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#define STACK_CAPACITY 1000


#ifndef ____Stack__
#define ____Stack__
class Stack
{
    int place = 0;
    char * buf;
public:
    Stack();
    void push(char c);
    char pop();
    char top();
    bool isEmpty();
    bool isFull();
    ~Stack();
    void print();
};


#endif // ____Stack__
