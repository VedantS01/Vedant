/******
 * 
 *  CacheBlock.cpp  -- contains definition of member functions of the class
 * 
 *  Author          -- Vedant Saboo (CS19b074)
 * 
 *****/

#include <iostream>
using namespace std;

#include "Cache.h"

CacheBlock::CacheBlock(int_16 n) { //enter n in units of Bytes
    tagSize = n * 8;
    tag = new bit[tagSize];
    valid = false;
    dirty = false;
}
CacheBlock::CacheBlock(int_16 n, Block* block) { //enter n in units of Bytes
    tagSize = n * 8;
    tag = new bit[tagSize];
    dataBlock = block;
    valid = true;
    dirty = false;
}
CacheBlock::~CacheBlock() {
    delete[] tag;
    valid = false;
}