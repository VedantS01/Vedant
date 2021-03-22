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

CacheBlock::CacheBlock(type_tag t) { //enter n in units of Bytes
    tag = t;
    valid = true;
    dirty = false;
}
CacheBlock::CacheBlock() {
    valid = false;
    dirty = false;
}
CacheBlock::CacheBlock(type_tag t, Block* block) { //enter n in units of Bytes
    tag = t;
    dataBlock = block;
    valid = true;
    dirty = false;
}
CacheBlock::~CacheBlock() {
    valid = false;
}