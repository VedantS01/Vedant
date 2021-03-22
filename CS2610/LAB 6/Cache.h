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
typedef long long int type_tag;
#define BYTE_ADDRESSING 8

//define cache block
/**
 *  class CacheBlock    --  contains information about the cache block, and various support bits
 *  Author              --  Vedant Saboo (CS19b074)
 **/
class CacheBlock{
    public:
    type_tag tag;
    bit valid;
    bit dirty;
    Block* dataBlock;
    CacheBlock* next;
    //CacheBlock* prev; //if need be
    CacheBlock(type_tag);         //argument unit in bytes
    CacheBlock(type_tag, Block*); //argument unit in bytes, and pointer to the data allocation
    CacheBlock();
    ~CacheBlock();
    //other methods go here
};


//a set wrapper, to aide link lists
/**
 *  struct SetWrapper   --  creates wrapper for CacheBlock to be used in a linked list Set
 *  Author              --  Vedant Saboo (CS19b074)
 **/
typedef struct SetWrapper {
    public:
    CacheBlock cacheBlock; //cache block
    CacheBlock* next; //the next cache block
} SetWrapper;

//a set as a linked list of cache blocks
/**
 *  class Set           --  a linked list of cache blocks with random replacement policy
 *  Author              --  Vedant Saboo (CS19b074)
 **/
class Set {
    public:
    CacheBlock* set;
    int_16 ways;
    Set(int_16);
    Block& get(type_tag);
    Block& evict();
};

class Cache {
    public:
    int cacheSize; //in bytes
    int blockSize; //in bytes
    int associativity; //number of ways
    int replacementPolicy; 
    int numSets;
    int numWays;
    CacheBlock** sets;
    void intialise();
    void access(int, type_tag , int, int);
    void read(type_tag, int, int);
    void write(type_tag, int, int);
    CacheBlock* get(type_tag, int, int); // a cache miss
    void evict();
};
