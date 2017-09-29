#include <iostream>

#include "feature\static_assert_test.h"
#include "ill_typed.h"

#include "test\data_structure\min_heap_test.h"
#include "test\data_structure\dual_stack_test.h"

#include "data_structure\union_find_sets.h"

using std::cout;

namespace test = zyf::test;

#include <cmath>
#include <cassert>

int main(int argc, char **argv) {
  //std::cout << std::boolalpha;
  //std::cout << is_expr_ill_typed(0) << std::endl;
  //std::cout << is_expr_ill_typed(1.0) << std::endl;
  ////std::cout << isExprIllTyped<ill_expr_t2, void>() << std::endl;

  //std::cout << has_typedef_foobar<int>::value << std::endl;

  test::MinHeap_RunTests();
  test::DualStack_RunTests();

  std::getchar();
}
