#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "../include/memory.h"
#include <stdint.h>

#define BYTE_SIZE 8
#define INSTRC_BITS 4
#define INSTRB_CNT 4

#define REFERENCE_INSTR_LEN 9
#define NOT_INSTR_LEN 1
#define REFERENCE_BYTES 4
#define REGISTERS_INSTR_LEN 2
#define DEST_REG_LENGTH 1
#define DLENGTH_IDENTIFIER_BITS 3

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
Instruction readInstructionFromMemory(byte* mem_loc);
void executeInstruction(byte* mem_loc, uint64_t* reg, byte* memory);
void updateFlags(byte reg_id, uint64_t* reg);
uint64_t getOperandFromInstruction(Instruction instr, uint64_t* reg, byte* memory);
// operations

/// @brief All 2 parameter math operations e.g. A + B take this path
void opp_math(Instruction instr, uint64_t* reg, byte* memory);
/// @brief Not operation
void opp_not(Instruction instr, uint64_t* reg, byte* memory);
/// @brief Enables comparing 2 parameeters, sets the comparison register flags 
void opp_cmp(Instruction instr, uint64_t* reg, byte* memory);
#endif
