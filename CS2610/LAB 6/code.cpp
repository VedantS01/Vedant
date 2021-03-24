#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;
#include "Cache.h"
#define HASH_TABLE_SIZE 0x8000000

long long int hasher(long long int val) {
    return val % HASH_TABLE_SIZE;
}

int cache_misses;
int cache_hits;
int total_memory_refs;
int read_accesses;
int write_accesses;
int compulsory_misses;
int capacity_misses;
int conflict_misses;
int read_misses;
int write_misses;
int dirty_blocks_evicted;

//#include "MainMemory.h"
/*
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
};*/

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
    return dec;
}


/*
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
        this.blockSize = blockSize;
        dirty = false;
        valid = false;
        next = NULL;
        prev = NULL;
    }
};
*/

/*
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
        this.index = index;
        this.numWays = numWays;
        CacheBlock* cb = new CacheBlock(blockSize);
        head = cb;
        tail = cb;
        for(int i = 1; i < numWays; i++) {
            cb = new CacheBlock(blockSize);
            tail.next = cb;
            cb.prev = tail;
            tail = cb;
        }
    }
    CacheBlock* operator[] (int at) {
        CacheBlock* cb;
        if(at <= (numWays - 1)/2) {
            cb = head;
            for(int i = 0; i < at; i++) {
                cb = cb.next;
            }
            return cb;
        } else {
            cb = tail;
            for(int i = numWays - 1; i > at; i--) {
                cb = cb.prev;
            }
            return cb;
        }
    }
    CacheBlock* find(type_tag tag) {
        CacheBlock* cb = head;
        for(int i = 0; i < numWays; i++) {
            if (!cb.valid) {
                //get the block from memory, in cb
                //TODO:
                //a miss
                cache_misses++;
                cb.pointer = new Block;
                cb.valid = true;
                cb.tag = tag;
                return cb;
            } else if(cb.tag == tag) {
                //a hit!
                cache_hits++;
                return cb;
            }
            cb = cb.next;
        }
        evict();
        //get the block from memory, in tail
        //a miss
        cache_misses++;
        tail.pointer = new Block;
        tail.valid = true;
        tail.tag = tag;
        return tail;
    }
    void evict() { //rp = random, lru
        CacheBlock* cb = tail;
        if(cb.valid) {
            if(cb.dirty) {
                //write the block at cb to the memory
            }
            cb.valid = false;
            cb.tag = 0;
            cb.dirty = false;
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
*/
/*
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
                this.blockSize = blockSize;
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
        Set() {

        }
        Set(int index, int numWays, int blockSize) {
            cout << "Set: contructor call\n";
            this.index = index;
            this.numWays = numWays;
            CacheBlock* cb = new CacheBlock(blockSize);
            head = cb;
            tail = cb;
            for(int i = 0; i < numWays; i++) {
                cb = new CacheBlock(blockSize);
                tail.next = cb;
                cb.prev = tail;
                tail = cb;
            }
        }
        CacheBlock* operator[] (int at) {
            CacheBlock* cb;
            if(at <= (numWays - 1)/2) {
                cb = head.next;
                for(int i = 0; i < at; i++) {
                    cb = cb.next;
                }
                return cb;
            } else {
                cb = tail;
                for(int i = numWays - 1; i > at; i--) {
                    cb = cb.prev;
                }
                return cb;
            }
        }
        CacheBlock* find(type_tag tag) {
            CacheBlock* cb = head.next;
            for(int i = 0; i < numWays; i++) {
                if (!cb.valid) {
                //get the block from memory, in cb
                //TODO:
                //a miss
                    cache_misses++;
                    cb.pointer = new Block;
                    cb.valid = true;
                    cb.tag = tag;
                    return cb;
                } else if(cb.tag == tag) {
                //a hit!
                    cache_hits++;
                    return cb;
                }
                cb = cb.next;
            }
            evict();
            //get the block from memory, in tail
            //a miss
            cache_misses++;
            tail.pointer = new Block;
            tail.valid = true;
            tail.tag = tag;
            CacheBlock* prev = tail.prev;
            tail.next = head.next;
            prev.next = NULL;
            head.next = tail;
            tail = prev;
            return head.next;
        }
        void evict() { //rp = random, lru
            CacheBlock* cb = tail;
            if(cb.valid) {
                if(cb.dirty) {
                //write the block at cb to the memory
                }
                cb.valid = false;
                cb.tag = 0;
                cb.dirty = false;
            }
        }
        void write(type_tag t, int b) {
            CacheBlock* cb = find(t);
            //write in cb, at block offset b
        }
        void read(type_tag t, int b) {
            CacheBlock* cb = find(t);
            //read from cb, at block offset b
            cb.dirty = true;
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
                this.blockSize = blockSize;
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
        Set() {

        }
        Set(int index, int numWays, int blockSize) {
            cout << "Set: contructor call\n";
            this.index = index;
            this.numWays = numWays;
            CacheBlock* cb = new CacheBlock(blockSize);
            head = cb;
            tail = cb;
            for(int i = 0; i < numWays; i++) {
                cb = new CacheBlock(blockSize);
                tail.next = cb;
                cb.prev = tail;
                tail = cb;
            }
        }
        CacheBlock* operator[] (int at) {
            CacheBlock* cb;
            if(at <= (numWays - 1)/2) {
                cb = head.next;
                for(int i = 0; i < at; i++) {
                    cb = cb.next;
                }
                return cb;
            } else {
                cb = tail;
                for(int i = numWays - 1; i > at; i--) {
                    cb = cb.prev;
                }
                return cb;
            }
        }
        CacheBlock* find(type_tag tag) {
            CacheBlock* cb = head.next;
            for(int i = 0; i < numWays; i++) {
                if (!cb.valid) {
                //get the block from memory, in cb
                //TODO:
                //a miss
                    cache_misses++;
                    cb.pointer = new Block;
                    cb.valid = true;
                    cb.tag = tag;
                    if(cb != head.next) {
                        CacheBlock* prev = cb.prev;
                        prev.next = cb.next;
                        cb.next = head.next;
                        head.next = cb;
                        if(cb == tail) tail = prev;
                    }
                    return cb;
                } else if(cb.tag == tag) {
                //a hit!
                    cache_hits++;
                    if(cb != head.next) {
                        CacheBlock* prev = cb.prev;
                        prev.next = cb.next;
                        cb.next = head.next;
                        head.next = cb;
                        if(cb == tail) tail = prev;
                    }       
                    return cb;
                }
                cb = cb.next;
            }
            evict();
            //get the block from memory, in tail
            //a miss
            cache_misses++;
            tail.pointer = new Block;
            tail.valid = true;
            tail.tag = tag;
            if(head.next == tail) {
                return tail;
            }
            CacheBlock* prev = tail.prev;
            prev.next = NULL;
            tail.next = head.next;
            head.next = tail;
            tail = prev;
            return head.next;
        }
        void evict() { //rp = random, lru
            CacheBlock* cb = tail;
            if(cb.valid) {
                if(cb.dirty) {
                //write the block at cb to the memory
                }
                cb.valid = false;
                cb.tag = 0;
                cb.dirty = false;
            }
        }
        void write(type_tag t, int b) {
            CacheBlock* cb = find(t);
            //write in cb, at block offset b
            cb.dirty = true;
        }
        void read(type_tag t, int b) {
            CacheBlock* cb = find(t);
            //read from cb, at block offset b
        }
    };
    
};

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
            //CacheBlock* next;
            //CacheBlock* prev;
            CacheBlock(int blockSize) {
                this.blockSize = blockSize;
                dirty = false;
                valid = false;
                //next = NULL;
                //prev = NULL;
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
            cout << "Set: contructor call\n";
            this.index = index;
            this.numWays = numWays;
            blocks = new CacheBlock[numWays];
            for(int i = 0; i < numWays; i++) {
                blocks[i] = CacheBlock(blockSize);
            }

            //init_lru_tree
            initLRUTree();
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
        void afterMissOperation(int pos) {
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
        CacheBlock* find(type_tag tag) {
            for(int i = 0; i < numWays; i++) {
                if(!blocks[i].valid) {
                    continue;
                }
                if(blocks[i].tag == tag) {
                //a hit!
                    cache_hits++;
                    return &blocks[i];
                    //return cb;
                }
            }
            //miss;
            //evict();
            cache_misses++;
            //TODO: get the block
            int i = replacePosition();
            if(blocks[i].valid) {
                evict(i);
            }
            blocks[i].tag = tag;
            blocks[i].valid = true;
            blocks[i].pointer = new Block;
            afterMissOperation(i + numWays - 1);
            return &blocks[i];
        }
        void evict(int i) {
            if(blocks[i].dirty) {
                //write to memory/write buffer
            }
            blocks[i].valid = false;
            blocks[i].tag = 0;
            blocks[i].dirty = false;
        }
        void write(type_tag t, int b) {
            CacheBlock* cb = find(t);
            //write in cb, at block offset b
            cb.dirty = true;
        }
        void read(type_tag t, int b) {
            CacheBlock* cb = find(t);
            //read from cb, at block offset b
        }
    };
    

};

*/


