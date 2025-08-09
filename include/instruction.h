#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "../include/memory.h"
#include <stdint.h>

#define BYTE_SIZE 8
#define INSTRC_BITS 5
#define INSTRB_CNT 3

typedef enum{
    ADD, // Add
    MUL, // Multiply
    SUB, // Subtract
    DIV, // Divide
    AND, // And
    OR, // OR
    NOT, // NOT
    CMP, // Compare
    B, // Branch
    LDR, // Load Register
    MOV, // Move Register
    STR, // Store in Memory
    SWI, // OS call
    SWP, // SWAP register with memory
} InstructionCode;

typedef struct{
    byte* instr_start;
    byte instr_length;
    InstructionCode instr_code;
} Instruction;

byte readBitAreaFromByte(byte target_byte, unsigned int byte_cnt, unsigned int offset);
void executeInstruction(byte* mem_loc, uint64_t* reg, byte* memory);
// operations

/// @brief All math operations take this path
void opp_math(Instruction instr, uint64_t* reg, byte* memory);
#endif
