#include "s21_array.h"

#include <gtest/gtest.h>

#include <array>

template <typename T, size_t N>
bool compare_array(s21::array<T, N> arr, std::array<T, N> ctrl) {
  if (ctrl.size() != arr.size())
    return false;
  bool result = true;
  for (size_t i = 0; i < arr.size() && result; i++)
    if (ctrl[i] != arr[i]) {
      result = false;
      break;
    }
  return result;
}

TEST(s21_array_test, default_constructor) {
  s21::array<int, 0> arr;
  std::array<int, 0> ctrl;
  ASSERT_TRUE(compare_array(arr, ctrl));
}

TEST(s21_array_test, default_constructor_2) {
  s21::array<int, 0> arr = s21::array<int, 0>();
  ASSERT_EQ(arr.empty(), true);
}

TEST(s21_array_test, default_constructor_3) {
  s21::array<int, 10> arr = s21::array<int, 10>();
  ASSERT_EQ(arr.empty(), false);
}

TEST(s21_array_test, value_constructor) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  ASSERT_EQ(arr.empty(), false);
}

TEST(s21_array_test, value_constructor_2) {
  s21::array<double, 10> arr{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  std::array<double, 10> ctrl{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  ASSERT_TRUE(compare_array(arr, ctrl));
}

TEST(s21_array_test, copy_constructor) {
  s21::array<int, 10> arr{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  s21::array<int, 10> arr_copied(arr);
  std::array<int, 10> ctrl{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  std::array<int, 10> ctrl_copied(ctrl);
  ASSERT_TRUE(compare_array(arr, ctrl));
  ASSERT_TRUE(compare_array(arr_copied, ctrl_copied));
}

TEST(s21_array_test, copy_constructor_2) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  s21::array<int, 4> arr2 = s21::array<int, 4>(arr);

  ASSERT_EQ(arr2.size(), arr.size());
  ASSERT_EQ(arr2.empty(), false);
}

TEST(s21_array_test, move_constructor) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  s21::array<int, 4> arr2 = std::move(arr);

  ASSERT_EQ(arr2.empty(), false);
}

TEST(s21_array_test, move_constructor_2) {
  s21::array<int, 10> arr{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  s21::array<int, 10> arr_moved(std::move(arr));
  std::array<int, 10> ctrl{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  std::array<int, 10> ctrl_moved(std::move(ctrl));
  ASSERT_TRUE(compare_array(arr, ctrl));
  ASSERT_TRUE(compare_array(arr_moved, ctrl_moved));
}

TEST(s21_array_test, operator_move_constructor) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  ASSERT_EQ(arr.empty(), false);
}

TEST(s21_array_test, operator_move_constructor_2) {
  s21::array<int, 10> arr{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  s21::array<int, 10> arr_moved;
  arr_moved = std::move(arr);
  std::array<int, 10> ctrl{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  std::array<int, 10> ctrl_moved;
  ctrl_moved = std::move(ctrl);
  ASSERT_TRUE(compare_array(arr, ctrl));
  ASSERT_TRUE(compare_array(arr_moved, ctrl_moved));
}

TEST(s21_array_test, at) {
  s21::array<int, 4> arr = s21::array<int, 4>();
  arr.fill(3);

  ASSERT_EQ(arr.at(2), 3);
}

TEST(s21_array_test_WITH_THROW, at_2) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  EXPECT_ANY_THROW(arr.at(10));
}

TEST(s21_array_test_WITH_THROW, at_3) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  EXPECT_ANY_THROW(arr.at(-10));
}

TEST(s21_array_test_WITH_THROW, at_4) {
  s21::array<int, 0> arr = s21::array<int, 0>();

  EXPECT_ANY_THROW(arr.at(0));
}

TEST(s21_array_test, at_5) {
  s21::array<int, 3> arr{1, 2, 3};
  std::array<int, 3> ctrl{1, 2, 3};
  ASSERT_EQ(arr.at(1), ctrl.at(1));
  ASSERT_EQ(arr.at(0), ctrl.at(0));
}

TEST(s21_array_test, square_operator) {
  s21::array<int, 4> arr = s21::array<int, 4>();
  arr.fill(3);

  ASSERT_EQ(arr[2], 3);
}

TEST(s21_array_test_WITH_THROW, square_operator_2) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  EXPECT_NO_THROW(arr[10]);
}

TEST(s21_array_test_WITH_THROW, square_operator_3) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  EXPECT_NO_THROW(arr[-10]);
}

TEST(s21_array_test, square_operator_4) {
  s21::array<int, 10> arr{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  std::array<int, 10> ctrl{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  ASSERT_EQ(arr[5], ctrl[5]);
  ASSERT_EQ(arr[9], ctrl[9]);
}

TEST(s21_array_test, empty) {
  s21::array<int, 3> arr{1, 2, 3};
  std::array<int, 3> ctrl{1, 2, 3};
  ASSERT_EQ(arr.empty(), ctrl.empty());
}

TEST(s21_array_test, empty2) {
  s21::array<int, 0> arr;
  std::array<int, 0> ctrl;
  ASSERT_EQ(arr.empty(), ctrl.empty());
}

TEST(s21_array_test, empty_3) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  ASSERT_EQ(arr.empty(), false);
}

TEST(s21_array_test, front) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  ASSERT_EQ(arr.front(), 1);
}

TEST(s21_array_test, front_2) {
  s21::array<int, 3> arr{1, 2, 3};
  std::array<int, 3> ctrl{1, 2, 3};
  ASSERT_EQ(arr.front(), ctrl.front());
  arr[0] = 8;
  ctrl[0] = 8;
  ASSERT_EQ(arr.front(), ctrl.front());
}

TEST(s21_array_test, back) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  ASSERT_EQ(arr.back(), 4);
}

