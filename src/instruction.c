#include "../include/instruction.h"
#include "../include/register.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
  // increment the Programm counter by instructionLength + code byte
  reg[PC] += (instr.instr_length + 1);
}

void opp_math(Instruction instr, uint64_t *reg, byte *memory) {
  if ((1 << 8) & *(instr.instr_start)) {
    if (instr.instr_length < REFERENCE_MINIMUM_INSTR_LEN) {
      perror("Unexpected instruction length!\n");
      exit(EXIT_FAILURE);
    }

  } else {
    if (instr.instr_length < REGISTERS_MINIMUM_LEN) {
      perror("Unexpected instruction length!\n");
      exit(EXIT_FAILURE);
    }
  }
}

byte readBitAreaFromByte(const byte target_byte, const unsigned int byte_cnt, const unsigned int offset) {
    if ((byte_cnt + offset) > BYTE_SIZE) {
        perror("Out of byte range\n");
        return 0;
    }
    const byte bit_mask = (1 << (byte_cnt + 1)) - 1;
    return (target_byte >> offset) & bit_mask;
}
