/**
 *  FILE            :           CacheLRU.cpp
 *  PURPOSE         :           Contains implementations of class CacheLRU which are a part of the cache simulator
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
 *  BEGIN Implementation of class CacheLRU
 **/
//findR: a function to retrieve a block from cache to read, if not, retrieve from memory
bool CacheLRU::findR(type_tag t, int s)
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
                CacheBlock cb = sets[s][i];
                sets[s].erase(sets[s].begin() + i);
                sets[s].push_front(cb);
                return true;
            }
        }
        //a miss!
        cache_misses++;
        CacheBlock cb = sets[s].back();
        delete cb.pointer;
        if (cb.dirty)
        {
            dirty_blocks_evicted++;
        }
        sets[s].pop_back();
        cb.tag = t;
        cb.valid = true;
        cb.dirty = false;
        cb.pointer = new Block;
        sets[s].push_front(cb);
        return false;
    }

//findW: a function to retrieve a block from cache to write, if not, retrieve from memory
bool CacheLRU::findW(type_tag t, int s)
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
                CacheBlock cb = sets[s][i];
                cb.dirty = true;
                sets[s].erase(sets[s].begin() + i);
                sets[s].push_front(cb);
                return true;
            }
        }
        //a miss!
        cache_misses++;
        CacheBlock cb = sets[s].back();
        delete cb.pointer;
        if (cb.dirty)
        {
            dirty_blocks_evicted++;
        }
        sets[s].pop_back();
        cb.tag = t;
        cb.valid = true;
        cb.dirty = true;
        cb.pointer = new Block;
        sets[s].push_front(cb);
        return false;
    }

/**
 * END Implementation of class CacheLRU
 * 
 * END of file
 **/