#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdbool.h>
#include "../include/instruction.h"
#include "../include/register.h"

/// @brief tests  the reading of instructions
void test_read_instr(){
  byte instr_header = (ADD << INSTRB_CNT) + 5;
  Instruction simple_instr =  readInstructionFromMemory(&instr_header);
  CU_ASSERT_EQUAL(simple_instr.instr_code, ADD);
  CU_ASSERT_EQUAL(simple_instr.instr_length, 5);
  CU_ASSERT_EQUAL(simple_instr.instr_start, &instr_header + 1);
}

/// @brief tests all math operations
void test_opp_math(){
  /// references
  uint64_t reg[RREG_SIZE] = {0};
  reg[RAX] = 5;
  byte memory_add_ref[] = { (ADD << INSTRB_CNT) + REFERENCE_INSTR_LEN, (1 << 7) + (3 << REGISTER_REF_SIZE) + RAX, 0,0,0,0,0,0,0,10, 0,0,0,25};
  Instruction instr = readInstructionFromMemory(memory_add_ref);
  opp_math(instr, reg, memory_add_ref);
  CU_ASSERT_EQUAL(30, reg[RAX]);
  /// registers 
  reg[RAX] = 5;
  reg[RBX] = 5;
  byte memory_add_reg[] = { (ADD << INSTRB_CNT) + REGISTERS_INSTR_LEN, RAX, RBX};
  instr = readInstructionFromMemory(memory_add_reg);
  opp_math(instr, reg, NULL);
  CU_ASSERT_EQUAL(10, reg[RAX]);
}

void test_opp_not(){
  uint64_t reg[RREG_SIZE] = {0};
  reg[RAX] = 5;
  byte memory[] = {(NOT<< INSTRB_CNT) + NOT_INSTR_LEN, RAX};
  Instruction isnstr = readInstructionFromMemory(memory);
  opp_not(isnstr, reg, NULL);
  CU_ASSERT_EQUAL(-6, reg[RAX]);
}


int main(){
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("InstructionTestSuite", 0, 0);
  CU_add_test(suite, "test instruction reading", test_read_instr);
  CU_add_test(suite, "test math operations", test_opp_math);
  CU_add_test(suite, "test not operations", test_opp_not);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}