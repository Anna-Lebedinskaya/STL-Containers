#include <gtest/gtest.h>

#include "s21_list_tests.cpp"
#include "s21_queue_tests.cpp"
#include "s21_stack_tests.cpp"
#include "s21_vector_tests.cpp"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
