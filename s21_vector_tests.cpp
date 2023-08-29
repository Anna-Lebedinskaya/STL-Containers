#include <gtest/gtest.h>

#include <vector>

#include "s21_vector.h"

TEST(s21_vector_test_WITH_TROW, Operator_Brakets) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  int &v = vector[4];
  int &c = ctrl[4];
  EXPECT_EQ(v, c);

  v = vector[0];
  c = ctrl[0];
  EXPECT_EQ(v, c);

  v = vector[6];
  c = ctrl[6];
  EXPECT_EQ(v, c);
}

TEST(s21_vector_test, Front) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  EXPECT_EQ(vector.front(), ctrl.front());
}

TEST(s21_vector_test, Back) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  EXPECT_EQ(vector.back(), ctrl.back());
}

TEST(s21_vector_test, Data) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  int *v = vector.data();
  int *c = ctrl.data();
  EXPECT_EQ(*v, *c);
}

TEST(s21_vector_test, Begin) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  s21::vector<int>::iterator v = vector.begin();
  std::vector<int>::iterator c = ctrl.begin();
  EXPECT_EQ(*v, *c);
}

TEST(s21_vector_test, End) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  s21::vector<int>::iterator v = vector.end();
  std::vector<int>::iterator c = ctrl.end();
  EXPECT_EQ(*--v, *--c);
}

TEST(s21_vector_test, iterator_1) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  s21::vector<int>::iterator v = vector.begin();
  std::vector<int>::iterator c = ctrl.begin();
  EXPECT_EQ(*++v, *++c);
}

TEST(s21_vector_test, iterator_2) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  s21::vector<int>::iterator v = vector.end();
  std::vector<int>::iterator c = ctrl.end();
  EXPECT_EQ(*--v, *--c);
}

TEST(s21_vector_test, iterator_3) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  s21::vector<int>::iterator v = vector.begin();
  std::vector<int>::iterator c = ctrl.begin();
  EXPECT_TRUE(*v == *c);
}

TEST(s21_vector_test, iterator_4) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  s21::vector<int>::iterator v = vector.begin();
  std::vector<int>::iterator c = ctrl.begin();
  EXPECT_TRUE(*v != ++*c);
}

TEST(s21_vector_test, Empty) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  EXPECT_EQ(vector.empty(), vector.empty());
}

TEST(s21_vector_test, Size) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  EXPECT_EQ(vector.size(), ctrl.size());

  s21::vector<int> vectorTemp;
  std::vector<int> ctrlTemp;
  EXPECT_EQ(vectorTemp.size(), ctrlTemp.size());
}

TEST(s21_vector_test, max_size) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  EXPECT_EQ(vector.max_size(), ctrl.max_size());

  s21::vector<int> vectorTemp{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrlTemp{1, 4, 5, 2, 7, 12, 14};
  EXPECT_EQ(vectorTemp.max_size(), ctrlTemp.max_size());
}

TEST(s21_vector_test, max_size_2) {
  s21::vector<int> test_int;
  std::vector<int> og_int;
  EXPECT_EQ(test_int.max_size(), og_int.max_size());
  s21::vector<double> test_double;
  std::vector<double> og_double;
  EXPECT_EQ(test_double.max_size(), og_double.max_size());
}

TEST(s21_vector_test_WITH_TROW, Reserve) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  vector.reserve(14);
  ctrl.reserve(14);
  EXPECT_EQ(vector.capacity(), ctrl.capacity());

  //   EXPECT_THROW(vector.reserve(2), std::exception);
}

TEST(s21_vector_test, capacity) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  EXPECT_EQ(vector.capacity(), 7);
}

TEST(s21_vector_test, shrink_to_fit) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  vector.reserve(14);
  ctrl.reserve(14);
  vector.shrink_to_fit();
  ctrl.shrink_to_fit();
  EXPECT_EQ(vector.capacity(), ctrl.capacity());
}

