/**--------------------------------------------------
 * 
 * $id$
 * Stack.h 
 * Version : 1.0
 * Author : Vedant Ashish Saboo CS19B074
 * 
 * Created -- 09:52 AM 2/23/2021
 * Last Modified :
 * 
 * Bugs :
 **---------------------------------------------------*/

#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

/**
 * class StackNode
 */
class StackNode {
    private:
    int data;
    StackNode* next;
    friend class Stack;
};

/**
 * class Stack
 * public methods: top, pop, push, isEmpty
 */
class Stack {
    private:
    StackNode* tos;
    const static int ERR = -1;
    public:
    Stack() {
        tos = NULL;
    }
    int top();
    int pop();
    void push(int);
    bool isEmpty();
};

#endif