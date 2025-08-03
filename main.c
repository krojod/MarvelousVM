#include "src/memory.h"
#include "src/register.h"
#include <stdint.h>
#include <stdlib.h>

int main() {
    uint64_t reg[RREG_SIZE] = {0};
    byte* memory = createMemory();
    //TODO load programm

    free(memory);
    return EXIT_SUCCESS;
}