TEST(s21_vector_test, clear) {
  s21::vector<int> vector{1, 4, 5, 2, 7, 12, 14};
  std::vector<int> ctrl{1, 4, 5, 2, 7, 12, 14};
  vector.clear();
  ctrl.clear();
  EXPECT_EQ(vector.capacity(), 7);
  EXPECT_EQ(vector.size(), ctrl.size());
}

TEST(s21_vector_test, insert) {
  s21::vector<int> vector;
  std::vector<int> ctrl;
  vector.push_back(2);
  vector.push_back(23);
  vector.push_back(3);
  vector.push_back(33);

  ctrl.push_back(2);
  ctrl.push_back(23);
  ctrl.push_back(3);
  ctrl.push_back(33);

  s21::vector<int>::iterator v = vector.begin();
  std::vector<int>::iterator c = ctrl.begin();

  v = vector.insert(v, 1);
  c = ctrl.insert(c, 1);

  EXPECT_EQ(*v, *c);
}

TEST(s21_vector_test, insert_2) {
  s21::vector<int> vector;
  std::vector<int> ctrl;
  vector.push_back(2);
  vector.push_back(23);
  vector.push_back(3);
  vector.push_back(33);

  ctrl.push_back(2);
  ctrl.push_back(23);
  ctrl.push_back(3);
  ctrl.push_back(33);

  s21::vector<int>::iterator v = vector.begin();
  std::vector<int>::iterator c = ctrl.begin();

  v = vector.insert(v + 3, 1);
  c = ctrl.insert(c + 3, 1);
  EXPECT_EQ(*v, *c);
}

TEST(s21_vector_test, erase_1) {
  s21::vector<int> vector;
  std::vector<int> ctrl;
  vector.push_back(2);
  vector.push_back(23);
  vector.push_back(3);
  vector.push_back(33);

  ctrl.push_back(2);
  ctrl.push_back(23);
  ctrl.push_back(3);
  ctrl.push_back(33);

  s21::vector<int>::iterator v = vector.begin();
  std::vector<int>::iterator c = ctrl.begin();

  vector.erase(v);
  ctrl.erase(c);
  EXPECT_EQ(vector[0], ctrl[0]);
}

TEST(s21_vector_test, erase_2) {
  s21::vector<int> vector;
  std::vector<int> ctrl;
  vector.push_back(2);
  vector.push_back(23);
  vector.push_back(3);
  vector.push_back(33);

  ctrl.push_back(2);
  ctrl.push_back(23);
  ctrl.push_back(3);
  ctrl.push_back(33);

  s21::vector<int>::iterator v = vector.begin();
  std::vector<int>::iterator c = ctrl.begin();

  vector.erase(v + 3);
  ctrl.erase(c + 3);
  EXPECT_EQ(vector[2], ctrl[2]);
}

TEST(s21_vector_test, push_back) {
  s21::vector<int> vector;
  std::vector<int> ctrl;
  vector.push_back(2);
  vector.push_back(23);
  vector.push_back(3);
  vector.push_back(33);

  ctrl.push_back(2);
  ctrl.push_back(23);
  ctrl.push_back(3);
  ctrl.push_back(33);

  for (size_t i = 0; i < vector.size(); i++) {
    EXPECT_EQ(vector[i], ctrl[i]);
  }
}

TEST(s21_vector_test, PopBack) {
  s21::vector<int> vector;
  std::vector<int> ctrl;
  vector.push_back(2);
  vector.push_back(23);
  vector.push_back(3);
  vector.push_back(33);
  vector.pop_back();
  vector.pop_back();

  ctrl.push_back(2);
  ctrl.push_back(23);
  ctrl.push_back(3);
  ctrl.push_back(33);
  ctrl.pop_back();
  ctrl.pop_back();

  for (size_t i = 0; i < vector.size(); i++) {
    EXPECT_EQ(vector[i], ctrl[i]);
  }
}

