#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

// 64 bit Registry
enum {
    RAX = 0,
    RBX = 1,
    RCX = 2,
    RDX = 3,
    RSI = 4,
    RDI = 5,
    RSP = 6,
    RBP = 7,
    RREG_SIZE = 8
};

// 32 bit Registry
enum {
    EAX = 0,
    EBX = 1,
    ECX = 2,
    EDX = 3,
    ESI = 4,
    EDI = 5,
    ESP = 6,
    EBP = 7,
    EREG_SIZE = 8
};

// 16 bit registry
enum {
    AX = 0,
    BX = 1,
    CX = 2,
    DX = 3,
    SI = 4,
    DI = 5,
    SP = 6,
    BP = 7,
    REG_SIZE = 8
};

// 8 high bit registries
enum {
    AH = 0,
    BH = 1,
    CH = 2,
    DH = 3,
    HREG_SIZE = 4
};
// 8 low bit registries
enum {
    AL = 0,
    BL = 1,
    CL = 2,
    DL = 3,
    SIL = 4,
    DIL = 5,
    SPL = 6,
    BPL = 7,
    LREG_SIZE = 8
};


#endif //REGISTER_H
