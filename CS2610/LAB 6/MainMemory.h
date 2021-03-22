/******************************************
 *  Cache.h         :       Contains definition of structures and functions used to simulate MainMemory
 *  
 *  Author          :       Vedant Saboo (CS19B074)
 *  Version         :       1.0.0
 *  Created         :       10:13 AM 3/19/2021
 *  Last Modified   :       10:14 AM 3/19/2021 by Vedant
 * 
 ******************************************/

#include <iostream>
#include <cmath>
using namespace std;
typedef short unsigned int int_16;
typedef bool bit;
#define BYTE_ADDRESSING 8
#define MEMORY_SIZE 0x80000000 //size in bytes

int_16 blockSize;

//define block
/**
 *  class Block         --  contains information about the generic block
 *  Author              --  Vedant Saboo (CS19b074)
 **/
class Block {
    public:
    bit* addr;
    int_16 addrSize;
    bit* data[BYTE_ADDRESSING];
    int_16 dataSize;
};

//rest structure to be determined