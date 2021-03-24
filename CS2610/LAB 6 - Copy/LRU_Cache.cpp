#ifndef LRU_CACHE_CPP
#define LRU_CACHE_CPP

#include <iostream>
using namespace std;
#include <fstream>
#include "Cache.cpp"

class LRU_Cache : public Cache {
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
            CacheBlock* next;
            CacheBlock* prev;
            CacheBlock(int blockSize) {
                this->blockSize = blockSize;
                dirty = false;
                valid = false;
                next = NULL;
               prev = NULL;
            }
        };
        CacheBlock* head;
        CacheBlock* tail;
        int numWays;
        int index;
        int blockSize;
        bool full() {
            CacheBlock* cb = head->next;
            for(int i = 0; i < numWays; i++) {
                if(!cb->valid) return false;
                cb = cb->next;
            }
            return true;
        }
        void print(ofstream& fout) {
            CacheBlock* cb = head->next;
            for(int i = 0; i < numWays; i++) {
                if(cb->valid) fout << cb->tag << " ";
                else
                    fout << "INVALID" << " ";
                cb = cb->next;
            }
            fout << endl;
        }
        Set() {

        }
        Set(int index, int numWays, int blockSize) {
            this->index = index;
            this->numWays = numWays;
            CacheBlock* cb = new CacheBlock(blockSize);
            head = cb;
            tail = cb;
            for(int i = 0; i < numWays; i++) {
                cb = new CacheBlock(blockSize);
                tail->next = cb;
                cb->prev = tail;
                tail = cb;
            }
        }
        CacheBlock* operator[] (int at) {
            CacheBlock* cb;
            if(at <= (numWays - 1)/2) {
                cb = head->next;
                for(int i = 0; i < at; i++) {
                    cb = cb->next;
                }
                return cb;
            } else {
                cb = tail;
                for(int i = numWays - 1; i > at; i--) {
                    cb = cb->prev;
                }
                return cb;
            }
        }
        bool find(type_tag tag, bool read) {
            CacheBlock* cb = head->next;
            for(int i = 0; i < numWays; i++) {
                if (!cb->valid) {
                //get the block from memory, in cb
                //TODO:
                //a miss
                    cache_misses++;
                    cb->pointer = new Block;
                    cb->valid = true;
                    cb->tag = tag;
                    cb->dirty = false;
                    if(cb != head->next) {
                        CacheBlock* prev = cb->prev;
                        prev->next = cb->next;
                        cb->next = head->next;
                        head->next = cb;
                        if(cb == tail) tail = prev;
                    }
                    if(read)
                        read_misses++;
                    else 
                        write_misses++;
                    return false;
                } else if(cb->tag == tag) {
                //a hit!
                    cache_hits++;
                    if(cb != head->next) {
                        CacheBlock* prev = cb->prev;
                        prev->next = cb->next;
                        cb->next = head->next;
                        head->next = cb;
                        if(cb == tail) tail = prev;
                    }
                    if(!read) {
                        cb->dirty = true;
                    }       
                    return true;
                }
                cb = cb->next;
            }
            evict();
            //get the block from memory, in tail
            //a miss
            cache_misses++;
            if(read) 
                read_misses++;
            else 
                write_misses++;
            tail->pointer = new Block;
            tail->valid = true;
            tail->tag = tag;
            if(head->next == tail) {
                return false;
            }
            CacheBlock* prev = tail->prev;
            prev->next = NULL;
            tail->next = head->next;
            head->next = tail;
            tail = prev;
            return false;
        }
        void evict() { //rp = lru
            CacheBlock* cb = tail;
            if(cb->valid) {
                if(cb->dirty) {
                    dirty_blocks_evicted++;
                }
                cb->valid = false;
                cb->tag = 0;
                cb->dirty = false;
            }
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