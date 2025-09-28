#include "../include/instruction.h"
#include "../include/register.h"
#include "../include/memory.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Instruction readInstructionFromMemory(byte *mem_loc)
{
  InstructionCode instr_code =
      readBitAreaFromByte(*mem_loc, INSTRC_BITS, INSTRB_CNT);
  Instruction instr = {mem_loc + 1, readBitAreaFromByte(*mem_loc, INSTRB_CNT, 0), instr_code};
  return instr;
}

void executeInstruction(byte *mem_loc, uint64_t *reg, byte *memory) {
  Instruction instr = readInstructionFromMemory(mem_loc);
  switch (instr.instr_code) {
  case ADD:
  case MUL:
  case SUB:
  case DIV:
  case AND:
  case OR:  opp_math(instr, reg, memory); break;
  case NOT: opp_not(instr, reg, memory); break;
  case CMP: opp_cmp(instr, reg, memory); break;
  case B:   opp_b(instr, reg, memory); break;
  case LDR:
    break;
  case MOV:
    break;
  case STR:
    break;
  case SWI:
    break;
  case SWP:
    break;
  default:
    break;
  }
  // increment the Programm counter by instructionLength + code byte
  reg[PC] += (instr.instr_length + 1);
}

void opp_math(Instruction instr, uint64_t *reg, byte *memory) {
  byte dest_reg = readBitAreaFromByte(*instr.instr_start, REGISTER_REF_SIZE, 0);
  uint64_t operand = getOperandFromInstruction(instr, reg, memory);
  switch (instr.instr_code) {
    case ADD: reg[dest_reg] = reg[dest_reg] + operand; break;
    case SUB: reg[dest_reg] = reg[dest_reg] - operand; break;
    case MUL: reg[dest_reg] = reg[dest_reg] * operand; break;
    case DIV: reg[dest_reg] = reg[dest_reg] / operand; break;
    case OR: reg[dest_reg] = reg[dest_reg] | operand; break;
    case AND: reg[dest_reg] = reg[dest_reg] & operand; break;
    default: {
      free(memory);
      perror("Unexpected control flow!");
      exit(EXIT_FAILURE);
    } break;
    }
    updateFlags(dest_reg, reg);
}

void opp_not(Instruction instr, uint64_t* reg, byte* memory){
  byte dest_reg = readBitAreaFromByte(*instr.instr_start, REGISTER_REF_SIZE, 0);
  if(instr.instr_length != NOT_INSTR_LEN){
    perror("Unexpected instruction length!\n");
    free(memory);
    exit(EXIT_FAILURE);
  }
  reg[dest_reg] = ~reg[dest_reg];
  updateFlags(dest_reg, reg);
}

void opp_cmp(Instruction instr, uint64_t *reg, byte *memory)
{
  byte dest_reg = readBitAreaFromByte(*instr.instr_start, REGISTER_REF_SIZE, 0);
  uint64_t operand = getOperandFromInstruction(instr, reg, memory);
  reg[FLAGS] = 0;
  if(reg[dest_reg] < operand){
    reg[FLAGS] = NFLAG;
  }
  else if(reg[dest_reg] > operand)
  {
    reg[FLAGS] = PFLAG;
  }
  else{
    reg[FLAGS] = ZFLAG;
  }
}

void opp_b(Instruction instr, uint64_t *reg, byte *memory)
{
  if (instr.instr_length != REFERENCE_INSTR_LEN)
  {
    perror("Unexpected instruction length!\n");
    free(memory);
    exit(EXIT_FAILURE);
  }
  byte bit_mask = readBitAreaFromByte(instr.instr_start, B_MASK_SIZE, 0);
  if(bit_mask & reg[FLAGS]){
    uint64_t offset = readNBytesOfMemory(sizeof(uint64_t), instr.instr_start + META_DATA_BYTES);
    reg[PC] += offset;
  }
}

byte readBitAreaFromByte(const byte target_byte, const unsigned int bit_cnt, const unsigned int offset)
{
  if ((bit_cnt + offset) > BYTE_SIZE)
  {
    perror("Out of byte range\n");
    return 0;
  }
  const byte bit_mask = (1 << (bit_cnt)) - 1;
  return (target_byte >> offset) & bit_mask;
}

void updateFlags(byte reg_id, uint64_t *reg)
{
  reg[FLAGS] = 0;
  if((long)reg[reg_id] < 0)
  {
    reg[FLAGS] = NFLAG;
  }
  else if ((long)reg[reg_id] > 0) {
    reg[FLAGS] = PFLAG;
  }
  else {
    reg[FLAGS] = ZFLAG;
  }
}

uint64_t getOperandFromInstruction(Instruction instr, uint64_t *reg, byte *memory)
{
  uint64_t operand;
  // first bit is set to 1, second parameter is loaded from memory
  if ((1 << 7) & *(instr.instr_start)) {
    if (instr.instr_length != REFERENCE_INSTR_LEN) {
      perror("Unexpected instruction length!\n");
      free(memory);
      exit(EXIT_FAILURE);
    }
    // add 1 as 3 bits can represent 0...7 as 0 i s not possible 1...8 can be represented
    byte dataLength =  readBitAreaFromByte(*instr.instr_start, DLENGTH_IDENTIFIER_BITS, REGISTER_REF_SIZE) + 1;
    uint64_t offset = readNBytesOfMemory(sizeof(uint64_t), instr.instr_start + META_DATA_BYTES);
    operand = readNBytesOfMemory(dataLength, &memory[reg[PC] + offset]);
  } 
  // first bit is set to 0, second parameter is loaded from registry
  else {
    if (instr.instr_length != REGISTERS_INSTR_LEN) {
      perror("Unexpected instruction length!\n");
      free(memory);
      exit(EXIT_FAILURE);
    }
    operand = reg[readBitAreaFromByte(*instr.instr_start + 1, REGISTER_REF_SIZE, 0)];
  }
  return operand;
}
