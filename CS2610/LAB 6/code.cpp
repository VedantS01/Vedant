#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
//#include "Cache.h"
//#include "MainMemory.h"
typedef short unsigned int int_16;
typedef bool bit;
typedef long long int type_tag;
#define BYTE_ADDRESSING 8
#define MEMORY_SIZE 0x80000000 //size in bytes
int cache_misses = 0;
int cache_hits = 0;
int total_memory_refs = 0;
class Block {
    public:
    bit* addr;
    int_16 addrSize;
    bit* data[BYTE_ADDRESSING];
    int_16 dataSize;
};

string HexToBinary(string hex) {
    string ret;
    for(auto i = hex.begin(); i != hex.end(); i++) {
        switch (*i)
        {
        case '0':
            ret.push_back('0');
            ret.push_back('0');
            ret.push_back('0');
            ret.push_back('0');
            break;
        case '1':
            ret.push_back('0');
            ret.push_back('0');
            ret.push_back('0');
            ret.push_back('1');
            break;
        case '2':
            ret.push_back('0');
            ret.push_back('0');
            ret.push_back('1');
            ret.push_back('0');
            break;
        case '3':
            ret.push_back('0');
            ret.push_back('0');
            ret.push_back('1');
            ret.push_back('1');
            break;
        case '4':
            ret.push_back('0');
            ret.push_back('1');
            ret.push_back('0');
            ret.push_back('0');
            break;
        case '5':
            ret.push_back('0');
            ret.push_back('1');
            ret.push_back('0');
            ret.push_back('1');
            break;
        case '6':
            ret.push_back('0');
            ret.push_back('1');
            ret.push_back('1');
            ret.push_back('0');
            break;
        case '7':
            ret.push_back('0');
            ret.push_back('1');
            ret.push_back('1');
            ret.push_back('1');
            break;
        case '8':
            ret.push_back('1');
            ret.push_back('0');
            ret.push_back('0');
            ret.push_back('0');
            break;
        case '9':
            ret.push_back('1');
            ret.push_back('0');
            ret.push_back('0');
            ret.push_back('1');
            break;
        case 'a':
            ret.push_back('1');
            ret.push_back('0');
            ret.push_back('1');
            ret.push_back('0');
            break;
        case 'b':
            ret.push_back('1');
            ret.push_back('0');
            ret.push_back('1');
            ret.push_back('1');
            break;
        case 'c':
            ret.push_back('1');
            ret.push_back('1');
            ret.push_back('0');
            ret.push_back('0');
            break;
        case 'd':
            ret.push_back('1');
            ret.push_back('1');
            ret.push_back('0');
            ret.push_back('1');
            break;
        case 'e':
            ret.push_back('1');
            ret.push_back('1');
            ret.push_back('1');
            ret.push_back('0');
            break;
        case 'f':
            ret.push_back('1');
            ret.push_back('1');
            ret.push_back('1');
            ret.push_back('1');
            break;
        
        
        default:
            break;
        }
    }
    return ret;
}

long long int HexToDec(string hex) {
    long long int dec = 0;
    for(auto i = hex.begin(); i != hex.end(); i++) {
        int deci = *i <= '9' ? *i - '0' : *i - 'a';
        dec = dec * 16 + deci;
    }
    cout << hex << " " << dec << endl;
    return dec;
}

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

