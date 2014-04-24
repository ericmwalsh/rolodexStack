//
//  Stack.cc
//
//
//  Created by Eric Walsh on 4/3/14.
//
//

#include "Stack.h"
Stack::Stack(){
    buf = new char[STACK_CAPACITY];
}

Stack::~Stack(){
    delete buf;
}

bool Stack::isEmpty(){ //Big-O is O(1)
    return place==0;
}

bool Stack::isFull(){ //Big-O is O(1)
    return place==STACK_CAPACITY;
}

void Stack::push(char s){  //O(1)
    if(isFull()) cout << "Unable to execute push(string s) : Stack is full!" << endl;
    else buf[place++]=s;
}

char Stack::pop(){ //O(1)
    if(isEmpty()) cout << "Unable to execute pop() : Stack is empty!" << endl;
    else{
        char ans;
        ans = buf[--place];
        return ans;
    }
}

char Stack::top(){ //O(1)
    if(isEmpty()) cout << "Unable to execute top() : Stack is empty!" << endl;
    else return buf[place-1];
}

void Stack::print(){ //O(N)
    for(int i = 0; i<place; i++) cout << "Entry " << i << " : " << buf[i] << endl;
}


int main(){
    //for(;;){
    while(!cin.eof()){
        Stack * s = new Stack();
        string input;
        cin >> input;
        cout << "Your input was " << input << endl;
        for(int i=0; i<input.length(); i++) s->push(input[i]);
        cout << "Your input Stack-Reversed is ";
        while(!s->isEmpty()) cout << s->pop();
        cout << endl;
    }
    cout << "Control - D (EOF) input detected! Exiting program..." << endl;
    return 0;
}
