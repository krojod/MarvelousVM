#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/memory.h"

byte* createMemory() {
    byte* memory = malloc(sizeof(byte) * DEFAULT_MEM_SIZE);
    if (!memory)
    {
        perror("Not enough memory");
        exit(EXIT_FAILURE);
    }
    return memory;
}

uint64_t readNBytesOfMemory(int n, const byte* mem_loc){
    uint64_t memoryBlock = 0;
    for(int i = n - 1; i >= 0; i--)
    {
        memoryBlock = (memoryBlock | mem_loc[i]) << (sizeof(byte)* i);
    }
    return memoryBlock;
}
