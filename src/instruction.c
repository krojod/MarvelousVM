#include "../include/instruction.h"
#include "../include/register.h"
#include "../include/memory.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void executeInstruction(byte *mem_loc, uint64_t *reg, byte *memory) {
  InstructionCode instr_code =
      readBitAreaFromByte(*mem_loc, INSTRC_BITS, INSTRB_CNT);
  Instruction instr = {
      mem_loc + 1, readBitAreaFromByte(*mem_loc, INSTRB_CNT, 0), instr_code};
  switch (instr_code) {
  case ADD:
  case MUL:
  case SUB:
  case DIV:
  case AND:
  case OR:
   {
    opp_math(instr, reg, memory);
    break;
  }
  case NOT:break;
  case CMP:
    break;
  case B:
    break;
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
  uint64_t operand;
  if ((1 << 8) & *(instr.instr_start)) {
    if (instr.instr_length != REFERENCE_MINIMUM_INSTR_LEN) {
      perror("Unexpected instruction length!\n");
      free(memory);
      exit(EXIT_FAILURE);
    }
    // add 1 as 3 bits can represent 0...7 as 0 i s not possible 1...8 can be represented
    byte dataLength =  readBitAreaFromByte(*instr.instr_start, DLENGTH_IDENTIFIER_BITS, REGISTER_REF_SIZE) + 1;
    uint64_t offset = readNBytesOfMemory(sizeof(uint64_t), instr.instr_start + DEST_REG_LENGTH);
    operand = readNBytesOfMemory(dataLength, &memory[reg[PC] + offset]);
  } else {
    if (instr.instr_length != REGISTERS_MINIMUM_LEN) {
      perror("Unexpected instruction length!\n");
      free(memory);
      exit(EXIT_FAILURE);
    }
    operand = readBitAreaFromByte(*instr.instr_start + 1, REGISTER_REF_SIZE, 0);
  }
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
  
}

byte readBitAreaFromByte(const byte target_byte, const unsigned int byte_cnt, const unsigned int offset) {
    if ((byte_cnt + offset) > BYTE_SIZE) {
        perror("Out of byte range\n");
        return 0;
    }
    const byte bit_mask = (1 << (byte_cnt + 1)) - 1;
    return (target_byte >> offset) & bit_mask;
}

void updateFlags(byte reg_id, uint64_t* reg)
{
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
