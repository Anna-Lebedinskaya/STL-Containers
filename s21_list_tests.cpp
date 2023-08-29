#include <gtest/gtest.h>

#include <iostream>
#include <limits>
#include <list>
// #include <queue>

#include "s21_list.h"

template <typename T> bool compare_list(std::list<T> ctrl, s21::list<T> copy) {
  bool res = true;
  if (ctrl.size() != copy.size()) {
    res = false;
  } else {
    bool pass = true;
    while (pass && !ctrl.empty()) {
      if (ctrl.front() != copy.front()) {
        pass = false;
        res = false;
      }
      ctrl.pop_front();
      copy.pop_front();
    }
  }
  return res;
}

TEST(s21_list_test, default_constructor) {
  s21::list<int> lst;
  std::list<int> ctrl;
  ASSERT_EQ(lst.empty(), ctrl.empty());
  ASSERT_EQ(ctrl.max_size() - lst.max_size(), 0);
}

TEST(s21_list_test, default_constructor_2) {
  s21::list<int> lst = s21::list<int>();
  ASSERT_EQ(lst.empty(), true);
}

TEST(s21_list_test, init_constructor) {
  s21::list<int> lst = s21::list<int>(3);
  ASSERT_EQ(lst.empty(), false);
}

TEST(s21_list_test, init_constructor_2) {
  s21::list<int> lst{1, 2, 3};
  ASSERT_FALSE(lst.empty());
  ASSERT_EQ(lst.front(), 1);
  lst.clear();
  ASSERT_TRUE(lst.empty());
}

TEST(s21_list_test, copy_constructor) {
  s21::list<int> lst{3, 2, 1};
  s21::list<int> lst2(lst);
  ASSERT_EQ(lst.front(), lst2.front());
}

TEST(s21_list_test, copy_constructor_2) {
  s21::list<int> lst = s21::list<int>(3);
  lst.push_back(4);
  lst.push_back(3);
  s21::list<int> lst2 = s21::list<int>(lst);
  std::list<int> ctrl({0, 0, 0, 4, 3});
  ASSERT_EQ(lst2.size(), 5);
  EXPECT_TRUE(compare_list(ctrl, lst2));
}

TEST(s21_list_test, move_constructor) {
  s21::list<int> lst{1, 2, 3};
  s21::list<int> lst1(std::move(lst));
  ASSERT_TRUE(lst.empty());
  ASSERT_FALSE(lst1.empty());
}

TEST(s21_list_test, move_constructor_2) {
  s21::list<int> lst = s21::list<int>(3);
  lst.push_back(4);
  lst.push_back(3);
  s21::list<int> lst2 = std::move(lst);
  ASSERT_EQ(lst2.size(), 5);
  ASSERT_EQ(lst.size(), 0);
  EXPECT_TRUE(lst.empty());
  std::list<int> ctrl({0, 0, 0, 4, 3});
  EXPECT_TRUE(compare_list(ctrl, lst2));
}

TEST(s21_list_test, constructor_and_empty) {
  s21::list<float> lst;
  std::list<float> ctrl;
  ASSERT_EQ(lst.empty(), ctrl.empty());
}

TEST(s21_list_test, move_operator_constructor) {
  s21::list<int> lst{1, 2, 3};
  s21::list<int> lst1(std::move(lst));
  ASSERT_TRUE(lst.empty());
  ASSERT_FALSE(lst1.empty());
}

TEST(s21_list_test, front_and_back) {
  s21::list<float> lst{5, 4, 3, 2, 1};
  std::list<float> ctrl{5, 4, 3, 2, 1};
  ASSERT_EQ(lst.front(), ctrl.front());
  ASSERT_EQ(lst.back(), ctrl.back());
}

TEST(s21_list_test, back) {
  s21::list<int> lst = s21::list<int>(3);
  lst.push_back(5);
  ASSERT_EQ(lst.back(), 5);
}

TEST(s21_list_test, back_2) {
  s21::list<int> lst = s21::list<int>();
  std::list<int> ctrl = std::list<int>();
  ASSERT_EQ(lst.back(), ctrl.back());
}

TEST(s21_list_test, front) {
  s21::list<int> lst = s21::list<int>(3);
  lst.push_back(5);
  ASSERT_EQ(lst.back(), 5);
}

