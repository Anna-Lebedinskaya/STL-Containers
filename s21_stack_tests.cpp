#include <gtest/gtest.h>

#include <stack>

#include "s21_stack.h"

void compare_stacks(s21::stack<float> &stack, std::stack<float> &ctrl) {
  while (stack.size() || ctrl.size()) {
    ASSERT_EQ(stack.top(), ctrl.top());
    stack.pop();
    ctrl.pop();
  }
}

TEST(s21_stack_test, alltogather) {
  // default
  s21::stack<float> stack;
  std::stack<float> ctrl;
  ASSERT_EQ(stack.empty(), ctrl.empty());

  stack.push(1);
  ctrl.push(1);
  stack.push(2);
  ctrl.push(2);
  stack.push(3);
  ctrl.push(3);
  stack.push(2);
  ctrl.push(2);
  ASSERT_EQ(stack.size(), ctrl.size());
  compare_stacks(stack, ctrl);

  // initializer_list
  std::initializer_list<float> data{1, 2, 3, 4, 5};
  s21::stack<float> stack2{1, 2, 3, 4, 5};
  std::stack<float> ctrl2(data);
  ASSERT_EQ(stack2.size(), ctrl2.size());
  compare_stacks(stack2, ctrl2);

  // copy
  std::initializer_list<float> data_tmp{6, 7, 8, 9, 10};
  s21::stack<float> stack_tmp{6, 7, 8, 9, 10};
  std::stack<float> ctrl_tmp(data_tmp);

  s21::stack<float> stack3(stack_tmp);
  std::stack<float> ctrl3(ctrl_tmp);
  ASSERT_EQ(stack3.size(), ctrl3.size());

  // move constructor
  s21::stack<float> stack4(std::move(stack3));
  std::stack<float> ctrl4(std::move(ctrl3));
  ASSERT_EQ(stack4.size(), ctrl4.size());
  compare_stacks(stack4, ctrl4);

  // move operator
  s21::stack<float> stack5 = std::move(stack_tmp);
  std::stack<float> ctrl5(data_tmp);
  ASSERT_EQ(stack5.size(), ctrl5.size());
  compare_stacks(stack5, ctrl5);
}

TEST(s21_stack_test, default_constructor) {
  s21::stack<int> stack;
  std::stack<int> ctrl;
  ASSERT_EQ(stack.empty(), ctrl.empty());
}

TEST(s21_stack_test, init_constructor) {
  s21::stack<int> stack{1, 2, 3};
  ASSERT_FALSE(stack.empty());
}

TEST(s21_stack_test, copy_constructor) {
  s21::stack<int> stack{1};
  s21::stack<int> s21QueueCopied(stack);
  ASSERT_EQ(stack.top(), s21QueueCopied.top());
}

TEST(s21_stack_test, move_constructor) {
  s21::stack<int> stack{1, 2, 3};
  s21::stack<int> s21QueueMoved(std::move(stack));
  ASSERT_TRUE(stack.empty());
  ASSERT_FALSE(s21QueueMoved.empty());
}

TEST(s21_stack_test, move_operator_constructor) {
  s21::stack<int> stack{1, 2, 3};
  s21::stack<int> s21QueueMoved;
  s21QueueMoved = std::move(stack);
  ASSERT_TRUE(stack.empty());
  ASSERT_FALSE(s21QueueMoved.empty());
}

TEST(s21_stack_test, constructor_2) {
  s21::stack<int> stack = s21::stack<int>();

  ASSERT_EQ(stack.empty(), true);
}

TEST(s21_stack_test, constructor_initiazlizer) {
  s21::stack<int> stack = s21::stack<int>{10, 20};
  ASSERT_EQ(stack.empty(), false);
  ASSERT_EQ(stack.top(), 20);
}

TEST(s21_stack_test, constructor) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(5);
  stack.push(10);
  stack.push(12);
  s21::stack<int> stack2 = s21::stack<int>(stack);
  ASSERT_EQ(stack2.empty(), false);
  ASSERT_EQ(stack2.top(), 12);
}

