#ifndef CACHE_CPP
#define CACHE_CPP

#include <iostream>
#include <fstream>
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

class Cache {
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
            cout << "Entered set with index " << index << endl;
            CacheBlock* cb = head->next;
            if(cb == NULL) {
                cout << "Error, cb is null\n";
                return;
            }
            cout << "peek in\n";
            for(int i = 0; i < numWays; i++) {
                cout << "i = " << i << "\n";
                if(cb == NULL) {
                cout << "Error, cb is null\n";
                fout << "UNBOUND ";
                continue;
            }
                if(cb->valid) fout << cb->tag << " ";
                else fout << "INVALID" << " ";

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
                    if(read) read_misses++;
                    else write_misses++;
                    return false;
                } else if(cb->tag == tag) {
                //a hit!
                    cache_hits++;
                    if(!read) {
                        //write to block pointed to by *cb
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
            if(read) read_misses++;
            else write_misses++;
            tail->pointer = new Block;
            tail->valid = true;
            tail->tag = tag;
            if(tail == head->next) {
                return false;
            }
            CacheBlock* prev = tail->prev;
            tail->next = head->next;
            prev->next = NULL;
            head->next = tail;
            tail = prev;
            return false;
        }
        void evict() { //rp = random
            if(tail->valid) {
                if(tail->dirty) {
                    dirty_blocks_evicted++;
                }
                tail->valid = false;
                tail->tag = 0;
                tail->dirty = false;
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
    
    public:
    int cacheSize; //in bytes
    int blockSize; //in bytes
    int associativity; //number of ways
    int replacementPolicy; 
    int numSets;
    int numWays;
    Set* sets;

    void print() {
        ofstream fout;
        fout.open("cache.contents.out", ios::app);
        for(int i = 0;  i < numSets; i++) sets[i].print(fout);
        fout << endl;
        fout.close();
    }
    
    void initialise() {
        if(associativity != 0) {
            numWays = associativity;
        } else 
            numWays = cacheSize / blockSize ;
        numSets = cacheSize / blockSize / numWays ;
        sets = new Set [numSets]; //later, charactorize by associativity.
        for(int i = 0; i < numSets; i++) sets[i] = Set(i, numWays, blockSize);
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
    }
    bool access(string hex) {
        total_memory_refs++;
        long long int dec = HexToDec(hex);
        int wr = dec / MEMORY_SIZE;
        type_tag tag = (type_tag) dec % MEMORY_SIZE;
        int blockOffset = tag % blockSize;
        tag = (type_tag) tag / blockSize;
        int setIndex = tag % numSets;
        tag = (type_tag) tag / numSets;
        ofstream fout;
        fout.open("cache.decoder.out", ios::app);
        fout << " : " << hex << "\n\t" << wr << " " <<tag << " " << setIndex << " " << blockOffset << "\n" ;
        if(wr == 1) {
            write_accesses++;
            return write(tag, setIndex, blockOffset);
        } else {
            read_accesses++;
            return read(tag, setIndex, blockOffset);
        }
    }
    bool read(type_tag t, int s, int b) {
        return sets[s].read(t, b);
    }
    bool write(type_tag t, int s, int b) {
        return sets[s].write(t, b);
    }
    bool full() {
        bool f = true;
        for(int i = 0; i < numSets; i++) {
            f = f && sets[i].full();
        }
        return f;
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

#endif

