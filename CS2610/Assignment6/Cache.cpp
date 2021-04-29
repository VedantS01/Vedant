/**
 *  FILE            :           Cache.pp
 *  PURPOSE         :           Contains implementations of classes Cache and CacheBlock which are a part of the cache simulator
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

#include <iostream>
#include <fstream>
#include <cmath>
#include "Cache.h"
using namespace std;

/**
 * Implementation of methods of class CacheBlock
 **/
CacheBlock::CacheBlock(int blockSize)
    {
        this->blockSize = blockSize;
        dirty = false;
        valid = false;
    }
CacheBlock::~CacheBlock()
    {
    }
/**
 * END class CacheBlock
 **/

/**
 * Implementation of methods of class Cache
 **/
//Constructor of class Cache
Cache::Cache(int cacheSize1, int blockSize1, int associativity1)
    {
        //set class parameters
        cacheSize = cacheSize1;
        blockSize = blockSize1;
        associativity = associativity1;
        if (associativity != 0)
        {
            numWays = associativity;
        }
        else
            numWays = cacheSize / blockSize;
        numSets = cacheSize / blockSize / numWays;

        //reset global parameters
        cache_hits = 0;
        cache_misses = 0;
        total_memory_refs = 0;
        read_accesses = 0;
        write_accesses = 0;
        compulsory_misses = 0;
        capacity_misses = 0;
        conflict_misses = 0;
        read_misses = 0;
        write_misses = 0;
        dirty_blocks_evicted = 0;

        //allocate space for cache structure
        sets = new deque<CacheBlock>[numSets];
        fullArray = vector<bool>(numSets, false);
        for (int i = 0; i < numSets; i++)
        {
            for (int j = 0; j < numWays; j++)
                sets[i].push_back(CacheBlock(blockSize));
        }
    }

//process a request 'dec'
bool Cache::access(long long int dec)
    {
        total_memory_refs++;
        //split msb bit as wr
        int wr = dec >> 31;
        type_tag tag = (type_tag)dec & 0x7fffffff;
        int w = 0, b = blockSize;
        while (b > 1)
        {
            b = b >> 1;
            w++;
        }
        //split the block offset from the remaining query bits
        int blockOffset = tag % blockSize;
        tag = (type_tag)tag >> w;
        b = numSets;
        w = 0;
        while (b > 1)
        {
            b = b >> 1;
            w++;
        }
        //split the set index from the remaining query bits
        int setIndex = tag % numSets;
        tag = (type_tag)tag >> w;
        
        //what is now left is tag value

        if (wr == 1)
        {
            write_accesses++;
            return write(tag, setIndex, blockOffset);
        }
        else
        {
            read_accesses++;
            return read(tag, setIndex, blockOffset);
        }
        return true;
    }
//process read request
bool Cache::read(type_tag t, int s, int b)
    {
        bool hit = findR(t, s);
        if (!hit)
            read_misses++;
        return hit;
    }

//process write request
bool Cache::write(type_tag t, int s, int b)
    {
        bool hit = findW(t, s);
        if (!hit)
            write_misses++;
        return hit;
    }

//return true if cache is full, else return null
bool Cache::full()
    {
        for (int i = 0; i < numSets; i++)
        {
            if (!fullArray[i])
                return false;
        }
        return true;
    }

//findR: a function to retrieve a block from cache to read, if not, retrieve from memory
bool Cache::findR(type_tag t, int s)
    {
        for (int i = 0; i < numWays; i++)
        {
            if (!sets[s][i].valid)
            {
                //a miss!
                cache_misses++;
                if (i == numWays - 1)
                {
                    fullArray[s] = true;
                }
                CacheBlock cb = sets[s].back();
                sets[s].pop_back();
                cb.tag = t;
                cb.valid = true;
                cb.dirty = false;
                cb.pointer = new Block;
                sets[s].push_front(cb);
                return false;
            }
            if (sets[s][i].tag == t)
            {
                //a hit!
                cache_hits++;
                return true;
            }
        }
        //a miss!
        cache_misses++;
        //randomset is a randimised integer value from 0 to numWays - 1 (both inclusive)
        int randomset = rand() % numWays ;
        CacheBlock cb = sets[s][randomset];
        delete cb.pointer;
        if (cb.dirty)
        {
            dirty_blocks_evicted++;
        }
        sets[s].erase(sets[s].begin() + randomset);
        cb.tag = t;
        cb.valid = true;
        cb.dirty = false;
        cb.pointer = new Block;
        sets[s].push_front(cb);
        return false;
    }

//findW: a function to retrieve a block from cache to write, if not, retrieve from memory
bool Cache::findW(type_tag t, int s)
    {
        for (int i = 0; i < numWays; i++)
        {
            if (!sets[s][i].valid)
            {
                //a miss!
                cache_misses++;
                if (i == numWays - 1)
                {
                    fullArray[s] = true;
                }
                CacheBlock cb = sets[s].back();
                sets[s].pop_back();
                cb.tag = t;
                cb.valid = true;
                cb.dirty = true;
                cb.pointer = new Block;
                sets[s].push_front(cb);
                return false;
            }
            if (sets[s][i].tag == t)
            {
                //a hit!
                cache_hits++;
                sets[s][i].dirty = true;
                return true;
            }
        }
        //a miss!
        cache_misses++;
        //randomset is a randimised integer value from 0 to numWays - 1 (both inclusive)
        int randomset = rand() % numWays ;
        CacheBlock cb = sets[s][randomset];
        delete cb.pointer;
        if (cb.dirty)
        {
            dirty_blocks_evicted++;
        }
        sets[s].erase(sets[s].begin() + randomset);
        cb.tag = t;
        cb.valid = true;
        cb.dirty = true;
        cb.pointer = new Block;
        sets[s].push_front(cb);
        return false;
    }

//translator function from hexadecimal string to decimal value
long long int Cache::HexToDec(string hex)
    {
        long long int dec = 0;
        for (auto i = hex.begin(); i != hex.end(); i++)
        {
            int deci = *i <= '9' ? *i - '0' : *i - 'a';
            dec = dec * 16 + deci;
        }
        return dec;
    }

/**
 * END of file
 **/
