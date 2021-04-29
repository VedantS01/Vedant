/**
 *  FILE            :           CacheLRUP.cpp
 *  PURPOSE         :           Contains implementations of class CacheLRUP which are a part of the cache simulator
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
 *  BEGIN Implementation of class CacheLRUP
 **/
void CacheLRUP::initLruTree()
    {
        int n = numWays;
        lruDepth = 0;
        while (n > 1)
        {
            n = n >> 1;
            lruDepth++;
        }
        for (int i = 0; i < numSets; i++)
        {
            lruTree[i] = vector<int>(numWays - 1, LEFT);
            for (int j = 0; j < numWays; j++)
            {
                lruTree[i].push_back(j);
            }
        }
    }

//find the replace position for a new block to come in in case of a cache miss
int CacheLRUP::replacePosition(int s)
    {
        int l = 0;
        for (int i = 0; i < lruDepth; i++)
        {
            if (lruTree[s][l] == LEFT)
            {
                l = l * 2 + 1;
            }
            else
            {
                l = l * 2 + 2;
            }
        }
        return lruTree[s][l];
    }

//update the contents of lru tree after a cache memory access
void CacheLRUP::afterOperation(int s, int pos)
    {
        for (int i = 0; i < lruDepth; i++)
        {
            if (pos % 2 == LEFT)
            {
                pos = (pos - 1) >> 1;
                lruTree[s][pos] = LEFT;
            }
            else
            {
                pos = (pos - 1) >> 1;
                lruTree[s][pos] = RIGHT;
            }
        }
    }

//findR: a function to retrieve a block from cache to read, if not, retrieve from memory
bool CacheLRUP::findR(type_tag t, int s)
    {
        for (int i = 0; i < numWays; i++)
        {
            if (!sets[s][i].valid)
            {
                continue;
            }
            if (sets[s][i].tag == t)
            {
                //a hit!
                cache_hits++;
                afterOperation(s, i + numWays - 1);
                return true;
            }
        }
        //a miss!
        cache_misses++;
        int i = replacePosition(s);
        CacheBlock *cb = &sets[s][i];
        if (cb->valid)
        {
            fullArray[s] = true;
            delete cb->pointer;
            if (cb->dirty)
            {
                dirty_blocks_evicted++;
            }
        }
        cb->tag = t;
        cb->valid = true;
        cb->dirty = false;
        cb->pointer = new Block;
        afterOperation(s, i + numWays - 1);

        //TODO: update the fullArray
        /*
        bool f = true;
        for(int i = 0; i < numWays; i++) {
            if(!sets[s][i].valid) f = false;
        }
        fullArray[s] = f;
        */
        return false;
    }

//findW: a function to retrieve a block from cache to write, if not, retrieve from memory    
bool CacheLRUP::findW(type_tag t, int s)
    {
        for (int i = 0; i < numWays; i++)
        {
            if (!sets[s][i].valid)
            {
                continue;
            }
            if (sets[s][i].tag == t)
            {
                //a hit!
                cache_hits++;
                sets[s][i].dirty = true;
                afterOperation(s, i + numWays - 1);
                return true;
            }
        }
        //a miss!
        cache_misses++;
        int i = replacePosition(s);
        CacheBlock *cb = &sets[s][i];
        if (cb->valid)
        {
            fullArray[s] = true;
            delete cb->pointer;
            if (cb->dirty)
            {
                dirty_blocks_evicted++;
            }
        }

        cb->tag = t;
        cb->valid = true;
        cb->dirty = true;
        cb->pointer = new Block;
        afterOperation(s, i + numWays - 1);

        return false;
    }

/**
 * END Implementation of class CacheLRUP
 * 
 * END of file
 * 
 **/