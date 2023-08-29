#include <gtest/gtest.h>

#include <queue>

#include "s21_queue.h"

template <typename T>
testing::AssertionResult compare_queue(std::queue<T> ctrl,
                                       s21::queue<T> queue) {
  testing::AssertionResult res = testing::AssertionSuccess() << "Queues match";
  if (ctrl.size() != queue.size()) {
    res = testing::AssertionFailure()
          << "Sizes don't match " << ctrl.size() << " != " << queue.size();
  } else {
    bool pass = true;
    while (pass && !ctrl.empty()) {
      if (ctrl.front() != queue.front()) {
        pass = false;
        res = testing::AssertionFailure()
              << ctrl.front() << " != " << queue.front();
      }
      ctrl.pop();
      queue.pop();
    }
  }
  return res;
}

TEST(s21_queue_test, allconstructors) {
  // default
  s21::queue<float> queue;
  std::queue<float> ctrl;
  ASSERT_EQ(queue.empty(), ctrl.empty());

  queue.push(777);
  ctrl.push(777);
  queue.push(888);
  ctrl.push(888);
  ASSERT_EQ(queue.size(), ctrl.size());
  compare_queue(ctrl, queue);

  // initializer_list
  std::initializer_list<float> data{1, 2, 3, 4, 5};
  s21::queue<float> queue2{1, 2, 3, 4, 5};
  std::queue<float> ctrl2(data);
  ASSERT_EQ(queue2.size(), ctrl2.size());
  compare_queue(ctrl2, queue2);

  // copy
  std::initializer_list<float> data_tmp{6, 7, 8, 9, 10};
  s21::queue<float> queue_tmp{6, 7, 8, 9, 10};
  std::queue<float> ctrl_tmp(data_tmp);

  s21::queue<float> queue3(queue_tmp);
  std::queue<float> ctrl3(ctrl_tmp);
  ASSERT_EQ(queue3.size(), ctrl3.size());

  // move constructor
  s21::queue<float> queue4(std::move(queue3));
  std::queue<float> ctrl4(std::move(ctrl3));
  ASSERT_EQ(queue4.size(), ctrl4.size());
  compare_queue(ctrl4, queue4);

  // move operator
  s21::queue<float> queue5 = std::move(queue_tmp);
  std::queue<float> ctrl5(data_tmp);
  ASSERT_EQ(queue5.size(), ctrl5.size());
  compare_queue(ctrl5, queue5);
}

TEST(s21_queue_test, default_constructor) {
  s21::queue<int> queue;
  std::queue<int> ctrl;
  ASSERT_EQ(queue.empty(), ctrl.empty());
}

TEST(s21_queue_test, init_constructor) {
  s21::queue<int> queue{1, 2, 3};
  ASSERT_FALSE(queue.empty());
}

TEST(s21_queue_test, copy_constructor) {
  s21::queue<int> queue{1};
  s21::queue<int> queue2(queue);
  ASSERT_EQ(queue.front(), queue2.front());
}

TEST(s21_queue_test, move_constructor) {
  s21::queue<int> queue{1, 2, 3};
  s21::queue<int> queue2(std::move(queue));
  ASSERT_TRUE(queue.empty());
  ASSERT_FALSE(queue2.empty());
}

TEST(s21_queue_test, move_operator_constructor) {
  s21::queue<int> queue{1, 2, 3};
  s21::queue<int> queue2;
  queue2 = std::move(queue);
  ASSERT_TRUE(queue.empty());
  ASSERT_FALSE(queue2.empty());
}

TEST(s21_queue_test, move) {
  s21::queue<int> queue1({5, 3, 2, 7});
  s21::queue<int> queue2 = std::move(queue1);
  std::queue<int> ctrl({5, 3, 2, 7});
  EXPECT_TRUE(compare_queue(ctrl, queue2));
  EXPECT_TRUE(queue1.empty());
}

TEST(s21_queue_test, move_2) {
  s21::queue<int> queue1({5, 3, 2, 7});
  s21::queue<int> queue2(std::move(queue1));
  std::queue<int> ctrl({5, 3, 2, 7});
  EXPECT_TRUE(compare_queue(ctrl, queue2));
  EXPECT_TRUE(queue1.empty());
}

