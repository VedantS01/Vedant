/**
 *  FILE            :           Cache.h
 *  PURPOSE         :           Contains declarations of various classes which are a part of the cache simulator
 *  
 *  VERSION         :           1.2.1
 *  DATE CREATED    :           2021 March, 18 10:51 PM
 *  LAST MODIFIED   :           2021 March, 28 10:41 AM by Vedant
 * 
 *  AUTHOR(S)       :           Vedant Saboo (CS19B074)
 *                  :           Sanchit Gupta (CS19B071)
 *                  :           Parth Ajmera (CS19B065)
 * 
 **/

#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

typedef short unsigned int int_16;
typedef bool bit;
typedef long long int type_tag;
#define BYTE_ADDRESSING 8
#define MEMORY_SIZE 0x80000000 //size in bytes

extern int cache_misses;
extern int cache_hits;
extern int total_memory_refs;
extern int read_accesses;
extern int write_accesses;
extern int compulsory_misses;
extern int capacity_misses;
extern int conflict_misses;
extern int read_misses;
extern int write_misses;
extern int dirty_blocks_evicted;

class Block
{
public:
    bit *addr;
    int_16 addrSize;
    bit *data[BYTE_ADDRESSING];
    int_16 dataSize;
};

class CacheBlock
{
public:
    bool dirty;
    bool valid;
    type_tag tag;
    int blockSize;
    Block *pointer;
    CacheBlock(int blockSize);
    ~CacheBlock();
};

/**
 *  class Cache     :       Cache with flexible blockSize, cacheSize and associativity, with applied random replacement policy
 **/
class Cache
{
public:
    int blockSize;
    int cacheSize;
    int numSets;
    int numWays;
    int associativity;
    static const int replacementPolicy = 0; //random replacement policy
    vector<bool> fullArray;
    deque<CacheBlock> *sets;
    /*
    void print()
    {
        for (int i = 0; i < numSets; i++)
        {
            for (int j = 0; j < numWays; j++)
            {
                if (!sets[i][j].valid)
                    cout << "INVALID"
                         << " ";
                else
                    cout << sets[i][j].tag << " ";
            }
            cout << endl;
        }
    }*/
    Cache(int cacheSize1, int blockSize1, int associativity1);
    bool access(long long int dec);
    bool read(type_tag t, int s, int b);
    bool write(type_tag t, int s, int b);
    bool full();
    virtual bool findR(type_tag t, int s);
    virtual bool findW(type_tag t, int s);

protected:
    long long int HexToDec(string hex);
};

/**
 *  class CacheLRU  :       Cache with flexible blockSize, cacheSize and associativity, with applied least recently used replacement policy
 **/
class CacheLRU : public Cache
{
public:
    static const int replacementPolicy = 1; //lru replacement policy
    CacheLRU(int cacheSize1, int blockSize1, int associativity1) : Cache(cacheSize1, blockSize1, associativity1) {}
    bool findR(type_tag t, int s);
    bool findW(type_tag t, int s);
};

/**
 *  class CacheLRUP :       Cache with flexible blockSize, cacheSize and associativity, with applied pseudo least recently used replacement policy
 **/
class CacheLRUP : public Cache
{
public:
    vector<vector<int>> lruTree;
    const int LEFT = 0;
    const int RIGHT = 1;
    static const int replacementPolicy = 2; //pseudo lru replacement policy
    int lruDepth;
    void initLruTree();
    int replacePosition(int s);
    void afterOperation(int s, int pos);
    CacheLRUP(int cacheSize1, int blockSize1, int associativity1) : Cache(cacheSize1, blockSize1, associativity1)
    {
        // if (associativity != 0)
        // {
        //     numWays = associativity;
        // }
        // else
        //     numWays = cacheSize / blockSize;
        // numSets = cacheSize1 / blockSize1 / numWays;
        // cache_hits = 0;
        // cache_misses = 0;
        // total_memory_refs = 0;
        // read_accesses = 0;
        // write_accesses = 0;
        // compulsory_misses = 0;
        // capacity_misses = 0;
        // conflict_misses = 0;
        // read_misses = 0;
        // write_misses = 0;
        // dirty_blocks_evicted = 0;
        // sets = new deque<CacheBlock> [numSets];
        // fullArray = vector<bool> (numSets, false);
        // for(int i = 0; i < numSets; i++) {
        //     for(int j = 0; j < numWays; j++)
        //         sets[i].push_back(CacheBlock(blockSize));
        // }
        lruTree = vector<vector<int>>(numSets);
        initLruTree();
    }
    bool findR(type_tag t, int s);
    bool findW(type_tag t, int s);
};

/**
 * END OF CLASS DECLARATIONS
 **/
#endif

/**
 * END of file
 **/
