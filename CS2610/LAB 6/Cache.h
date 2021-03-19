/******************************************
 *  Cache.h         :       Contains definition of structures and functions used to create the cache simulator
 *  
 *  Author          :       Vedant Saboo (CS19B074) ; Sanchit Gupta (CS19B071) ; Parth AJmera (CS19B065)
 *  Version         :       1.0.0
 *  Created         :       10:13 AM 3/19/2021
 *  Last Modified   :       10:14 AM 3/19/2021 by Vedant
 * 
 ******************************************/

#include <iostream>
#include <string>
#include "MainMemory.h"
using namespace std;
typedef short unsigned int int_16;
typedef bool bit;
#define BYTE_ADDRESSING 8

//define cache block
/**
 *  class CacheBlock    --  contains information about the cache block, and various support bits
 *  Author              --  Vedant Saboo (CS19b074)
 **/
class CacheBlock{
    public:
    bit* tag;
    int_16 tagSize;
    bit valid;
    bit dirty;
    Block* dataBlock;
    CacheBlock(int_16);         //argument unit in bytes
    CacheBlock(int_16, Block*); //argument unit in bytes, and pointer to the data allocation
    ~CacheBlock();
    //other methods go here
};



typedef struct SetWrapper {
    public:
    CacheBlock cacheBlock; //cache block
    CacheBlock* next; //the next cache block
} SetWrapper;

