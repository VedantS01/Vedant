#include "Cache.h"
#include "MainMemory.h"
using namespace std;

void Cache::access(int wr, type_tag tag, int setIndex, int blockOffset) {
    if(wr == 1) {
        write(tag, setIndex, blockOffset);
    } else {
        read(tag, setIndex, blockOffset);
    }
}

void Cache::write(type_tag tag, int setIndex, int blockOffset) {
    CacheBlock* cb = sets[setIndex];
    for(int i = 0; i < numWays; i++) {
        if(cb->tag == tag) {
            //write in the cb->dataBlock->data;
            cb->dirty = true;
            return;
        }
    }

    //a cache write miss
    evict();
    cb = get(tag, setIndex, blockOffset);
    //write in the cb->dataBlock->data;
    cb->dirty = true;
}

void Cache::read(type_tag tag, int setIndex, int blockOffset) {
    CacheBlock* cb = sets[setIndex];
    for(int i = 0; i < numWays; i++) {
        if(cb->tag == tag) {
            //read from the cb->dataBlock->data;
            return;
        }
    }

    //a cache read miss
    evict();
    cb = get(tag, setIndex, blockOffset);
    //read from the cb->dataBlock->data;
    cb->dirty = true;
}

CacheBlock* Cache::get(type_tag tag, int setIndex, int blockOffset) {
    CacheBlock* cp = sets[setIndex];
    for(int i = 0; i < numWays; i++) {
        if(cp == NULL) {
            cp = new CacheBlock(tag);
            cp->next = sets[setIndex]->next;
            sets[setIndex]->next = cp;
        }
    }

    
}

void Cache::intialise() {
    if(associativity != 0) {
        numWays = associativity;
    } else {
        numWays = cacheSize / blockSize ;
    }
    if(numWays == 0) {
        cout << "Erro, bad input\n";
        exit(0);
    }
    sets = new CacheBlock*[numSets];
    CacheBlock* cb;
    for(int i = 0; i < numSets; i++) {
        cb = sets[i]->next;
        for(int j = 0; j < numWays; j++) {
            cb = new CacheBlock(blockSize);
        }
    }
}

