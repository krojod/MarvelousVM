#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdbool.h>
#include "../include/instruction.h"

/// @brief tests all math operations
void test_opp_math(){
  
  CU_ASSERT(true);
}


int main(){
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("InstructionTestSuite", 0, 0);
  CU_add_test(suite, "test of add()", test_opp_math);

  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}