int main() {
    int cacheSize, blockSize, associativity, replacementPolicy;
    string filename;
    
    vector<char> hashTable;

    cin >> cacheSize;
    cin >> blockSize;
    cin >> associativity;
    cin >> replacementPolicy;
    cin >> filename;
    ifstream fin;
    ofstream fout;
    fout.open("debug.out", ios::app);
    fin.open(filename);
    if(!fin.is_open()) {
        cerr << "ERROR: Memory Trace File Does Not Exist\n";
        exit(0);
    }
    Cache* cache;
    if(replacementPolicy == Cache::replacementPolicy) {
        cache = new Cache;
    } else if (replacementPolicy == CacheLRU::replacementPolicy) {
        cache = new CacheLRU;
    } else if (replacementPolicy == CacheLRUP::replacementPolicy) {
        cache = new CacheLRUP;
    } else {
        exit(0);
    }
    cache->cacheSize = cacheSize;
    cache->blockSize = blockSize;
    cache->associativity = associativity;
    //cache->replacementPolicy = replacementPolicy;
    cache->initialise();
    string trace;
    long long int dec;
    type_tag tag;
    hashTable = vector<char> (HASH_TABLE_SIZE/blockSize, 'x');
    while(fin.eof() == 0) {
        fin >> trace;
        bool hit = cache->access(trace);

        // for hash records
        
        dec = HexToDec(trace);
        char ch = hashTable[hasher(dec) / blockSize];
        fout << "DEBUG: " << hasher(dec) / blockSize << " Set: " << (hasher(dec) / blockSize) % cache->numSets << endl;
        if(ch == 'x') {
            compulsory_misses++;
            hashTable[hasher(dec) / blockSize] = 'y';
        } else {
            if(!hit) {
                if(cache->full()) {
                    capacity_misses++;
                } else {
                    conflict_misses++;
                }
            }
        }
    }
    cout << "Cache Size                     =            " << cacheSize << "  bytes\n" ;
    cout << "Block Size                     =            " << blockSize << "  bytes\n" ;
    cout << "Type of cache                  =            " ;
    switch (associativity) {
    case 0:
        cout << "fully asscociative cache\n";
        break;
    case 1:
        cout << "direct mapped cache\n";
        break;
    default:
        cout << cache->numWays << "-way set associative cache\n";
        break;
    }
    cout << "Replacement Policy             =            " ;
    switch (replacementPolicy) {
    case 0:
        cout << "random\n";
        break;
    case 1:
        cout << "LRU\n";
        break;
    case 2:
        cout << "Pseudo LRU\n";
        break;
    default:
        break;
    }
    cout << "Cache Misses                   =            " << cache_misses << endl;
    cout << "Cache Hits                     =            " << cache_hits << endl;
    cout << "Total Memory Refereneces       =            " << total_memory_refs << endl;
    cout << "Read Accesses                  =            " << read_accesses << endl;
    cout << "Read Misses                    =            " << read_misses << endl;
    cout << "Write Accesses                 =            " << write_accesses << endl;
    cout << "Write Misses                   =            " << write_misses << endl;
    cout << "Dirty Blocks Evicted           =            " << dirty_blocks_evicted << endl;
    cout << "Compulsory Misses              =            " << compulsory_misses << endl;
    cout << "Capacity Misses                =            " << capacity_misses << endl;
    cout << "Conflict Misses                =            " << conflict_misses << endl;

    cout << endl;

}

/**
 * END OF FILE
 **/