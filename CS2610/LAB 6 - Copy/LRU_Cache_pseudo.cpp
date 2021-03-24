#ifndef LRU_CACHE_PSEUDO
#define LRU_CACHE_PSEUDO

#include <iostream>
#include <fstream>
using namespace std;
#include "Cache.cpp"

class LRU_Cache_Pseudo : public Cache {
    public:
    class Set {
        public:
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
            CacheBlock();
        };

        //TODO://
        int* lruTree;
        int depth;

        CacheBlock* blocks;
        int numWays;
        int index;
        int blockSize;
        Set() {

        }
        Set(int index, int numWays, int blockSize) {
            this->index = index;
            this->numWays = numWays;
            blocks = new CacheBlock[numWays];
            for(int i = 0; i < numWays; i++) {
                blocks[i] = CacheBlock(blockSize);
            }

            //init_lru_tree
            initLRUTree();
        }
        bool full() {
            for(int i = 0; i < numWays; i++) {
                if(!blocks[i].valid) return false;
            }
            return true;
        }
        void print(ofstream& fout) {
            for(int i = 0; i < numWays; i++) {
                if(blocks[i].valid) fout << blocks[i].tag << " ";
                else
                    fout << "INVALID" << " ";
            }
            fout << endl;
        }
        void initLRUTree() {
            int n = numWays;
            depth = 0;
            while(n > 1) {
                n >> 2;
                depth++;
            }
            lruTree = new int[2*numWays - 1];
            int i;
            for(i = 0; i < numWays - 1; i++) {
                lruTree[i] = 0;
            }
            while(i < 2*numWays - 1) {
                lruTree[i] = i - numWays + 1 ;
                i++;
            }
        }
        CacheBlock* operator[] (int at) {
            return &blocks[at];
        }
        int replacePosition() {
            int l = 0;
            for(int i = 0; i < depth; i++) {
                if(lruTree[l] == 0) {
                    l = l * 2 + 1;
                } else {
                    l = l * 2 + 2;
                }
            }
            return lruTree[l];
        }
        void afterOperation(int pos) {
            for(int i = 0; i < depth; i++) {
                if(pos % 2 == 0) {
                    pos = pos >> 2;
                    lruTree[pos] = 0;
                } else {
                    pos = pos >> 2;
                    lruTree[pos] = 1;
                }
            }
        }
        bool find(type_tag tag, bool read) {
            if(numWays = 1) {
                if(blocks[0].tag == tag) {
                    //a hit!
                    cache_hits++;
                    if(!read) blocks[0].dirty = true;
                    return true;
                } else {
                    //a miss
                    cache_misses++;
                    if(blocks[0].valid) evict(0);
                    if(read) read_misses++;
                    else write_misses++;
                    blocks[0].tag = tag;
                    blocks[0].valid = true;
                    blocks[0].dirty = false;
                    blocks[0].pointer = new Block;
                    return false;
                }
            }
            for(int i = 0; i < numWays; i++) {
                if(!blocks[i].valid) {
                    continue;
                }
                if(blocks[i].tag == tag) {
                //a hit!
                    cache_hits++;
                    if(!read) {
                        //write to block pointed to by *cb
                        blocks[i].dirty = true;
                    }
                    afterOperation(i + numWays - 1);
                    return true;
                    //return cb;
                }
            }
            //miss;
            //evict();
            cache_misses++;
            if(read) read_misses++;
            else write_misses++;
            //get replaceable position for the blocks
            int i = replacePosition();
            if(blocks[i].valid) {
                evict(i);
            }
            blocks[i].tag = tag;
            blocks[i].valid = true;
            blocks[i].pointer = new Block;
            blocks[i].dirty = false;
            afterOperation(i + numWays - 1);
            return false;
        }
        void evict(int i) {
            if(blocks[i].dirty) {
                dirty_blocks_evicted++;
            }
            blocks[i].valid = false;
            blocks[i].tag = 0;
            blocks[i].dirty = false;
        }
        bool write(type_tag t, int b) {
            return find(t, false);
            //write in cb, at block offset b
        }
        bool read(type_tag t, int b) {
            return find(t, true);
            //read from cb, at block offset b
        }
    };
    

};

#endif