TEST(s21_queue_test, push_one) {
  s21::queue<int> queue;
  queue.push(10);
  EXPECT_EQ(queue.front(), 10);
  EXPECT_EQ(queue.back(), 10);
  EXPECT_FALSE(queue.empty());
}

TEST(s21_queue_test, copy) {
  s21::queue<int> queue1({5, 3, 2, 7});
  s21::queue<int> queue2 = queue1;
  std::queue<int> ctrl({5, 3, 2, 7});
  EXPECT_TRUE(compare_queue(ctrl, queue1));
  EXPECT_TRUE(compare_queue(ctrl, queue2));
}

TEST(s21_queue_test, initialize_list) {
  s21::queue<int> queue({-5, 0, 6, 7, 8124});
  std::queue<int> ctrl({-5, 0, 6, 7, 8124});
  EXPECT_TRUE(compare_queue(ctrl, queue));
}
TEST(s21_queue_test, push_multiple) {
  s21::queue<int> queue;
  std::queue<int> ctrl;
  queue.push(10);
  queue.push(20);
  queue.push(-30);
  ctrl.push(10);
  ctrl.push(20);
  ctrl.push(-30);
  EXPECT_TRUE(compare_queue(ctrl, queue));
  EXPECT_EQ(queue.front(), 10);
  EXPECT_EQ(queue.back(), -30);
  EXPECT_EQ(ctrl.front(), 10);
  EXPECT_EQ(ctrl.back(), -30);
}

TEST(s21_queue_test, swap) {
  std::initializer_list<float> data1{5, 4, 3, 2, 1};
  s21::queue<float> queue1(data1);
  std::queue<float> ctrl1(data1);
  std::initializer_list<float> data2{6, 7, 8, 9, 10};
  s21::queue<float> queue2(data2);
  std::queue<float> ctrl2(data2);
  queue1.swap(queue2);
  ctrl1.swap(ctrl2);
  compare_queue(ctrl1, queue1);
  compare_queue(ctrl2, queue2);
}

TEST(s21_queue_test, swap_1) {
  s21::queue<int> queue1({1, 2, 3, 4});
  std::queue<int> ctrl({1, 2, 3, 4});
  s21::queue<int> queue2({-1, -2, -3});
  std::queue<int> ctrl2({-1, -2, -3});
  queue1.swap(queue2);
  EXPECT_TRUE(compare_queue(ctrl2, queue1));
  EXPECT_TRUE(compare_queue(ctrl, queue2));
  queue2.swap(queue1);
  EXPECT_TRUE(compare_queue(ctrl, queue1));
  EXPECT_TRUE(compare_queue(ctrl2, queue2));
}

TEST(s21_queue_test, swap_2) {
  s21::queue<int> queue{566, 123, 3, 3, 2, 1};
  s21::queue<int> queue2{566, 123};
  queue.swap(queue2);
  ASSERT_EQ(queue.size(), 2);
  ASSERT_EQ(queue2.size(), 6);
}

TEST(s21_queue_test, push) {
  s21::queue<int> queue;
  queue.push(566);
  std::queue<int> ctrl;
  ctrl.push(566);
  ASSERT_EQ(queue.front(), ctrl.front());
  ASSERT_EQ(queue.back(), ctrl.back());
}

TEST(s21_queue_test, pop) {
  s21::queue<int> queue{566, 123};
  std::queue<int> ctrl;
  ctrl.push(566);
  ctrl.push(123);
  ASSERT_EQ(queue.front(), ctrl.front());
  ASSERT_EQ(queue.back(), ctrl.back());
  queue.pop();
  ctrl.pop();
  ASSERT_EQ(queue.front(), ctrl.front());
  ASSERT_EQ(queue.back(), ctrl.back());
}

TEST(s21_queue_test, size) {
  s21::queue<int> queue{566, 123, 3, 3, 2, 1};
  s21::queue<int> queue2{566, 123};
  ASSERT_EQ(queue.size(), 6);
  ASSERT_EQ(queue2.size(), 2);
}

TEST(s21_queue_test, emplace_back) {
  s21::queue<int> copy = s21::queue<int>();
  copy.emplace_back(1, 2, 3, 4, 5);
  std::queue<int> og = std::queue<int>();
  og.push(1);
  og.push(2);
  og.push(3);
  og.push(4);
  og.push(5);
  EXPECT_TRUE(compare_queue(og, copy));
}
