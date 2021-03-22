/******
 * 
 *  Set.cpp         -- contains definition of member functions of the class Set
 * 
 *  Author          -- Vedant Saboo (CS19b074)
 * 
 *****/

#include <iostream>
using namespace std;

#include "Cache.h"

Set::Set(int_16 w) {
    set->next = NULL;
    CacheBlock* cb;
    for(int i = 0; i < w; i++) {
        cb = new CacheBlock(blockSize);
        cb->next = set->next;
        set->next = cb;
    }
}