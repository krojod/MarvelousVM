#include <stdlib.h>
#include <stdio.h>
#include "memory.h"

byte* createMemory() {
    byte* memory = malloc(sizeof(byte) * DEFAULT_MEM_SIZE);
    if (!memory)
    {
        perror("Not enough memory");
        exit(EXIT_FAILURE);
    }
    return memory;
}