TEST(s21_list_test, front_2) {
  s21::list<int> lst = s21::list<int>();
  std::list<int> ctrl = std::list<int>();
  ASSERT_EQ(lst.front(), ctrl.front());
}

TEST(s21_list_test, empty) {
  s21::list<int> lst = s21::list<int>();
  ASSERT_EQ(lst.empty(), true);
}

TEST(s21_list_test, max_size) {
  s21::list<float> lst;
  std::list<float> ctrl;
  ASSERT_EQ(lst.max_size(), ctrl.max_size());
}

TEST(s21_list_test, size_constructor) {
  s21::list<int> lst(5);
  ASSERT_EQ(lst.size(), 5);
}

TEST(s21_list_test, size) {
  s21::list<int> lst = s21::list<int>();
  ASSERT_EQ(lst.size(), 0);
}

TEST(s21_list_test, size_2) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_front(4);
  lst.push_back(4);
  lst.push_back(3);
  lst.push_back(2);
  lst.pop_back();
  lst.pop_front();
  ASSERT_EQ(lst.size(), 3);
}

TEST(s21_list_test, clear) {
  s21::list<float> lst{5, 4, 3, 2, 1};
  lst.clear();
  ASSERT_EQ(lst.size(), 0);

  s21::list<int> lst2;
  lst2.clear();
  ASSERT_EQ(lst2.size(), 0);
}

TEST(s21_list_test, clear_2) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_front(4);
  lst.clear();
  ASSERT_EQ(lst.empty(), true);
}

TEST(s21_list_test, clear_3) {
  s21::list<int> lst = s21::list<int>();
  lst.clear();
  ASSERT_EQ(lst.empty(), true);
}

TEST(s21_list_test, insert) {
  s21::list<int> lst;
  lst.push_back(10);
  lst.push_back(12);
  lst.insert(lst.begin(), 1);

  std::list<int> ctrl;
  ctrl.push_back(10);
  ctrl.push_back(12);
  ctrl.insert(ctrl.begin(), 1);
  EXPECT_TRUE(compare_list(ctrl, lst));
}

TEST(s21_list_test, insert_2) {
  s21::list<int> lst = s21::list<int>();
  auto it = lst.begin();
  lst.insert(it, 0);
  ASSERT_EQ(lst.size(), 1);
}

TEST(s21_list_test, insert_3) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(10);
  lst.push_back(12);
  lst.push_back(12);
  auto it = lst.begin();
  lst.insert(it, 12);
  ASSERT_EQ(lst.size(), 4);
}

TEST(s21_list_test, insert_end) {
  s21::list<int> lst;
  lst.push_back(10);
  lst.push_back(12);
  lst.insert(lst.end(), 1);

  std::list<int> ctrl;
  ctrl.push_back(10);
  ctrl.push_back(12);
  ctrl.insert(ctrl.end(), 1);
  EXPECT_TRUE(compare_list(ctrl, lst));
}

TEST(s21_list_test, insert_begin) {
  s21::list<int> lst;
  lst.push_back(10);
  lst.push_back(12);
  lst.insert(lst.begin(), 1);

  std::list<int> ctrl;
  ctrl.push_back(10);
  ctrl.push_back(12);
  ctrl.insert(ctrl.begin(), 1);
  EXPECT_TRUE(compare_list(ctrl, lst));
}

TEST(s21_list_test, insert_begin_empty) {
  s21::list<int> lst;
  lst.insert(lst.begin(), 1);
  lst.push_back(10);
  lst.push_back(12);

  std::list<int> ctrl;
  ctrl.insert(ctrl.begin(), 1);
  ctrl.push_back(10);
  ctrl.push_back(12);
  EXPECT_TRUE(compare_list(ctrl, lst));
}

TEST(s21_list_test, erase) {
  s21::list<int> lst;
  auto it = lst.begin();
  lst.insert(it, 0);
  lst.push_back(12);
  lst.push_back(34);
  it = lst.begin();
  lst.erase(++it);
  ASSERT_EQ(lst.size(), 2);

  std::list<int> ctrl;
  auto ctrl_it = ctrl.begin();
  ctrl.insert(ctrl_it, 0);
  ctrl.push_back(12);
  ctrl.push_back(34);
  ctrl_it = ctrl.begin();
  ctrl.erase(++ctrl_it);
  EXPECT_TRUE(compare_list(ctrl, lst));
}

