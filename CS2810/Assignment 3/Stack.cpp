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

#include <iostream>
#include "Stack.h"
using namespace std;

/**
 * Begin implementation of class Stack Methods
 **/
int Stack::top() { //returns value stored at the top of the stack
    if(!isEmpty()) {
        return tos->data;
    }
    return ERR;
}
int Stack::pop() { //deletes an element from the top and returns its value
    StackNode* temp = tos->next;
    int retValue = tos->data;
    delete tos;
    tos = temp;
    return retValue;
}
void Stack::push(int val) { //inserts an element in the stack
    StackNode* temp = new StackNode;
    temp->data = val;
    temp->next = tos;
    tos = temp;
}
bool Stack::isEmpty() { //checks whether the stack is empty.
    return tos == NULL;
}
/**
 * End of class Stack implementation
 **/