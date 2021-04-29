#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;
#include "Cache.h"
#define HASH_TABLE_SIZE 0x8000000

long long int hasher(long long int val)
{
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

long long int HexToDec(string hex)
{
    long long int dec = 0;
    for (auto i = hex.begin(); i != hex.end(); i++)
    {
        int deci = *i <= '9' ? *i - '0' : *i - 'a' + 10;
        dec = dec * 16 + deci;
    }
    return dec;
}

int main()
{
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
    if (!fin.is_open())
    {
        cerr << "ERROR: Memory Trace File Does Not Exist\n";
        exit(0);
    }
    Cache *cache;
    if (replacementPolicy == Cache::replacementPolicy)
    {
        cache = new Cache(cacheSize, blockSize, associativity);
    }
    else if (replacementPolicy == CacheLRU::replacementPolicy)
    {
        cache = new CacheLRU(cacheSize, blockSize, associativity);
    }
    else if (replacementPolicy == CacheLRUP::replacementPolicy)
    {
        cache = new CacheLRUP(cacheSize, blockSize, associativity);
    }
    else
    {
        exit(0);
    }
    // cache->cacheSize = cacheSize;
    // cache->blockSize = blockSize;
    // cache->associativity = associativity;
    // cache->replacementPolicy = replacementPolicy;
    // cache->initialise();
    // string trace;
    long long int dec;
    //type_tag tag;
    hashTable = vector<char>(HASH_TABLE_SIZE / blockSize, 'x');
    while (fin.eof() == 0)
    {
        fin >> hex >> dec;
        bool hit = cache->access(dec);
        // for hash records

        //dec = HexToDec(trace);
        fout << "WR = " << (dec >> 0x1f) << "\t";
        dec = (long long int)dec % HASH_TABLE_SIZE;
        dec = (long long int)dec / blockSize;
        fout << "DEBUG: " << dec << " Set: " << (dec) % cache->numSets << endl;
        if (hashTable[dec] == 'x')
        {
            compulsory_misses++;
            hashTable[dec] = 'y';
        }
        else
        {
            if (!hit)
            {
                if (cache->full())
                {
                    capacity_misses++;
                }
                else
                {
                    conflict_misses++;
                }
            }
        }
    }

    //print out simulation results
    cout << "Cache Size                     =            " << cacheSize << "  bytes\n";
    cout << "Block Size                     =            " << blockSize << "  bytes\n";
    cout << "Type of cache                  =            ";
    switch (associativity)
    {
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
    cout << "Replacement Policy             =            ";
    switch (replacementPolicy)
    {
    case Cache::replacementPolicy:
        cout << "random\n";
        break;
    case CacheLRU::replacementPolicy:
        cout << "LRU\n";
        break;
    case CacheLRUP::replacementPolicy:
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