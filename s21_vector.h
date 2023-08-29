#ifndef CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_

#include <iostream>
#include <limits>
#include <memory>

namespace s21 {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  // using позволяет определять псевдонимы для типов

  vector();
  explicit vector(size_type size);
  vector(std::initializer_list<T> const &items);
  // explicit не допускает неявные преобразования типов
  vector(const vector &other);
  vector(vector &&other);
  ~vector();
  vector<T> &operator=(const vector &other);
  vector<T> &operator=(vector &&other);

  reference at(size_type position);
  reference operator[](size_type position);
  const_reference operator[](size_type position) const;
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type newCapacity);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator position, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  //допы
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&... args);
  template <typename... Args>
  void emplace_back(Args &&... args);

 private:
  T *arr_;
  size_type size_;
  size_type capacity_;
};

}  // namespace s21

#include "s21_vector.inl"

#endif
