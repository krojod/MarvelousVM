#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#define DEFAULT_MEM_SIZE 10000

typedef uint8_t byte;

/// @brief creates the memory for the VM on the heap
byte* createMemory();
/// @brief reads up to 8 bytes of memory 
uint64_t readNBytesOfMemory(int n, const byte* mem_loc);

#endif