TEST(s21_array_test, back_2) {
  s21::array<int, 3> arr{1, 2, 3};
  std::array<int, 3> ctrl{1, 2, 3};
  ASSERT_EQ(arr.back(), ctrl.back());
  arr[2] = 8;
  ctrl[2] = 8;
  ASSERT_EQ(arr.back(), ctrl.back());
}

TEST(s21_array_test, data) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  auto dt = arr.data();

  ASSERT_EQ(dt[0], 1);
}

TEST(s21_array_test, data_2) {
  s21::array<int, 1> arr{6};
  s21::array<int, 1>::iterator iter = arr.data();
  ASSERT_EQ(*iter, 6);
  ASSERT_EQ(iter, arr.begin());
}

TEST(s21_array_test, begin) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  auto dt = arr.begin();

  ASSERT_EQ(*dt, 1);
}

TEST(s21_array_test, begin_end) {
  s21::array<int, 0> arr;
  s21::array<int, 0>::iterator iter = arr.begin();
  ASSERT_EQ(iter, arr.end());
}

TEST(s21_array_test, size) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  ASSERT_EQ(arr.size(), 4);
}

TEST(s21_array_test, size_2) {
  s21::array<int, 3> arr{1, 2, 3};
  std::array<int, 3> ctrl{1, 2, 3};
  ASSERT_EQ(arr.size(), ctrl.size());
}

TEST(s21_array_test, max_size) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});

  ASSERT_EQ(arr.max_size(), 4);
}

TEST(s21_array_test, max_size_2) {
  s21::array<int, 3> arr{1, 2, 3};
  std::array<int, 3> ctrl{1, 2, 3};
  ASSERT_EQ(arr.max_size(), ctrl.max_size());
}

TEST(s21_array_test, fill) {
  s21::array<int, 5> arr;
  arr.fill(100);
  for (std::size_t i = 0; i < arr.size(); i++)
    ASSERT_EQ(arr[i], 100);
}

TEST(s21_array_test, fill_2) {
  s21::array<int, 10> arr;
  arr.fill(99);
  std::array<int, 10> ctrl;
  ctrl.fill(99);
  ASSERT_TRUE(compare_array(arr, ctrl));
}

TEST(s21_array_test, swap) {
  s21::array<int, 4> arr = s21::array<int, 4>({1, 2, 3, 4});
  s21::array<int, 4> arr2 = s21::array<int, 4>();
  arr2.fill(7);
  arr.swap(arr2);

  ASSERT_EQ(*arr.begin(), 7);
}

TEST(s21_array_test, swap_2) {
  s21::array<int, 10> arr;
  s21::array<int, 10> arr2{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  arr.fill(99);
  arr2.swap(arr);
  std::array<int, 10> ctrl;
  std::array<int, 10> ctrl2{6, 5, 3, 4, 77, 1, 18, 6, 1, 2};
  ctrl.fill(99);
  ctrl2.swap(ctrl);
  ASSERT_TRUE(compare_array(arr, ctrl));
  ASSERT_TRUE(compare_array(arr, ctrl));
}