TEST(s21_list_test_WITH_THROW, erase_2) {
  s21::list<int> lst = s21::list<int>();
  auto it = lst.begin();
  EXPECT_THROW(lst.erase(it), std::exception);
}

TEST(s21_list_test, erase_3) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  lst.push_back(4);
  auto it = lst.begin();
  lst.erase(it);

  std::list<int> ctrl;
  ctrl.push_back(1);
  ctrl.push_back(2);
  ctrl.push_back(3);
  ctrl.push_back(4);
  auto ctrl_it = ctrl.begin();
  ctrl.erase(ctrl_it);
  EXPECT_TRUE(compare_list(ctrl, lst));
}

TEST(s21_list_test, push) {
  s21::list<int> lst;
  lst.push_front(99);
  lst.push_back(123);
  std::list<int> ctrl;
  ctrl.push_front(99);
  ctrl.push_back(123);
  ASSERT_EQ(lst.front(), ctrl.front());
  ASSERT_EQ(lst.back(), ctrl.back());
}

TEST(s21_list_test, push_back) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  ASSERT_EQ(lst.front(), 5);
}

TEST(s21_list_test, push_back_2) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_back(54);
  ASSERT_EQ(lst.front(), 5);
}

TEST(s21_list_test, push_back_3) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_back(54);
  ASSERT_EQ(lst.back(), 54);
}

TEST(s21_list_test, push_front) {
  s21::list<int> lst = s21::list<int>();
  lst.push_front(54);
  lst.push_front(32);
  lst.push_front(12);
  ASSERT_EQ(lst.front(), 12);
}

TEST(s21_list_test, pop) {
  s21::list<int> lst{566, 123};
  std::list<int> ctrl;
  ctrl.push_back(566);
  ctrl.push_back(123);
  ASSERT_EQ(lst.front(), ctrl.front());
  ASSERT_EQ(lst.back(), ctrl.back());
  lst.pop_back();
  ctrl.pop_back();
  ASSERT_EQ(lst.front(), ctrl.front());
  ASSERT_EQ(lst.back(), ctrl.back());
  lst.pop_front();
  ctrl.pop_front();
  ASSERT_EQ(lst.empty(), ctrl.empty());
}

TEST(s21_list_test, pop_front) {
  s21::list<int> lst = s21::list<int>();
  lst.push_front(54);
  lst.push_front(32);
  lst.push_front(12);
  lst.pop_front();
  ASSERT_EQ(lst.front(), 32);
}

TEST(s21_list_test, pop_back) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(5);
  lst.push_back(45);
  lst.pop_back();
  ASSERT_EQ(lst.back(), 5);
}

TEST(s21_list_test, merge) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(10);
  lst.push_back(20);
  lst.push_back(30);
  s21::list<int> lst2 = s21::list<int>();
  lst2.push_back(40);
  lst2.push_back(50);
  lst2.push_back(60);
  lst.merge(lst2);
  s21::list<int> lst3 = s21::list<int>();
  lst3.push_back(10);
  lst3.push_back(20);
  lst3.push_back(30);
  lst3.push_back(40);
  lst3.push_back(50);
  lst3.push_back(60);

  ASSERT_EQ(lst3.size(), 6);
}

TEST(s21_list_test, swap) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(15);
  lst.push_back(32);
  s21::list<int> lst2 = s21::list<int>();
  lst2.push_back(81);
  lst2.push_back(71);

  lst.swap(lst2);

  ASSERT_EQ(lst.front(), 81);
  ASSERT_EQ(lst2.front(), 15);
}

TEST(s21_list_test, size_swap) {
  s21::list<int> lst{566, 123, 3, 3, 2, 1};
  s21::list<int> lst2{566, 123};
  ASSERT_EQ(lst.size(), 6);
  ASSERT_EQ(lst2.size(), 2);
  lst.swap(lst2);
  ASSERT_EQ(lst.size(), 2);
  ASSERT_EQ(lst2.size(), 6);
}

TEST(s21_list_test, reverse) {
  s21::list<int> lst = {10, 20, 30};
  lst.reverse();
  ASSERT_EQ(lst.front(), 30);
}

TEST(s21_list_test, splice) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  s21::list<int> lst2 = s21::list<int>();
  lst2.push_back(4);
  lst2.push_back(5);
  s21::list<int>::const_iterator it(lst.begin());
  lst.splice(it, lst2);
  ASSERT_EQ(lst.size(), 5);
}

