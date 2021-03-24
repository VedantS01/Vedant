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

class Block {
    public:
    bit* addr;
    int_16 addrSize;
    bit* data[BYTE_ADDRESSING];
    int_16 dataSize;
};

class CacheBlock {
            public:
            bool dirty;
            bool valid;
            type_tag tag;
            int blockSize;
            Block* pointer;
            CacheBlock(int blockSize) {
                this->blockSize = blockSize;
                dirty = false;
                valid = false;
            }
            ~CacheBlock() {
                
            }
        };

// cache with random replacement policy;
class Cache {
    public:
    int blockSize;
    int cacheSize;
    int numSets;
    int numWays;
    int associativity;
    static const int replacementPolicy = 0;
    vector<bool> fullArray;
    deque<CacheBlock>* sets;
    void print() {
        for(int i = 0; i < numSets; i++) {
            for(int j = 0; j < numWays; j ++) {
                if(!sets[i][j].valid)
                    cout << "INVALID" << " ";
                else
                    cout << sets[i][j].tag << " ";
            }
            cout << endl;
        }
    }
    virtual void initialise() {
        if(associativity != 0) {
            numWays = associativity;
        } else 
            numWays = cacheSize / blockSize ;
        numSets = cacheSize / blockSize / numWays ;
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
        sets = new deque<CacheBlock> [numSets];
        fullArray = vector<bool> (numSets, false);
        for(int i = 0; i < numSets; i++) {
            for(int j = 0; j < numWays; j++)
                sets[i].push_back(CacheBlock(blockSize));
        }
    }
    bool access(string hex) {
        //TODO: improve
        total_memory_refs++;
        long long int dec = HexToDec(hex);
        int wr = dec / MEMORY_SIZE;
        type_tag tag = (type_tag) dec % MEMORY_SIZE;
        int blockOffset = tag % blockSize;
        tag = (type_tag) tag / blockSize;
        int setIndex = tag % numSets;
        tag = (type_tag) tag / numSets;
        if(wr == 1) {
            write_accesses++;
            return write(tag, setIndex, blockOffset);
        } else {
            read_accesses++;
            return read(tag, setIndex, blockOffset);
        }
        return true;
    }
    bool read(type_tag t, int s, int b) {
        bool hit = findR(t, s);
        if(!hit) read_misses++;
        return hit;
    }
    bool write(type_tag t, int s, int b) {
        bool hit = findW(t, s);
        if(!hit) write_misses++;
        return hit;
    }
    bool full() {
        for(int i = 0; i < numSets; i++) {
            if(!fullArray[i]) return false;
        }
        return true;
    }
    //FIFO
    //TODO: Randomise
    virtual bool findR(type_tag t, int s) {
        for(int i = 0; i < numWays; i++) {
            if(! sets[s][i].valid) {
                //a miss!
                cache_misses++;
                if(i == numWays - 1) {
                    fullArray[i] = true;
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
            if(sets[s][i].tag == t) {
                //a hit!
                cache_hits++;
                return true;
            }
        }
        //a miss!
        cache_misses++;
        CacheBlock cb = sets[s].back();
        delete cb.pointer;
        if(cb.dirty) {
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
    virtual bool findW(type_tag t, int s) {
        for(int i = 0; i < numWays; i++) {
            if(! sets[s][i].valid) {
                //a miss!
                cache_misses++;
                if(i == numWays - 1) {
                    fullArray[i] = true;
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
            if(sets[s][i].tag == t) {
                //a hit!
                cache_hits++;
                sets[s][i].dirty = true;
                return true;
            }
        }
        //a miss!
        cache_misses++;
        CacheBlock cb = sets[s].back();
        delete cb.pointer;
        if(cb.dirty) {
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
    protected:
    long long int HexToDec(string hex) {
        long long int dec = 0;
        for(auto i = hex.begin(); i != hex.end(); i++) {
            int deci = *i <= '9' ? *i - '0' : *i - 'a';
            dec = dec * 16 + deci;
        }
        return dec;
    }
};

class CacheLRU : public Cache {
    public:
    static const int replacementPolicy = 1;
    bool findR(type_tag t, int s) {
        for(int i = 0; i < numWays; i++) {
            if(! sets[s][i].valid) {
                //a miss!
                cache_misses++;
                if(i == numWays - 1) {
                    fullArray[i] = true;
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
            if(sets[s][i].tag == t) {
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
        if(cb.dirty) {
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
    bool findW(type_tag t, int s) {
        for(int i = 0; i < numWays; i++) {
            if(! sets[s][i].valid) {
                //a miss!
                cache_misses++;
                if(i == numWays - 1) {
                    fullArray[i] = true;
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
            if(sets[s][i].tag == t) {
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
        if(cb.dirty) {
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
};

class CacheLRUP : public Cache {
    public:
    vector< vector <int>> lruTree;
    const int LEFT = 0;
    const int RIGHT = 1;
    static const int replacementPolicy = 2;
    int lruDepth;
    void initLruTree() {
        int n = numWays;
            lruDepth = 0;
            while(n > 1) {
                n = n >> 1;
                lruDepth++;
            }
            //0 0 0 0 1 2 3
        for(int i = 0; i < numSets; i++) {
            lruTree[i] = vector<int> (numWays - 1, LEFT) ;
            for(int j = 0; j < numWays; j++) {
                lruTree[i].push_back(j);
            }
        }
    }
    int replacePosition(int s) {
            int l = 0;
            for(int i = 0; i < lruDepth; i++) {
                if(lruTree[s][l] == LEFT) {
                    l = l * 2 + 1;
                } else {
                    l = l * 2 + 2;
                }
            }
            return lruTree[s][l];
        }
    void afterOperation(int s, int pos) {
        for(int i = 0; i < lruDepth; i++) {
            if(pos % 2 == LEFT) {
                pos = (pos - 1) >> 1;
                lruTree[s][pos] = LEFT;
            } else {
                pos = (pos - 1 )>> 1;
                lruTree[s][pos] = RIGHT;
            }
        }
    }
    void initialise() {
        if(associativity != 0) {
            numWays = associativity;
        } else 
            numWays = cacheSize / blockSize ;
        numSets = cacheSize / blockSize / numWays ;
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
        sets = new deque<CacheBlock> [numSets];
        fullArray = vector<bool> (numSets, false);
        for(int i = 0; i < numSets; i++) {
            for(int j = 0; j < numWays; j++)
                sets[i].push_back(CacheBlock(blockSize));
        }
        lruTree = vector< vector <int>> (numSets) ;
        initLruTree();
    }
    bool findR(type_tag t, int s) {
        for(int i = 0; i < numWays; i++) {
            if(! sets[s][i].valid) {
                continue;
            } 
            if(sets[s][i].tag == t) {
                //a hit!
                cache_hits++;
                afterOperation(s, i + numWays - 1);
                return true;
            }
        }
        //a miss!
        cache_misses++;
        int i = replacePosition(s);
        CacheBlock* cb = &sets[s][i];
        if(cb->valid) {
            fullArray[s] = true;
            delete cb->pointer;
            if(cb->dirty) {
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
    bool findW(type_tag t, int s) {
        for(int i = 0; i < numWays; i++) {
            if(! sets[s][i].valid) {
                continue;
            } 
            if(sets[s][i].tag == t) {
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
        CacheBlock* cb = &sets[s][i];
        if(cb->valid) {
            fullArray[s] = true;
            delete cb->pointer;
            if(cb->dirty) {
                dirty_blocks_evicted++;
            }
        }
        
        cb->tag = t;
        cb->valid = true;
        cb->dirty = false;
        cb->pointer = new Block;
        afterOperation(s, i + numWays - 1);

        
        return false;
    }
};

#endif

