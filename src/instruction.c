#include "../include/instruction.h"

#include <stdint.h>
#include <stdio.h>

void executeInstruction(byte *mem_loc, uint64_t *reg, byte *memory) {
  InstructionCode instr_code = readBitAreaFromByte(*mem_loc, INSTRC_BITS, INSTRB_CNT);
  Instruction instr = {mem_loc + 1, readBitAreaFromByte(*mem_loc, INSTRB_CNT, 0), instr_code};
  switch (instr_code) {
  case ADD:
  case MUL:
  case SUB:
  case DIV:
  case AND:
  case OR:
  case NOT: {
    opp_math(instr, reg, memory);
    break;
  }
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
}

void opp_math(Instruction instr, uint64_t* reg, byte* memory) {
    
}

byte readBitAreaFromByte(const byte target_byte, const unsigned int byte_cnt, const unsigned int offset) {
    if ((byte_cnt + offset) > BYTE_SIZE) {
        perror("Out of byte range\n");
        return 0;
    }
    const byte bit_mask = (1 << (byte_cnt + 1)) - 1;
    return (target_byte >> offset) & bit_mask;
}