TEST(s21_stack_test, constructor_move) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(5);
  stack.push(10);
  stack.push(12);
  s21::stack<int> stack2 = std::move(stack);
  ASSERT_EQ(stack2.empty(), false);
  ASSERT_EQ(stack2.top(), 12);
}

TEST(s21_stack_test, empty) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(5);
  ASSERT_EQ(stack.empty(), false);
}

TEST(s21_stack_test, push) {
  s21::stack<int> stack;
  stack.push(566);
  std::stack<int> ctrl;
  ctrl.push(566);
  ASSERT_EQ(stack.top(), ctrl.top());
}

TEST(s21_stack_test, push_2) {
  s21::stack<int> stack;
  stack.push(3);
  stack.push(4);
  stack.pop();
  std::stack<int> ctrl;
  ctrl.push(3);
  ASSERT_EQ(stack.top(), ctrl.top());
}

TEST(s21_stack_test, push_3) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(5);
  stack.push(10);
  ASSERT_EQ(stack.top(), 10);
}

TEST(s21_stack_test, pop) {
  s21::stack<int> stack{566, 123};
  std::stack<int> ctrl;
  ctrl.push(566);
  ctrl.push(123);
  ASSERT_EQ(stack.top(), ctrl.top());
  stack.pop();
  ctrl.pop();
  ASSERT_EQ(stack.top(), ctrl.top());
}

TEST(s21_stack_test, pop_3) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(5);
  stack.push(10);
  stack.pop();
  ASSERT_EQ(stack.top(), 5);
}

TEST(s21_stack_test, size) {
  s21::stack<int> stack{566, 123, 3, 3, 2, 1};
  s21::stack<int> stack2{566, 123};
  ASSERT_EQ(stack.size(), 6);
  ASSERT_EQ(stack2.size(), 2);
}

TEST(s21_stack_test, size_2) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(52);
  stack.push(3);
  stack.push(21);
  stack.push(456);
  stack.pop();
  ASSERT_EQ(stack.size(), 3);
}

TEST(s21_stack_test, top) {
  s21::stack<int> stack = s21::stack<int>();
  stack.push(52);
  stack.push(3);
  stack.pop();
  ASSERT_EQ(stack.top(), 52);
}

TEST(s21_stack_test, swap) {
  s21::stack<int> stack{566, 123, 3, 3, 2, 1};
  s21::stack<int> stack2{566, 123};
  stack.swap(stack2);
  ASSERT_EQ(stack.size(), 2);
  ASSERT_EQ(stack2.size(), 6);
}

TEST(s21_stack_test, swap_2) {
  s21::stack<int> stack = s21::stack<int>();
  s21::stack<int> stack2 = s21::stack<int>();
  stack.push(52);
  stack.push(3);
  stack2.push(12);
  stack2.push(11);
  stack.swap(stack2);
  ASSERT_EQ(stack.top(), 11);
  ASSERT_EQ(stack2.top(), 3);
}

TEST(s21_stack_test, swap_3) {
  std::initializer_list<float> data1{5, 4, 3, 2, 1};
  s21::stack<float> stack1(data1);
  std::stack<float> ctrl1(data1);
  std::initializer_list<float> data2{6, 7, 8, 9, 10};
  s21::stack<float> stack2(data2);
  std::stack<float> ctrl2(data2);
  stack1.swap(stack2);
  ctrl1.swap(ctrl2);
  compare_stacks(stack1, ctrl1);
  compare_stacks(stack2, ctrl2);
}

TEST(stack_test, stack_emplace_test) {
  s21::stack<int> stack = s21::stack<int>();

  stack.emplace_front(1, 2, 3, 4, 5, 11);

  ASSERT_EQ(stack.top(), 11);
  ASSERT_EQ(stack.size(), 6);
}