TEST(s21_vector_test, Swap) {
  s21::vector<int> vector{4, 4, 4};
  s21::vector<int> vectorTemp{1, 2, 3};
  std::vector<int> ctrl{4, 4, 4};
  std::vector<int> ctrlTemp{1, 2, 3};
  vector.swap(vectorTemp);
  ctrl.swap(ctrlTemp);
  for (size_t i = 0; i < vector.size(); i++) {
    EXPECT_EQ(vector[i], ctrl[i]);
    EXPECT_EQ(vectorTemp[i], ctrlTemp[i]);
  }
}

TEST(s21_vector_test_WITH_TROW, Size) {
  s21::vector<int> vector(5);
  EXPECT_EQ(vector.capacity(), 5);

  EXPECT_THROW(s21::vector<int> vector(-2), std::exception);
}

TEST(s21_vector_test, copy_construction) {
  s21::vector<int> vector{4, 4, 4};
  s21::vector<int> vectorTemp(vector);
  for (size_t i = 0; i < vector.size(); i++) {
    EXPECT_EQ(vector[i], vectorTemp[i]);
  }
}

TEST(s21_vector_test, operator_equal) {
  s21::vector<int> vector{4, 4, 4};
  s21::vector<int> vectorTemp = vector;
  for (size_t i = 0; i < vector.size(); i++) {
    EXPECT_EQ(vector[i], 4);
  }
}

TEST(s21_vector_test, move_constructor) {
  s21::vector<int> vector{4, 4, 4};
  s21::vector<int> vectorTemp(std::move(vector));
  for (size_t i = 0; i < vectorTemp.size(); i++) {
    EXPECT_EQ(vectorTemp[i], 4);
  }
}

TEST(s21_vector_test, move_equal_constructor) {
  s21::vector<int> vector{4, 4, 4};
  s21::vector<int> vectorTemp;
  vectorTemp = std::move(vector);
  for (size_t i = 0; i < vectorTemp.size(); i++) {
    EXPECT_EQ(vectorTemp[i], 4);
  }
}

TEST(s21_vector_test_WITH_TROW, access_tests) {
  s21::vector<int> test({1, 2, -6, 5, 256, 1026});
  std::vector<int> og({1, 2, -6, 5, 256, 1026});
  EXPECT_EQ(test.back(), og.back());
  EXPECT_EQ(test.front(), og.front());
  EXPECT_EQ(test.at(3), og.at(3));
  EXPECT_EQ(test[3], og[3]);
  EXPECT_ANY_THROW(test.at(12597));
  EXPECT_ANY_THROW(test.at(-124));
  int *test_begin = test.begin();
  int *test_end = test.end() - 1;
  int *test_data = test.data();
  auto og_begin = og.begin();
  auto og_end = og.end() - 1;
  auto og_data = og.data();
  EXPECT_EQ(*test_begin, *og_begin);
  EXPECT_EQ(*test_end, *og_end);
  EXPECT_EQ(test_begin, test_data);
  test_data++;
  og_data++;
  EXPECT_EQ(*test_data, *og_data);
}

TEST(s21_vector_test, copy_construct_empty) {
  s21::vector<double> test;
  s21::vector<double> copy(test);
  EXPECT_TRUE(copy.empty());
  EXPECT_EQ(test.size(), copy.size());
  EXPECT_EQ(test.capacity(), copy.capacity());
}

TEST(s21_vector_case, emplace) {
  s21::vector<int> vector{1, 2, 3, 4, 5};
  std::vector<int> vector2{1, 8, 7, 6, 2, 3, 4, 5};
  auto pos = vector.begin();
  ++pos;
  auto result = vector.emplace(pos, 8, 7, 6);
  ASSERT_EQ(*result, 6);

  vector.emplace_back(11, 22, 33);
  std::vector<int> vector3{1, 8, 7, 6, 2, 3, 4, 5, 11, 22, 33};
  for (long unsigned i = 0; i < vector.size(); i++)
    ASSERT_EQ(vector[i], vector3[i]);
}

// g++ -Werror -Wextra --std=c++17 s21_vector_tests.cpp -o test -lgtest
// -lgtest_main -pthread -g && ./test