TEST(s21_list_test, splice_2) {
  s21::list<int> lst = {1, 2, 3};
  s21::list<int> lst2 = {4, 5};
  s21::list<int>::const_iterator it(lst.begin());
  lst.splice(it, lst2);
  ASSERT_EQ(lst.front(), 4);
}

TEST(s21_list_test_WITH_TROW, splice_3) {
  s21::list<int> lst = {234};
  s21::list<int> lst2;
  s21::list<int>::const_iterator it(lst.begin());
  EXPECT_THROW(lst.splice(++it, lst2), std::exception);
}

TEST(s21_list_test, unique) {
  s21::list<int> lst = {10, 10, 20, 20, 30, 40, 50, 60};
  std::list<int> ctrl = {10, 10, 20, 20, 30, 40, 50, 60};

  lst.unique();
  ctrl.unique();

  ASSERT_EQ(lst.size(), 6);
  EXPECT_TRUE(compare_list(ctrl, lst));
}

TEST(s21_list_test, sort) {
  s21::list<int> lst = s21::list<int>();

  lst.push_back(5);
  lst.push_back(4);
  lst.push_back(3);
  lst.push_back(2);
  lst.push_back(1);

  lst.sort();

  ASSERT_EQ(lst.front(), 1);
  std::list<int> ctrl({1, 2, 3, 4, 5});
  EXPECT_TRUE(compare_list(ctrl, lst));
}

TEST(s21_list_test, sort_2) {
  s21::list<int> lst = s21::list<int>();

  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  lst.push_back(4);
  lst.push_back(5);

  lst.sort();

  std::list<int> ctrl({1, 2, 3, 4, 5});

  ASSERT_EQ(lst.front(), 1);
  EXPECT_TRUE(compare_list(ctrl, lst));
}

TEST(s21_list_test, sort_3) {
  s21::list<int> lst = s21::list<int>();

  lst.push_back(830145);
  lst.push_back(1908);
  lst.push_back(-1435);
  lst.push_back(6789);
  lst.push_back(-12);
  lst.push_back(8301345);

  std::list<int> ctrl = std::list<int>();

  ctrl.push_back(830145);
  ctrl.push_back(1908);
  ctrl.push_back(-1435);
  ctrl.push_back(6789);
  ctrl.push_back(-12);
  ctrl.push_back(8301345);

  lst.sort();
  ctrl.sort();

  ASSERT_EQ(lst.front(), -1435);
  EXPECT_TRUE(compare_list(ctrl, lst));
}

TEST(s21_list_test, begin) {
  s21::list<int> l({1, 2, 3, 4, 5});
  ASSERT_FALSE(l.begin() != l.begin());
}

TEST(s21_list_test, begin_1) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(3);
  lst.push_back(2);
  lst.push_back(4);
  lst.push_back(5);
  ASSERT_EQ(3, lst.front());
}

TEST(s21_list_test, end) {
  s21::list<int> lst = s21::list<int>();
  lst.push_back(3);
  lst.push_back(2);
  lst.push_back(4);
  lst.push_back(5);
  ASSERT_EQ(5, lst.back());
}

TEST(s21_list_case, emplace) {
  s21::list<float> s21_list{5, 4, 3, 2, 1};
  std::list<float> std_list{5, 6, 7, 8, 4, 3, 2, 1};
  auto pos = s21_list.begin();
  ++pos;
  s21::list<float>::const_iterator pos_const(pos);
  auto result = s21_list.emplace(pos_const, 6.f, 7.f, 8.f);
  ASSERT_EQ(*result, 8);
  compare_list(std_list, s21_list);

  std_list.emplace(++std_list.begin());
  auto ins_pos = s21_list.begin();
  ++ins_pos;
  s21::list<float>::const_iterator ins_pos_const(ins_pos);
  s21_list.emplace(ins_pos_const);

  s21_list.emplace_back(444.f, 555.f, 666.f);
  s21_list.emplace_front(111.f, 222.f, 333.f);
  std::list<float> std_list2{111, 222, 333, 5, 0,   6,   7,  8,
                             4,   3,   2,   1, 444, 555, 666};
  compare_list(std_list2, s21_list);

  ASSERT_EQ(*pos_const, 4);
}
