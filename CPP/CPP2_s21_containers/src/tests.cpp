#include <gtest/gtest.h>

#include "all_tests/array_test.cpp"
#include "all_tests/list_test.cpp"
#include "all_tests/map_test.cpp"
#include "all_tests/multiset_test.cpp"
#include "all_tests/queue_test.cpp"
#include "all_tests/set_test.cpp"
#include "all_tests/stack_test.cpp"
#include "all_tests/vector_test.cpp"

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
