#ifndef REGISTER_H
#define REGISTER_H

#define REGISTER_REF_SIZE 4


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
    RIP = 8,
    PC = 9,
    FLAGS = 10,
    RREG_SIZE = 11
};

// Flags
enum {
    ZFLAG = 1,
    PFLAG = 2,
    NFLAG = 4,
};

#endif //REGISTER_H