class Set {
    public:
    CacheBlock* head;
    CacheBlock* tail;
    int numWays;
    int index;
    int blockSize;
    Set() {

    }
    Set(int index, int numWays, int blockSize) {
        cout << "Set: contructor call\n";
        this->index = index;
        this->numWays = numWays;
        CacheBlock* cb = new CacheBlock(blockSize);
        head = cb;
        tail = cb;
        for(int i = 1; i < numWays; i++) {
            cb = new CacheBlock(blockSize);
            tail->next = cb;
            cb->prev = tail;
            tail = cb;
        }
    }
    CacheBlock* operator[] (int at) {
        CacheBlock* cb;
        if(at <= (numWays - 1)/2) {
            cb = head;
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
    CacheBlock* find(type_tag tag) {
        CacheBlock* cb = head;
        for(int i = 0; i < numWays; i++) {
            if (!cb->valid) {
                //get the block from memory, in cb
                //TODO:
                //a miss
                cache_misses++;
                cb->pointer = new Block;
                cb->valid = true;
                cb->tag = tag;
                return cb;
            } else if(cb->tag == tag) {
                //a hit!
                cache_hits++;
                return cb;
            }
            cb = cb->next;
        }
        evict();
        //get the block from memory, in tail
        //a miss
        cache_misses++;
        tail->pointer = new Block;
        tail->valid = true;
        tail->tag = tag;
        return tail;
    }
    void evict() { //rp = random, lru
        CacheBlock* cb = tail;
        if(cb->valid) {
            if(cb->dirty) {
                //write the block at cb to the memory
            }
            cb->valid = false;
            cb->tag = 0;
            cb->dirty = false;
        }
    }
    void write(type_tag t, int b) {
        CacheBlock* cb = find(t);
        //write in cb, at block offset b
    }
    void read(type_tag t, int b) {
        CacheBlock* cb = find(t);
        //read from cb, at block offset b
    }
};

class Cache {
    public:
    int cacheSize; //in bytes
    int blockSize; //in bytes
    int associativity; //number of ways
    int replacementPolicy; 
    int numSets;
    int numWays;
    Set* sets;
    void initialise() {
        if(associativity != 0) {
            numWays = associativity;
        } else 
            numWays = cacheSize / blockSize ;
        numSets = cacheSize / blockSize / numWays ;
        sets = new Set [numSets]; //later, charactorize by associativity.
        for(int i = 0; i < numSets; i++) sets[i] = Set(i, numWays, blockSize);
    }
    void access(string hex) {
        total_memory_refs++;
        long long int dec = HexToDec(hex);
        int wr = dec / MEMORY_SIZE;
        type_tag tag = (type_tag) dec % MEMORY_SIZE;
        int blockOffset = tag % blockSize;
        tag = (type_tag) tag / blockSize;
        int setIndex = tag % numSets;
        tag = (type_tag) tag / numSets;
        cout << "\t" << wr << " " << tag << " " << setIndex << " " << blockOffset << endl;
        if(wr == 1) {
            write(tag, setIndex, blockOffset);
        } else {
            read(tag, setIndex, blockOffset);
        }
    }
    void read(type_tag t, int s, int b) {
        sets[s].read(t, b);
    }
    void write(type_tag t, int s, int b) {
        sets[s].write(t, b);
    }
};

int main() {
    int cacheSize, blockSize, associativity, replacementPolicy;
    string filename;
    cout << "Enter cacheSize : "; cin >> cacheSize;
    cout << "Enter blockSize : "; cin >> blockSize;
    cout << "Enter associativity : "; cin >> associativity;
    cout << "Enter replacementPolicy : "; cin >> replacementPolicy;
    cout << "Enter filename : "; cin >> filename;
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()) {
        cout << "Memory Trace File Does Not Exist \n";
        return 0;
    }
    Cache cache;
    cache.cacheSize = cacheSize;
    cache.blockSize = blockSize;
    cache.associativity = associativity;
    cache.replacementPolicy = replacementPolicy;
    cache.initialise();
    string trace;
    long long int dec;
    type_tag tag;
    while(fin.eof() == 0) {
        fin >> trace;
        /*
        dec = HexToDec(trace);
        int wr = dec / MEMORY_SIZE;
        tag = (type_tag) dec % MEMORY_SIZE;
        int blockOffset = tag % blockSize;
        tag = (type_tag) tag / blockSize;
        int setIndex = tag % cache.numSets;
        tag = (type_tag) tag / cache.numSets;
        */
        cache.access(trace);
    }
    cout << "Cache Misses = " << cache_misses << endl;
    cout << "Cache Hits = " << cache_hits << endl;
    cout << "Total Memory References = " << total_memory_refs << endl;

}

/**
 * END OF FILE
 **/